#include "can_class.hpp"
#include "display_handler.hpp"
#include "display_class.hpp"
#include "frames.hpp"

void dataLayer::processInput(display &dHndl, const can_frame &frameGen){

        frame_100 fr100;
        frame_200 fr200;
        frame_300 fr300;

        if(frameGen.can_dlc > 0 && frameGen.can_id != 0)
        {
            switch(frameGen.can_id)
            {       
                case 100: //inpur handler
                    memcpy(fr100.get_frame_ptr(), &frameGen, sizeof(frameGen));   
                    dHndl.setValueAcc(fr100.get_accelerator());
                    dHndl.setValueBrake(fr100.get_brake());  
                    dHndl.setValueMode(fr100.get_mode());
                    dHndl.setValueStartStop(fr100.get_startstop());   
                    dHndl.setValueGearLever(fr100.get_gearlever()); 
                    dHndl.setValueInputUB(fr100.get_updatebit());                                                    
                    break;
                case 200: //ecm
                    memcpy(fr200.get_frame_ptr(), &frameGen, sizeof(frameGen));  
                    dHndl.setValueRpm(fr200.get_rpm());
                    dHndl.setValueFuelConsumptionAvg(fr200.get_fuelavg());
                    dHndl.setValueFuelConsumptionInst(fr200.get_fuelinst());                    
                    dHndl.setValueDriverInfo(fr200.get_driverinfo());
                    dHndl.setValueTelltale(fr200.get_telltale());
                    dHndl.setValueECMUB(fr200.get_updatebit());
                    break;
                case 300: //tcm
                    memcpy(fr300.get_frame_ptr(), &frameGen, sizeof(frameGen));  
                    dHndl.setValueVehicleSpeed(fr300.get_speed());
                    dHndl.setValueGearActual(fr300.get_gearactual());
                    dHndl.setValueGearRatio(fr300.get_gearratio());                    
                    dHndl.setValueTCMUB(fr300.get_updatebit());                                        
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "Can data read buffer is empty" << std::endl;
    return;
};