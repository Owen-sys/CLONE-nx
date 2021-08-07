#include "controller.hpp"

TasController::TasController(uint8_t deviceType, uint8_t bodyR, uint8_t bodyG, uint8_t bodyB, uint8_t buttonR, uint8_t buttonG, uint8_t buttonB)
{
    device.deviceType = deviceType;

    // Set the interface type
    device.npadInterfaceType = HidNpadInterfaceType_Bluetooth;

    // Colors
    device.singleColorBody = RGBA8_MAXALPHA(bodyR, bodyG, bodyB);
    device.singleColorButtons = RGBA8_MAXALPHA(buttonR, buttonG, buttonB);
    device.colorLeftGrip = device.singleColorBody;
    device.colorRightGrip = device.singleColorBody;

    // Charge is max
    state.battery_level = 4;

    // Set Buttons and analog_stick_
    state.buttons = 0;
    state.analog_stick_l.x += 0x10;
    if (state.analog_stick_l.x > JOYSTICK_MAX) state.analog_stick_l.x = JOYSTICK_MIN;
    state.analog_stick_r.y -= 0x10;
    if (state.analog_stick_r.y < JOYSTICK_MIN) state.analog_stick_r.y = JOYSTICK_MAX;
}

void TasController::attach()
{
    if(attachFlag) return;

    // Attach the controller
    Result rc = hiddbgAttachHdlsVirtualDevice(&HdlsHandle, &device);
    if (R_FAILED(rc))
        fatalThrow(rc);

    // Update the state
    rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    attachFlag = true;
}

void TasController::detach()
{
    if(!attachFlag) return;

    // Detatch Controller
    Result rc = hiddbgDetachHdlsVirtualDevice(HdlsHandle);
    if (R_FAILED(rc))
        fatalThrow(rc);

    attachFlag = false;
}

//This also resets the state of the controller after pressing so only to be used when pairing and not running a script
void TasController::pressLR()
{
    emptyMsg();
    state.buttons |= HidNpadButton_L;
    state.buttons |= HidNpadButton_R;
    setInputNextFrame();
}

void TasController::setInputNextFrame()
{
    Result rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalThrow(rc);
}

void TasController::runMsg(std::shared_ptr<struct controlMsg> msg)
{
    state.buttons = msg->keys;
    state.analog_stick_l.x = msg->joy_l_x;
    state.analog_stick_l.y = msg->joy_l_y;
    state.analog_stick_r.x = msg->joy_r_x;
    state.analog_stick_r.y = msg->joy_r_y;
}
void TasController::emptyMsg()
{
    state.buttons = 0;
    state.analog_stick_l.x = 0;
    state.analog_stick_l.y = 0;
    state.analog_stick_r.x = 0;
    state.analog_stick_r.y = 0;
}
