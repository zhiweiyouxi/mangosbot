#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"
#include "Multiplier.h"

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

    private:
        void MultiplyAndPush(ActionBasket** actions);

    protected:
	    Queue queue;
	    std::list<Trigger*> triggers;
        std::list<Multiplier*> multipliers;
	    Player* master;
	    Player* bot;
    };
}