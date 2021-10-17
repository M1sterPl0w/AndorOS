#pragma once

#include <common/types.h>

namespace andoros
{
    class GlobalDescriptorTable 
    {
        public:
            class SegmentDescriptor
            {   
                private: 
                    andoros::common::uint16_t limit_lo;
                    andoros::common::uint16_t base_lo;
                    andoros::common::uint8_t base_hi;
                    andoros::common::uint8_t type;
                    andoros::common::uint8_t flags_limit_hi;
                    andoros::common::uint8_t base_vhi;
                public:
                    SegmentDescriptor(andoros::common::uint32_t base, 
                                    andoros::common::uint32_t limit, 
                                    andoros::common::uint8_t type);
                    andoros::common::uint32_t Base();
                    andoros::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;

            // BAD for security, we are going to have one big codesegement and one large datasegment!!!!
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector; 

        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            andoros::common::uint16_t CodeSegmentSelector();
            andoros::common::uint16_t DataSegmentSelector();
    };
};