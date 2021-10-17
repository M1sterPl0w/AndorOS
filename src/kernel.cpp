#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

#include <eventhandler/keyboardeventhandler.h>

using namespace andoros::common;
using namespace andoros::drivers;
using namespace andoros::hardwarecommunication;
using namespace andoros::eventhandler;
using namespace andoros;

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(const void* multiboot_structure, unsigned int multiboot_magic)
{
    GlobalDescriptorTable gdt;
    InterruptManager interrupt(&gdt);

    DriverManager driverManager;

    KeyBoardEventHandler kbhandler;
    MouseEventHandler mouseHandler; 

    KeyboardDriver keyboardDriver(&interrupt, &kbhandler);
    driverManager.AddDriver(&keyboardDriver);

    MouseDriver mouseDriver(&interrupt, &mouseHandler);
    driverManager.AddDriver(&mouseDriver);
 
    driverManager.ActivateAll();
    
    interrupt.Activate();

    while(1)
    {
    }
}