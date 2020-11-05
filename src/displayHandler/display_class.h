#ifndef _DISPLAY_CLASS_H_
#define _DISPLAY_CLASS_H_ 
class displayHandler{

    public:
        displayHandler(){};
        void initDisplay();
        void update();
        void setValueAcc(int _acc){ accelerator = _acc; };
        void setValueRpm(int _rpm){  rpm = _rpm; };
        ~displayHandler(){};
    private:
        int accelerator = 0;
        int rpm = 0;

};

#endif