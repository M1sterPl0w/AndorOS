#pragma once

#include <gdt.h>
#include <common/types.h>
#include <hardwarecommunication/port.h>

namespace andoros
{
    namespace hardwarecommunication
    {
        class InterruptManager;

        class InterruptHandler
        {
        protected: 
            andoros::common::uint8_t interruptNumber;
            InterruptManager* interruptManager;

            InterruptHandler(andoros::common::uint8_t interruptNumber, InterruptManager* interruptManager);
            ~InterruptHandler();
    
        public:
            virtual andoros::common::uint32_t HandleInterrupt(andoros::common::uint32_t esp);

        };

        class InterruptManager
        {
            friend class InterruptHandler;
            protected:
                static InterruptManager* ActiveInterruptManager;

                InterruptHandler* handlers[256];

                struct GateDescriptor
                {
                    andoros::common::uint16_t handlerAddressLowBits;
                    andoros::common::uint16_t gdt_codeSegmentSelector; //the offset of the global descriptor table
                    andoros::common::uint8_t reserved; // reserved byte
                    andoros::common::uint8_t access;
                    andoros::common::uint16_t handlerAddressHighBits;
                } __attribute__((packed));

                static GateDescriptor interruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer
                {
                    andoros::common::uint16_t size;
                    andoros::common::uint32_t base;

                } __attribute__((packed));

                static void SetInterruptDescriptorTableEntry(
                    andoros::common::uint8_t interruptNumber, 
                    andoros::common::uint16_t  codeSegmentSelectorOffset,
                    void (*handler)(),
                    andoros::common::uint8_t DescriptorPrivilegeLevel,
                    andoros::common::uint8_t DescriptorType
                );

                andoros::hardwarecommunication::Port8BitSlow picMasterCommand;
                andoros::hardwarecommunication::Port8BitSlow picMasterData;
                andoros::hardwarecommunication::Port8BitSlow picSlaveCommand;
                andoros::hardwarecommunication::Port8BitSlow picSlaveData;

            public:
                InterruptManager(GlobalDescriptorTable* gdt);
                ~InterruptManager();

                void Activate();
                void Deactivate();

                static andoros::common::uint32_t HandleInterrupt(andoros::common::uint8_t interruptNumber, andoros::common::uint32_t currentStackPointer);
                andoros::common::uint32_t DoHandleInterrupt(andoros::common::uint8_t interruptNumber, andoros::common::uint32_t currentStackPointer);

                static void InterruptIgnore();
                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();
                static void HandleInterruptRequest0x0C();
        };
    };
};

