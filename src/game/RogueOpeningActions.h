#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastSapAction : public CastMeleeSpellAction
	{ 
	public: 
		CastSapAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "sap") {} 
	};

	class CastGarroteAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGarroteAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "garrote") {} 
	};


	class CastCheapShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastCheapShotAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "cheap shot") {} 
	};
	
}