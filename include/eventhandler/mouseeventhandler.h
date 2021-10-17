#pragma once

#include <common/types.h>

namespace andoros
{
    namespace eventhandler
    {
        class MouseEventHandler
        {
            andoros::common::int8_t x,y;

            public:
                MouseEventHandler();
                ~MouseEventHandler();

                virtual void OnMouseDown(andoros::common::uint8_t button);
                virtual void OnMouseUp(andoros::common::uint8_t button);
                virtual void OnMouseMove(int x, int y);   
        };
    }
}