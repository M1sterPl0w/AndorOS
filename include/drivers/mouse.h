#pragma once

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>
#include <eventhandler/mouseeventhandler.h>

namespace andoros
{
    namespace drivers 
    {
        class MouseDriver : public andoros::hardwarecommunication::InterruptHandler, public Driver
        {
            andoros::hardwarecommunication::Port8Bit dataport;
            andoros::hardwarecommunication::Port8Bit commandport;

            andoros::common::uint8_t buffer[3]; // 3 byte buffer
            andoros::common::uint8_t offset;
            andoros::common::uint8_t buttons; // Store last state button

            andoros::common::int8_t x, y;

            public:
                MouseDriver(andoros::hardwarecommunication::InterruptManager* manager, andoros::eventhandler::MouseEventHandler* handler);
                ~MouseDriver();

                andoros::eventhandler::MouseEventHandler* handler;

                virtual andoros::common::uint32_t HandleInterrupt(andoros::common::uint32_t esp);
                virtual void Activate();
        };
    };
};