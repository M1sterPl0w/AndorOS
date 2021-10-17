#include <drivers/keyboard.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <eventhandler/keyboardeventhandler.h>

using namespace andoros::common;
using namespace andoros::drivers;
using namespace andoros::hardwarecommunication;
using namespace andoros::eventhandler;

void write(const char* str);
void writeHex(uint8_t hex);
void clear();
void backSpace();

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyBoardEventHandler* handler)
: InterruptHandler(0x21, manager),
dataport(0x60), 
commandport(0x64)
{
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver()
{

}

void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
    {
        dataport.Read();
    }
    commandport.Write(0xAE); // Tells pic to start sending keyboard interrupt??? / I think it enable keyboard, 0xAD disbles it.
    commandport.Write(0x20); // Give us your current state
    uint8_t status = (dataport.Read() | 1) & ~0x10; // Set rightmost bit to 1; and also clear the fith bit?
    commandport.Write(0x60); // Tells pic to change current state;
    dataport.Write(status);

    // https://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
    dataport.Write(0xF4); // Also enables? keyboard; https://www.win.tue.nl/~aeb/linux/kbd/scancodes-12.html
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t keyStroke = dataport.Read();    

    if(handler == 0)
    {
        return esp;
    }

    if(keyStroke < 0x80) // after this are key release codes
    {
        switch(keyStroke)
        {
            case 0x04:
                handler->OnKeyDown("3");
                break;
            case 0x10:
                handler->OnKeyDown("q");
                break;
            case 0x11:
                handler->OnKeyDown("w");
                break;
            case 0x12:
                handler->OnKeyDown("e");
                break;
            case 0x13:
                handler->OnKeyDown("r");
                break;
            case 0x14:
                handler->OnKeyDown("t");
                break;
            case 0x15:
                handler->OnKeyDown("y");
                break;
            case 0x16:
                handler->OnKeyDown("u");
                break;
            case 0x17:
                handler->OnKeyDown("i");
                break;
            case 0x18:
                handler->OnKeyDown("o");
                break;
            case 0x19:
                handler->OnKeyDown("p");
                break;
            case 0x1E:
                handler->OnKeyDown("a");
                break;
            case 0x1F:
                handler->OnKeyDown("s");
                break;
            case 0x20:
                handler->OnKeyDown("d");
                break;
            case 0x21:
                handler->OnKeyDown("f");
                break;
            case 0x22:
                handler->OnKeyDown("g");
                break;
            case 0x23:
                handler->OnKeyDown("h");
                break;
            case 0x24:
                handler->OnKeyDown("j");
                break;
            case 0x25:
                handler->OnKeyDown("k");
                break;
            case 0x26:
                handler->OnKeyDown("l");
                break;
            case 0x2C:
                handler->OnKeyDown("z");
                break;
            case 0x2D:
                handler->OnKeyDown("x");
                break;
            case 0x2E:
                handler->OnKeyDown("c");
                break;
            case 0x2F:
                handler->OnKeyDown("v");
                break;
            case 0x30:
                handler->OnKeyDown("b");
                break;
            case 0x31:
                handler->OnKeyDown("n");
                break;
            case 0x32:
                handler->OnKeyDown("m");
                break;
            case 0x1C:
                handler->OnKeyDown("\n");
                break;  
            case 0x53:
                handler->OnKeyDown("del");
                break;
            case 0x0E:
                handler->OnKeyDown("back");
                break;
            case 0x39:
                handler->OnKeyDown(" ");
                break;
            case 0xFA:
            case 0x45: 
            case 0xC5:
            default:
                break;
        }
    }

    return esp;
}