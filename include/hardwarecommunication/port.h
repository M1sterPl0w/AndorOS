#pragma once

#include <common/types.h>

namespace andoros
{
  namespace hardwarecommunication
  {
    class Port
    {
      protected:  
        andoros::common::uint16_t portnumber; // is always 16-bit  
        Port(andoros::common::uint16_t portnumber);
        ~Port();
    };
 
    class Port8Bit : public Port
    {
      public:  
        Port8Bit(andoros::common::uint16_t portnumber);
        ~Port8Bit();
        virtual void Write(andoros::common::uint8_t data);
        virtual andoros::common::uint8_t Read();
    };

    class Port8BitSlow : public Port8Bit
    {
      public:  
        Port8BitSlow(andoros::common::uint16_t portnumber);
        ~Port8BitSlow();
        virtual void Write(andoros::common::uint8_t data);
    };


    class Port16Bit : public Port
    {
      public:  
        Port16Bit(andoros::common::uint16_t portnumber);
        ~Port16Bit();
        virtual void Write(andoros::common::uint16_t data);
        virtual andoros::common::uint16_t Read();
    };

    class Port32Bit : public Port
    {
      public:  
        Port32Bit(andoros::common::uint16_t portnumber);
        ~Port32Bit();
        
        virtual void Write(andoros::common::uint32_t data);
        virtual andoros::common::uint32_t Read();
    };
  };
};

