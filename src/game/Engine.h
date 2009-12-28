#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"

namespace ai
{
    class MANGOS_DLL_SPEC Engine : public PlayerBotAiAware
    {
    public:
        Engine(Player* const master, Player* const bot, PlayerbotAI* const ai) : PlayerBotAiAware(ai)
        {
            this->master = master;
            this->bot = bot;
        }

	    virtual void Init() {}
	    virtual void DoNextAction(Unit*);

    public:
	    virtual ~Engine(void);
    protected:
	    Queue queue;
	    std::list<Trigger*> triggers;
	    Player* master;
	    Player* bot;
    };
}