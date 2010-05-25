#include "pchdef.h"
#include "DBCStructure.h"
#include "Spell.h"
#include "Group.h"
#include "Creature.h"
#include "Unit.h"
#include "SpellAuras.h"
#include "PlayerbotAIFacade.h"
#include "FleeManager.h"
#include "PlayerbotAIBase.h"

using namespace ai;

void PlayerbotAIFacade::Melee() 
{ 
	Unit* target = GetTargetManager()->GetCurrentTarget();
    if (!target)
        return;

	Player* bot = ai->GetPlayerBot();
	if (!bot->isInFrontInMap(target, 5.0f))
		bot->SetInFront(target);
    
    Attack(target); 
}

void PlayerbotAIFacade::Emote(uint32 emote)
{
    ai->GetPlayerBot()->HandleEmoteCommand(emote);
}

void PlayerbotAIFacade::Attack(Unit* target) 
{
	if (!target) 
		return;

	ai->Attack(target); 
}
