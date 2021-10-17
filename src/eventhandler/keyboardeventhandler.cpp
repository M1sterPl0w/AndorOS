#include <eventhandler/keyboardeventhandler.h>
#include <screen/console.h>

using namespace andoros;
using namespace andoros::eventhandler;
using namespace andoros::screen;

static Console Terminal;

KeyBoardEventHandler::KeyBoardEventHandler()
{

}

KeyBoardEventHandler::~KeyBoardEventHandler()
{

}

void KeyBoardEventHandler::OnKeyDown(const char* key)
{
    if(key == "del")
    {
        Terminal.Clear();
    } 
    else if(key == "back")
    {
        Terminal.Backspace();
    }
    else
    {
        Terminal.Write(key);
    }
}

void KeyBoardEventHandler::OnKeyUp(const char* key)
{
    // Do nothing here yet.
}
