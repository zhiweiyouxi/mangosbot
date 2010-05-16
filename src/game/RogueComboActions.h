#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastSinisterStrikeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSinisterStrikeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "sinister strike") {} 
	};

    class CastMutilateAction : public CastMeleeSpellAction 
    { 
    public: 
        CastMutilateAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "mutilate") {} 
    };

	class CastGougeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGougeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "gouge") {} 
	};

}