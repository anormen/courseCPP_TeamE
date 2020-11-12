#include "message_handler.hpp"

message_handler::message_handler()
{
    this->can.canInit();
    this->init_fr100(this->data_read);
    this->init_fr200(this->data_write);
    this->exit_future = this->exit.get_future();
}

message_handler::~message_handler() {}


void message_handler::fr200_output_thread(fr200 &frame200)
{
    std::thread write_thread([&]() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));
            auto status = exit_future.wait_for(std::chrono::nanoseconds(0));
            if (status == std::future_status::ready){
                std::cout <<" exit write thread\n";
                break;
            }
            //std::lock_guard<std::mutex> guard(frame_write_mutex); //is it released in end of while? scope
            {
            data_write = frame200;
            std::lock_guard<std::mutex> guard(data_write_mutex);
            memcpy(&frame_write, &data_write, 16);
            uint16_t b = can.canWriteFrame(frame_write);
            //frame200=data_write;
            }
            can.printFrame(frame_write);
            
        }
    });
    write_thread.detach();
}

void message_handler::fr100_input_thread(fr100 &frame100)
{

    std::thread read_thread([&]() {
        exit.set_value_at_thread_exit(true);
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));

            this->can.canReadFrame(frame_read);
            if (frame_read.can_dlc > 0)
            {
                //can.printFrame(frame_read);
                //std::lock_guard<std::mutex> guard(data_write_mutex);
                {
                std::lock_guard<std::mutex> guard(data_read_mutex);
                memcpy(&data_read, &frame_read, 16);
                }
                mode = static_cast<SimulationMode>(data_read.mode);
                while (mode == SimulationMode::INACTIVE)
                {
                    can.canReadFrame(frame_read);
                    memcpy(&data_read, &frame_read, 16);
                    mode = static_cast<SimulationMode>(data_read.mode);
                }
                
                frame100=this->data_read; // Is this necessary? could I remove data_read?
            }
            if (mode == SimulationMode::OFF){
                std::cout << "Exit read thread\n";
                break;
            }
        }
    });
    read_thread.detach();
}

void message_handler::init_fr200(fr200 &frame200)
{
    frame200.rpm = 0;
    frame200.fuel = 0;
    frame200.telltale = 0;
    frame200.updatebit = 0;
    frame200.res0 = 0;
    frame200.res1 = 0;
    frame200.res2 = 0;
}

void message_handler::init_fr100(fr100 &frame100){
    frame100.mode=0;
    frame100.gearlever=0;
    frame100.startstop=0;
    frame100.updatebit=0;
    frame100.accelerator=0;
    frame100.brake=0;
    frame100.candlc=0;
    frame100.res0=0;
    frame100.res1=0;
    frame100.res2=0;
    frame100.res3=0;
    frame100.res4=0;
}