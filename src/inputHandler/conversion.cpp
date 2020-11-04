
#include <iostream>
#include "inputHandlerFrame.h"
#include "share/socketcan_cpp.h"

class Conversion{

private:
    uint8_t brakePedalPos = 0;
    uint8_t accPedalPos = 0;
    StartButtonSts startButton = StartButtonSts::UNPRESSED;
    GearLeverPos gearLeverPos = GearLeverPos::PARK;


    void AccPedUp(){
        accPedalPos = accPedalPos + 10;
        if (accPedalPos > 100) { 
            accPedalPos = 100;
        }
    void AccPedDown(){      
        if (accPedalPos >10) { 
            accpedalPos = accpedalPos - 10;
        }
        else
        {
            accPeUdalPos = 0;
        } 
    }
    void BrakePedalUp(){
        brakePedalPos = 100;
    }
    void BrakePedDown(){
        brakePedalPos = 0;
    }
    void SetStartButton(){
        startButton = StartButtonSts::PRESSED;
    }
    void ReleaseStartButton(){
        Startbutton = StartButtonSts::UNPRESSED;
    }
    void SetSimulationMode(){
        //Do something
    }
    
    

public:
    Conversion(){
    // Nothin here yet
    }    
   void  getFrame(CanFrame &_frame){
       _fram.id = Frame_id;
       _frame.data[0] = frameData.frameDataArray[0];
       _frame.data[1] = frameData.frameDataArray[1];
       _frame.data[2] = frameData.frameDataArray[2];
       _frame.data[3] = frameData.frameDataArray[3];
       _frame.data[4] = frameData.frameDataArray[4];
       _frame.len = 8;

   }

    void SetKey(int _key){
        switch (_key)
            case 259: // Arrow UP
                AccKeyUp();
                break;
            case 258: //Arrow Down
                AccKeyDown();
                break;
            case 67: // s
                SetStartButton();
                break;
            default :  
                ReleaseStartButton();         
        }

    ~Conversion() {
            
    }
}
