#pragma once

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>
#include <eventhandler/keyboardeventhandler.h>

namespace andoros
{
    namespace drivers 
    {
        class KeyboardDriver : public andoros::hardwarecommunication::InterruptHandler, public Driver
        {
            andoros::hardwarecommunication::Port8Bit dataport;
            andoros::hardwarecommunication::Port8Bit commandport;

            public:
                KeyboardDriver(andoros::hardwarecommunication::InterruptManager* manager, andoros::eventhandler::KeyBoardEventHandler* handler);
                ~KeyboardDriver();

                andoros::eventhandler::KeyBoardEventHandler* handler;

                virtual andoros::common::uint32_t HandleInterrupt(andoros::common::uint32_t esp);
                virtual void Activate();
        };
    };
};

