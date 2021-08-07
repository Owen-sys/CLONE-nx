#pragma once
#include <switch.h>
#include <cstring>
#include <string>
#include <memory>
#include <vector>

using namespace::std;

void waitForVsync();

struct controlMsg
{
    // Joys between -32768 to 32767
    int frame;
    u64 keys;
    s32 joy_l_x;
    s32 joy_l_y;
    s32 joy_r_x;
    s32 joy_r_y;
};

class TasController
{
    private:

    HiddbgHdlsHandle HdlsHandle= {0};
    HiddbgHdlsDeviceInfo device = {0};
    HiddbgHdlsState state = {0};
    static char controllerCount;

    public:
    bool attachFlag = false;

    TasController(uint8_t deviceType, uint8_t bodyR, uint8_t bodyG, uint8_t bodyB, uint8_t buttonR, uint8_t buttonG, uint8_t buttonB);
    TasController();
    void pressA();
    void pressLR();
    void attach();
    void detach();

    void setInputNextFrame();
    void setMotion();

    void runMsg(std::shared_ptr<struct controlMsg> msg);
    void emptyMsg();  
};
