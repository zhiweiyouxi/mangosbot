#include "pchdef.h"
#include "Engine.h"
namespace ai
{
Engine::Engine(Player* const master, Player* const bot, PlayerbotAI* const ai)
{
	this->master = master;
	this->bot = bot;
	this->ai = ai;
}

Engine::~Engine(void)
{
	Action* action = NULL;
	do 
	{
		action = queue.Pop();
	} while (action);
}

void Engine::DoNextAction(Unit*)
{
	Action* action = queue.Pop();
	
	if (action)
	{
		action->Execute();
		Action** actions = action->GetAfterActions();
		for (int i=0; i<sizeof(actions)/sizeof(Action*); i++)
		{
			queue.Push(actions[i], 1.0f);
		}
		delete action;
	}
}
}