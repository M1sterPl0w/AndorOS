#include <eventhandler/mouseeventhandler.h>
#include <common/types.h>
#include <screen/console.h>

using namespace andoros::eventhandler;
using namespace andoros::common;
using namespace andoros::screen;

static Console Terminal;

MouseEventHandler::MouseEventHandler()
{
    x = 12;
    y = 40;
}

MouseEventHandler::~MouseEventHandler()
{
}

void MouseEventHandler::OnMouseUp(uint8_t button)
{
    // Klik, zou het moeten doen
}

void MouseEventHandler::OnMouseDown(uint8_t button)
{
    // Klik, zou het moeten doen
}

void MouseEventHandler::OnMouseMove(int xOffset, int yOffset)
{
    Terminal.UpdateMouse(x, y);

    x += xOffset;
    if(x < 0) x = 0;
    if(x >= 80) x = 79;

    y -= yOffset; 
    if(y < 0) y = 0;
    if( y >= 25) y = 24;

    Terminal.UpdateMouse(x, y);
}