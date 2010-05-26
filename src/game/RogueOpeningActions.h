#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastSapAction : public CastMeleeSpellAction
	{ 
	public: 
		CastSapAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "sap") {} 
	};

	class CastGarroteAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGarroteAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "garrote") {} 
	};


	class CastCheapShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastCheapShotAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "cheap shot") {} 
	};
	
}