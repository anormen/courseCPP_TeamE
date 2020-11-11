#include "message_handler.hpp"

message_handler::message_handler()
{
    can.canInit();
    this->init_fr100();
    this->init_fr200();
}

message_handler::~message_handler() {}


void message_handler::fr200_output_thread(fr200 &data_write)
{
    std::thread write_thread([&]() {
        while (true)
        {
            std::cout << "write thread\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));
            auto status = exit_future.wait_for(std::chrono::nanoseconds(0));
            if (status == std::future_status::ready)
                break;
            //std::lock_guard<std::mutex> guard(frame_write_mutex); //is it released in end of while? scope
            memcpy(&frame_write, &data_write, 16);
            uint16_t b = can.canWriteFrame(frame_write);
            can.printFrame(frame_write);
        }
    });
    write_thread.detach();
}

void message_handler::fr100_input_thread(fr100 &data_read)
{

    std::thread read_thread([&]() {
        exit.set_value_at_thread_exit(true);
        while (true)
        {
            std::cout << "read thread\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));

            std::lock_guard<std::mutex> guard(data_read_mutex); // Hur funkar detta???

            can.canReadFrame(frame_read);
            if (frame_read.can_dlc > 0)
            {
                can.printFrame(frame_read);
                //std::lock_guard<std::mutex> guard(data_read_mutex);
                memcpy(&data_read, &frame_read, 16);
                mode = static_cast<SimulationMode>(data_read.mode);
                while (mode == SimulationMode::INACTIVE)
                {
                    can.canReadFrame(frame_read);
                    memcpy(&data_read, &frame_read, 16);
                    mode = static_cast<SimulationMode>(data_read.mode);
                }
            }
            if (mode == SimulationMode::OFF)
                break;
        }
    });
    read_thread.detach();
}

void message_handler::init_fr200()
{
    data_write.rpm = 0;
    data_write.fuel = 0;
    data_write.telltale = 0;
    data_write.updatebit = 0;
    data_write.res0 = 0;
    data_write.res1 = 0;
    data_write.res2 = 0;
}

void message_handler::init_fr100(){
    data_read.mode=0;
    data_read.gearlever=0;
    data_read.startstop=0;
    data_read.updatebit=0;
    data_read.accelerator=0;
    data_read.brake=0;
    data_read.candlc=0;
    data_read.res0=0;
    data_read.res1=0;
    data_read.res2=0;
    data_read.res3=0;
    data_read.res4=0;
}