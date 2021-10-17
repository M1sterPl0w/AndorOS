#include <screen/console.h>
#include <common/types.h>

using namespace andoros;
using namespace andoros::common;
using namespace andoros::screen;

static Console Terminal;

Console::Console()
{
    VideoMemory = (unsigned short*)0xb8000;
}

Console::~Console()
{
}

void Console::Write(const char* str)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                y++;
                x = 0;
                break;
            default: 
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xF400 | str[i]);
                x++;
                break;
        }

        if(x >= 80)
        {
            y++;
            x = 0;
        }

        if(y >= 25)
        {
            Clear();
        }        
    }    
}

void Console::Write(uint8_t hexValue)
{
    char foo[] = "0x00";
    char hex[] = "0123456789ABCDEF";
    foo[2] = hex[(hexValue >> 4) & 0xF];
    foo[3] = hex[hexValue & 0xF];

    Write(foo);
}

void Console::Write(uint16_t hexValue)
{
    char foo[] = "0x0000";
    char hex[] = "0123456789ABCDEF";

    foo[2] = hex[(hexValue >> 12) & 0xF];
    foo[3] = hex[(hexValue >> 8) & 0xF];
    foo[4] = hex[(hexValue >> 4) & 0xF];
    foo[5] = hex[hexValue & 0xF];

    Write(foo);
}

void Console::Write(const char* str, int8_t xLocation, int8_t yLocation)
{
    x = xLocation;
    y = yLocation;
    Write(str);
}

void Console::Backspace()
{
    if(x == 0 && y == 3)
    {
        return;
    }

    if(x == 0)
    {
        y--;
        for(uint8_t i = 80; i > 0; i--)
        {      
            if((VideoMemory[80*y+i] | 0xFF00) != 0xFF20)      
            {
                x = i;    
                break;
            }
        }
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00 | ' ');
        return;
    }

    x--;
    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00 | ' ');
}

void Console::Clear()
{
    for(y = 3; y < 25; y++)
    {
        for(x = 0; x < 80; x++)
        {
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00 | ' ');
        }
    }

    x = 0;
    y = 3;
}

void Console::InitMouse(int8_t x, int8_t y)
{
    VideoMemory[80*12+40] = ((VideoMemory[80*12+40] & 0xF000) >> 4)
                        | ((VideoMemory[80*12+40] & 0x0F00) << 4)                              
                        | ((VideoMemory[80*12+40] & 0x00FF));
}

void Console::UpdateMouse(int8_t x, int8_t y)
{
    VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                | ((VideoMemory[80*y+x] & 0x0F00) << 4)
                | ((VideoMemory[80*y+x] & 0x00FF));
}