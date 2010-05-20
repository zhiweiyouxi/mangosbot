#pragma once

#include "GenericActions.h"

namespace ai {
	class CastBearFormAction : public CastBuffSpellAction { 
	public: 
		CastBearFormAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "bear form") {} 

        virtual bool isPossible() {
			return CastBuffSpellAction::isPossible() && !spellManager->HasAura("dire bear form", GetTarget());
		}
        virtual bool isUseful() {
			return CastBuffSpellAction::isUseful() && !spellManager->HasAura("dire bear form", GetTarget());
		}
	};

	class CastDireBearFormAction : public CastBuffSpellAction { 
	public: 
		CastDireBearFormAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "dire bear form") {} 
        
        virtual NextAction** getAlternatives() {
			return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
		}
	};

	class CastCatFormAction : public CastBuffSpellAction { 
	public: 
		CastCatFormAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "cat form") {} 
	};

	class CastMoonkinFormAction : public CastBuffSpellAction { 
	public: 
		CastMoonkinFormAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "moonkin form") {} 
	};

	class CastCasterFormAction : public CastBuffSpellAction { 
	public: 
		CastCasterFormAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "caster form") {} 

		virtual bool isUseful() {
			return spellManager->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", 
				"flight form", "swift flight form", "moonkin form", NULL); 
		}
		virtual bool isPossible() { return TRUE; }
		
		virtual bool ExecuteResult();
	};

}