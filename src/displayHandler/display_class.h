#ifndef _DISPLAY_CLASS_H_
#define _DISPLAY_CLASS_H_ 
class displayHandler{

    public:
        displayHandler(){};
        void initDisplay();
        void update();
        void setValueAcc(int _acc){ accelerator = _acc; };
        void setValueRpm(int _rpm){  rpm = _rpm; };
        void setValueBrake(int _brake){  brake = _brake; };        
        ~displayHandler(){};
    private:
        int accelerator = 0;
        int rpm = 0;
        int brake = 0;        

};

#endif