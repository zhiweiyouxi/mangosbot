#pragma once

namespace ai {
	class CastFeralChargeCatAction : public CastReachTargetSpellAction 
	{
	public:
		CastFeralChargeCatAction(AiManagerRegistry* const ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
	};

	class CastCatSpellAction : public CastSpellAction 
	{
	public:
		CastCatSpellAction(AiManagerRegistry* const ai, const char* spell) : CastSpellAction(ai, spell) {}
		
		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastSpellAction::getPrerequisites());
		}
	};


	class CastCatBuffSpellAction : public CastBuffSpellAction 
	{
	public:
		CastCatBuffSpellAction(AiManagerRegistry* const ai, const char* spell) : CastBuffSpellAction(ai, spell) {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastBuffSpellAction::getPrerequisites());
		}
	};

	class CastCatMeleeSpellAction : public CastMeleeSpellAction 
	{
	public:
		CastCatMeleeSpellAction(AiManagerRegistry* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
		}
	};

	class CastCowerAction : public CastBuffSpellAction 
	{
	public:
		CastCowerAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "cower") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastBuffSpellAction::getPrerequisites());
		}
	};


	class CastBerserkAction : public CastCatBuffSpellAction 
	{
	public:
		CastBerserkAction(AiManagerRegistry* const ai) : CastCatBuffSpellAction(ai, "berserk") {}
	};

	class CastTigersFuryAction : public CastCatBuffSpellAction 
	{
	public:
		CastTigersFuryAction(AiManagerRegistry* const ai) : CastCatBuffSpellAction(ai, "tiger's fury") {}
	};
	
	class CastRakeAction : public CastDebuffSpellAction 
	{
	public:
		CastRakeAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "rake") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), new NextAction("cat form"), NULL), CastDebuffSpellAction::getPrerequisites());
		}
	};


	class CastClawAction : public CastCatMeleeSpellAction {
	public:
		CastClawAction(AiManagerRegistry* const ai) : CastCatMeleeSpellAction(ai, "claw") {}
	};

	class CastMangleCatAction : public CastCatMeleeSpellAction {
	public:
		CastMangleCatAction(AiManagerRegistry* const ai) : CastCatMeleeSpellAction(ai, "mangle (cat)") {}
	};

	class CastFerociousBiteAction : public CastCatMeleeSpellAction {
	public:
		CastFerociousBiteAction(AiManagerRegistry* const ai) : CastCatMeleeSpellAction(ai, "ferocious bite") {}
	};


	class CastRipAction : public CastCatMeleeSpellAction {
	public:
		CastRipAction(AiManagerRegistry* const ai) : CastCatMeleeSpellAction(ai, "rip") {}
	};



}