
#include "conversion.hpp"
#include "inputHandlerFrame.h"


void Conversion::AccPedUp(){
    frameData.DataSet.accPedal = frameData.DataSet.AccPedal + 10;
    if (frameData.DataSet.accPedal > 100) { 
        frameData.DataSet.accPedal = 100;
    }
    frameData.DataSet.accPedal = 100;
}
void Conversion::AccPedDown(){      
    if (frameData.DataSet.accPedal >10) { 
        frameData.DataSet.accPedal = frameData.DataSet.accPedal - 10;
    }
    else {
        frameData.DataSet.accPedal = 0;
    } 
}
void Conversion::BrakePedalUp(){
    frameData.DataSet.brakePedal = 100;
}
void Conversion::BrakePedDown(){
    frameData.DataSet.brakePedal = 0; 
}
void Conversion::SetStartButton(){
   // frameData.DataSet.startButton = StartButtonSts::PRESSED;
}
void Conversion::ReleaseStartButton(){
  //  frameData.DataSet.startButton = StartButtonSts::UNPRESSED;
}
void Conversion::SetSimulationMode(){
    //Do something
}

// This is defintion in can.h
//struct can_frame {
//	canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
//	__u8    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
//	__u8    __pad;   /* padding */
//	__u8    __res0;  /* reserved / padding */
//	__u8    __res1;  /* reserved / padding */
//	__u8    data[CAN_MAX_DLEN] __attribute__((aligned(8)));

void  Conversion::getFrame(can_frame &_frame){
    
    _frame.can_id = Frame_id;
    _frame.data[0] = frameData.frameDataArray[0];
    _frame.data[1] = frameData.frameDataArray[1];
    _frame.data[2] = frameData.frameDataArray[2];
    _frame.data[3] = frameData.frameDataArray[3];
    _frame.data[4] = frameData.frameDataArray[4];
    _frame.can_dlc = 8;

}

void Conversion::SetKey(int _key){
    switch (_key){
        case 259: // Arrow UP
            AccPedUp();
            break;
        case 258: //Arrow Down
            AccPedDown();
            break;
        case 115: // s
            SetStartButton();
            break;
        case 99: //
            BrakePedalUp();
        default :  
            ReleaseStartButton();         
    }
}
Conversion::~Conversion(){}
