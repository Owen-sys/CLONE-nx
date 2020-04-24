// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Include headers from other parts of the program
#include "controller.hpp"

// Create VSync event
Event vsync_event;

// Initialize frame counter variable
int frameCount = 0;

extern "C"
{
    // Sysmodules should not use applet*.
    u32 __nx_applet_type = AppletType_None;

    // Adjust size as needed.
    #define INNER_HEAP_SIZE 0x80000
    size_t nx_inner_heap_size = INNER_HEAP_SIZE;
    char   nx_inner_heap[INNER_HEAP_SIZE];

    void __libnx_init_time(void);
    void __libnx_initheap(void);
    void __appInit(void);
    void __appExit(void);
}

void __libnx_initheap(void)
{
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	// Newlib
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char*)addr;
	fake_heap_end   = (char*)addr + size;
}

// Init/exit services, update as needed.
void __attribute__((weak)) __appInit(void)
{
    Result rc;

    // Initialize default services.
    rc = smInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    rc = setsysInitialize();
    if (R_SUCCEEDED(rc)) {
        SetSysFirmwareVersion fw;
        rc = setsysGetFirmwareVersion(&fw);
        if (R_SUCCEEDED(rc))
            hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
        setsysExit();
    }

    // HID
    rc = hidInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_HID));

    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();

    rc = hiddbgInitialize();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // vsync
    rc = viInitialize(ViServiceType_System);
    if(R_FAILED(rc))
        fatalThrow(rc);
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void)
{
    // Cleanup default services.
    fsdevUnmountAll();
    fsExit();
    hidExit();
    smExit();
}

void frameIncrement(void* _)
{
    while(true)
    {
        // Wait for a new frame...
        Result rc = eventWait(&vsync_event, UINT64_MAX);
        if(R_FAILED(rc))
            fatalThrow(rc);

        // ... Then increment the counter
        ++frameCount;
    }
}

class file_exception : public std::exception
{
    virtual const char* what() const throw()
    {
        return "File unopenable";
    }
} f_ex;

// Main program entrypoint
int main(int argc, char* argv[])
{
    // Init other services
    ViDisplay disp;
    Result rc = viOpenDefaultDisplay(&disp);
    if(R_FAILED(rc))
        fatalThrow(rc);

    rc = viGetDisplayVsyncEvent(&disp, &vsync_event);
    if(R_FAILED(rc))
        fatalThrow(rc);

    // Initialization code can go here.
    // Skyline handle

    TasController *controller = new TasController(HidDeviceType_FullKey3, 0, 0, 0, 0, 0, 0);

    // Attach Work Buffer
    rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // Create new thread for counting frames
    // Commented out as it was stealing vsync events from the script runner
    /*
    Thread countThread;
    rc = threadCreate(&countThread, frameIncrement, NULL, 0x4000, 49, 3);
    if(R_FAILED(rc))
        fatalThrow(rc);
    rc = threadStart(&countThread);
    if(R_FAILED(rc))
        fatalThrow(rc);
    */

    // Your code / main loop goes here.
    while(true)
    {
        hidScanInput();

        if(hidKeyboardDown(KBD_Q))
        {
            controller->pressLR();
        }

        if(hidKeyboardDown(KBD_W))
        {
            controller->pressA();
        }

        if(hidKeyboardDown(KBD_1))
        {

            controller->attach();
        }

        if(hidKeyboardDown(KBD_MINUS))
        {
            controller->detach();
        }

        svcSleepThread(6250000);
    }

    rc = hiddbgReleaseHdlsWorkBuffer();

    hiddbgExit();
	
    return 0;
}
