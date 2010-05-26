#pragma once

#include "GenericActions.h"
#include "RogueComboActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"

namespace ai
{
	class CastEvasionAction : public CastBuffSpellAction 
	{ 
	public: 
		CastEvasionAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "evasion") {} 
	};

	class CastSprintAction : public CastBuffSpellAction 
	{ 
	public: 
		CastSprintAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "sprint") {} 
	};

	class CastKickAction : public CastSpellAction 
	{ 
	public: 
		CastKickAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "kick") {} 
	};

	class CastFeintAction : public CastBuffSpellAction 
	{ 
	public: 
		CastFeintAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "feint") {} 
	};

	class CastDismantleAction : public CastSpellAction 
	{ 
	public: 
		CastDismantleAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "dismantle") {} 
	};
	
	class CastDistractAction : public CastSpellAction 
	{ 
	public: 
		CastDistractAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "distract") {} 
	};
	
	class CastVanishAction : public CastBuffSpellAction 
	{ 
	public: 
		CastVanishAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "vanish") {} 
	};

	class CastBlindAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastBlindAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "blind") {} 
	};
	
	
	class CastRiposteAction : public CastSpellAction 
	{ 
	public: 
		CastRiposteAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "riposte") {} 
	};

	class CastBladeFlurryAction : public CastBuffSpellAction 
	{ 
	public: 
		CastBladeFlurryAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "blade flurry") {} 
	};

	class CastAdrenalineRushAction : public CastBuffSpellAction 
	{ 
	public: 
		CastAdrenalineRushAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "adrenaline rush") {} 
	};

	class CastKillingSpreeAction : public CastBuffSpellAction 
	{ 
	public: 
		CastKillingSpreeAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "killing spree") {} 
	};

}