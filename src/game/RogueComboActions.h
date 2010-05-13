#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastSinisterStrikeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSinisterStrikeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "sinister strike") {} 
	};

	class CastGougeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGougeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "gouge") {} 
	};

}