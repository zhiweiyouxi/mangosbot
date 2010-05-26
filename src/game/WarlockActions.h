#pragma once

#include "GenericActions.h"

namespace ai
{
	class CastDemonSkinAction : public CastBuffSpellAction {
	public:
		CastDemonSkinAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "demon skin") {}
	};

	class CastDemonArmorAction : public CastBuffSpellAction 
	{
	public:
		CastDemonArmorAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "demon armor") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

	class CastImmolateAction : public CastDebuffSpellAction 
	{
	public:
		CastImmolateAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "immolate") {}
	};

	class CastDrainSoulAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainSoulAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "drain soul") {}
		virtual bool isUseful() 
		{
			return ai->GetInventoryManager()->GetItemCount("soul shard") < 2;
		}
	};

	class CastDrainManaAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainManaAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "drain mana") {}
	};

	class CastDrainLifeAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainLifeAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "drain life") {}
	};

	class CastCurseOfAgonyAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfAgonyAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "curse of agony") {}
	};

	class CastCurseOfWeaknessAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfWeaknessAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "curse of weakness") {}
	};

	class CastCorruptionAction : public CastDebuffSpellAction 
	{
	public:
		CastCorruptionAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "corruption") {}
	};

	
	class CastSummonVoidwalkerAction : public CastBuffSpellAction 
	{
	public:
		CastSummonVoidwalkerAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "summon voidwalker") {}
	};

	class CastSummonImpAction : public CastBuffSpellAction 
	{
	public:
		CastSummonImpAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "summon imp") {}
	};

	class CastCreateHealthstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateHealthstoneAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "create healthstone") {}
	};

	class CastCreateFirestoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateFirestoneAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "create firestone") {}
	};

	class CastCreateSpellstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateSpellstoneAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "create spellstone") {}
	};
}