#pragma once

namespace Enternity
{
    class IRuntimeModule
    {
        public:
            virtual ~IRuntimeModule() = default;

            virtual bool Initialize() = 0;
            virtual void Finalize() = 0;
            virtual void Tick() = 0; 
    };
}