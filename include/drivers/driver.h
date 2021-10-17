#pragma once

namespace andoros
{
    namespace drivers
    {
        class Driver
        {
            public: 
                Driver();
                ~Driver();

                virtual void Activate();
                virtual void Deactivate();
                virtual int Reset();
        };

        class DriverManager
        {
            private:
                Driver* drivers[255]; // should be done differently
                int numDrivers;

            public:
                void AddDriver(Driver* driver);
                void ActivateAll();
                DriverManager();
                ~DriverManager();
        };
    };
};