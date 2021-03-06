#include <common/types.h>
#include <drivers/mouse.h>
#include <hardwarecommunication/interrupts.h>
#include <eventhandler/mouseeventhandler.h>

using namespace andoros::common;
using namespace andoros::drivers;
using namespace andoros::hardwarecommunication;
using namespace andoros::eventhandler;

MouseDriver::MouseDriver(InterruptManager* manager, MouseEventHandler* handler)
    :InterruptHandler(0x2C, manager),
    dataport(0x60),
    commandport(0x64)
{
    this->handler = handler;
}

MouseDriver::~MouseDriver()
{
}

void MouseDriver::Activate()
{    
    offset = 0;
    buttons = 0;
    
    commandport.Write(0xA8);
    commandport.Write(0x20);
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60);
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

// buffer 1 is movement on X
// buffer 2 is movement on Y
// But in the opposite direction?
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{   
    uint8_t status = commandport.Read();
    if(!(status & 0x20))
    {
        return esp;
    }

    buffer[offset] = dataport.Read();

    if(handler == 0)
    {
        return esp;
    }

    offset = (offset + 1) % 3;

    if(offset == 0)
    {
        if(buffer[1] != 0 || buffer[2] != 0)
        {
            handler->OnMouseMove(buffer[1], buffer[2]);
        }

        for(uint8_t i = 0; i < 3; i++)
        {
            if((buffer[0] & (0x01 << i)) != buttons & ((0x01 << i)))
            {
                if(buttons & (0x1<<i))
                {
                    handler->OnMouseUp(i+1);
                }
                else
                {
                    handler->OnMouseDown(i+1);
                }                   
            }
            buttons = buffer[0];
        }
    }

    return esp;
}