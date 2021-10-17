#pragma once

#include <common/types.h>

namespace andoros
{
    namespace screen
    {
        class Console
        {
            public:
                Console();
                ~Console();

                void Write(const char* str);
                void Write(andoros::common::uint8_t hexValue);
                void Write(andoros::common::uint16_t hexValue);
                void Write(const char* text, andoros::common::int8_t xLocation, andoros::common::int8_t yLocation);
                void Backspace();
                void Clear();

                void InitMouse(andoros::common::int8_t x, andoros::common::int8_t y);
                void UpdateMouse(andoros::common::int8_t x, andoros::common::int8_t y);

            private:
                unsigned short* VideoMemory;
                andoros::common::uint8_t x = 0;
                andoros::common::uint8_t y = 0;
        };
    }
}