#pragma once

namespace ai
{
    class AiManagerRegistryAware 
    {
    public:
        AiManagerRegistryAware(AiManagerRegistry* const ai) { this->ai = ai; }

    protected:
        AiManagerRegistry* ai;
    };
}