#pragma once
#include "GenericTriggers.h"

namespace ai {
    class MarkOfTheWildOnPartyTrigger : public BuffOnPartyTrigger { 
    public: 
        MarkOfTheWildOnPartyTrigger(PlayerbotAIFacade* const ai) : BuffOnPartyTrigger(ai, "mark of the wild") {}  
    };

    class MarkOfTheWildTrigger : public BuffTrigger { 
    public: 
        MarkOfTheWildTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "mark of the wild") {} 
    };

    class ThornsTrigger : public BuffTrigger { 
    public: 
        ThornsTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "thorns") {} 
    };

    class RakeTrigger : public DebuffTrigger 
    { 
    public: 
        RakeTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "rake") {} 
    };

    class InsectSwarmTrigger : public DebuffTrigger 
    { 
    public: 
        InsectSwarmTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "insect swarm") {} 
    };

    class MoonfireTrigger : public DebuffTrigger 
    { 
    public: 
        MoonfireTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "moonfire") {} 
    };

    class FaerieFireTrigger : public DebuffTrigger 
    { 
    public: 
        FaerieFireTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "faerie fire") {} 
    };
	
}