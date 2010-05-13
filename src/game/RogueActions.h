#pragma once

#include "GenericActions.h"
#include "RogueComboActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"

namespace ai
{
	class CastEvasionAction : public CastSpellAction 
	{ 
	public: 
		CastEvasionAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "evasion") {} 
	};

	class CastSprintAction : public CastSpellAction 
	{ 
	public: 
		CastSprintAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "sprint") {} 
	};

	class CastKickAction : public CastSpellAction 
	{ 
	public: 
		CastKickAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "kick") {} 
	};

	class CastFeintAction : public CastSpellAction 
	{ 
	public: 
		CastFeintAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "feint") {} 
	};

	class CastDismantleAction : public CastSpellAction 
	{ 
	public: 
		CastDismantleAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "dismantle") {} 
	};
	
	class CastDistractAction : public CastSpellAction 
	{ 
	public: 
		CastDistractAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "distract") {} 
	};
	
	class CastVanishAction : public CastSpellAction 
	{ 
	public: 
		CastVanishAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "vanish") {} 
	};

	class CastBlindAction : public CastSpellAction 
	{ 
	public: 
		CastBlindAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "blind") {} 
	};
	
	
	class CastRiposteAction : public CastSpellAction 
	{ 
	public: 
		CastRiposteAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "riposte") {} 
	};

	class CastBladeFlurryAction : public CastSpellAction 
	{ 
	public: 
		CastBladeFlurryAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "blade flurry") {} 
	};

	class CastAdrenalineRushAction : public CastSpellAction 
	{ 
	public: 
		CastAdrenalineRushAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "adrenaline rush") {} 
	};

	class CastKillingSpreeAction : public CastSpellAction 
	{ 
	public: 
		CastKillingSpreeAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "killing spree") {} 
	};

}