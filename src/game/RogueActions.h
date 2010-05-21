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
		CastEvasionAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "evasion") {} 
	};

	class CastSprintAction : public CastBuffSpellAction 
	{ 
	public: 
		CastSprintAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "sprint") {} 
	};

	class CastKickAction : public CastSpellAction 
	{ 
	public: 
		CastKickAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "kick") {} 
	};

	class CastFeintAction : public CastBuffSpellAction 
	{ 
	public: 
		CastFeintAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "feint") {} 
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
	
	class CastVanishAction : public CastBuffSpellAction 
	{ 
	public: 
		CastVanishAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "vanish") {} 
	};

	class CastBlindAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastBlindAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "blind") {} 
	};
	
	
	class CastRiposteAction : public CastSpellAction 
	{ 
	public: 
		CastRiposteAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "riposte") {} 
	};

	class CastBladeFlurryAction : public CastBuffSpellAction 
	{ 
	public: 
		CastBladeFlurryAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "blade flurry") {} 
	};

	class CastAdrenalineRushAction : public CastBuffSpellAction 
	{ 
	public: 
		CastAdrenalineRushAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "adrenaline rush") {} 
	};

	class CastKillingSpreeAction : public CastBuffSpellAction 
	{ 
	public: 
		CastKillingSpreeAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "killing spree") {} 
	};

}