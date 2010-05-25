#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastDemonSkinAction : public CastBuffSpellAction {
	public:
		CastDemonSkinAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "demon skin") {}
	};

	class CastDemonArmorAction : public CastBuffSpellAction 
	{
	public:
		CastDemonArmorAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "demon armor") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

	class CastImmolateAction : public CastDebuffSpellAction 
	{
	public:
		CastImmolateAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "immolate") {}
	};

	class CastDrainSoulAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainSoulAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "drain soul") {}
		virtual bool isUseful() 
		{
			return ai->GetInventoryManager()->GetItemCount("soul shard") < 2;
		}
	};

	class CastDrainManaAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainManaAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "drain mana") {}
	};

	class CastDrainLifeAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainLifeAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "drain life") {}
	};

	class CastCurseOfAgonyAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfAgonyAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "curse of agony") {}
	};

	class CastCurseOfWeaknessAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfWeaknessAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "curse of weakness") {}
	};

	class CastCorruptionAction : public CastDebuffSpellAction 
	{
	public:
		CastCorruptionAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "corruption") {}
	};

	
	class CastSummonVoidwalkerAction : public CastBuffSpellAction 
	{
	public:
		CastSummonVoidwalkerAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "summon voidwalker") {}
	};

	class CastSummonImpAction : public CastBuffSpellAction 
	{
	public:
		CastSummonImpAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "summon imp") {}
	};

	class CastCreateHealthstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateHealthstoneAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "create healthstone") {}
	};

	class CastCreateFirestoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateFirestoneAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "create firestone") {}
	};

	class CastCreateSpellstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateSpellstoneAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "create spellstone") {}
	};
}