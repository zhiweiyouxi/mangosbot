#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastEviscerateAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastEviscerateAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "eviscerate") {} 
	};

	class CastSliceAndDiceAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSliceAndDiceAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "slice and dice") {} 
	};

	class CastExposeArmorAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastExposeArmorAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "expose armor") {} 
	};

	class CastRuptureAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastRuptureAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "rupture") {} 
	};
	
	class CastKidneyShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastKidneyShotAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "kidney shot") {} 
	};
	
}