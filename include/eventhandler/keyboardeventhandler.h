#pragma once

#include <common/types.h>

namespace andoros
{
    namespace eventhandler
    {
        class KeyBoardEventHandler
        {
            public:
                KeyBoardEventHandler();
                ~KeyBoardEventHandler();

                virtual void OnKeyDown(const char * key);
                virtual void OnKeyUp(const char * key);
        };
    }
}