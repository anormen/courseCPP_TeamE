#ifndef _CAN_CLASS_H_
#define _CAN_CLASS_H_ 

int canInit(void);
int canReadFrame(const int, can_frame&);
int canWriteFrame(const int, can_frame&);
const char *ifname = "vcan0";
const int cycletime = 250; //cycletime for can send

#endif