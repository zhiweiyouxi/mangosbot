#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastEviscerateAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastEviscerateAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "eviscerate") {} 
	};

	class CastSliceAndDiceAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSliceAndDiceAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "slice and dice") {} 
	};

	class CastExposeArmorAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastExposeArmorAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "expose armor") {} 
	};

	class CastRuptureAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastRuptureAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "rupture") {} 
	};
	
	class CastKidneyShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastKidneyShotAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "kidney shot") {} 
	};
	
}