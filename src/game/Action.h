#pragma once

#include "PlayerBotAI.h"
#include "Spell.h"

namespace ai
{
	class Action
	{
	public:
		Action(PlayerbotAI* const ai);

		virtual void Execute() {}
		virtual Action** GetAfterActions() {return NULL;}
	public:
		virtual ~Action(void);

	protected:
		PlayerbotAI* ai;
	};

	//---------------------------------------------------------------------------------------------------------------------

	class CastSpellAction : public Action
	{
	public:
		CastSpellAction(PlayerbotAI* const ai, const char* spell);

		void Execute();
	private:
		uint32 spellid;
	};
}