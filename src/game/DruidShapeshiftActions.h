#pragma once

#include "GenericActions.h"

namespace ai {
	class CastBearFormAction : public CastAuraSpellAction { 
	public: 
		CastBearFormAction(PlayerbotAIFacade* const ai) : CastAuraSpellAction(ai, "bear form") {} 

        virtual bool isPossible() {
			return CastAuraSpellAction::isPossible() && !ai->HasAura("dire bear form");
		}
        virtual bool isUseful() {
			return CastAuraSpellAction::isUseful() && !ai->HasAura("dire bear form");
		}
	};

	class CastDireBearFormAction : public CastAuraSpellAction { 
	public: 
		CastDireBearFormAction(PlayerbotAIFacade* const ai) : CastAuraSpellAction(ai, "dire bear form") {} 
        
        virtual NextAction** getAlternatives() {
			return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
		}
	};

	class CastMoonkinFormAction : public CastAuraSpellAction { 
	public: 
		CastMoonkinFormAction(PlayerbotAIFacade* const ai) : CastAuraSpellAction(ai, "moonkin form") {} 
	};

	class CastCasterFormAction : public CastSpellAction { 
	public: 
		CastCasterFormAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "caster form") {} 

		virtual bool isUseful() {
			return ai->HasAnyAuraOf("dire bear form", "bear form", "cat form", "travel form", "aquatic form", 
				"flight form", "swift flight form", "moonkin form", NULL); 
		}
		virtual bool isPossible() { return TRUE; }
		
		virtual bool ExecuteResult();
	};

}