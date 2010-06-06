#include "../../pchdef.h"
#include "../playerbot.h"
#include "AttackerMapProvider.h"


using namespace ai;
using namespace std;

AttackerMapProvider::AttackerMapProvider(Player* _master) : master(_master)
{
    attackers = new LazyCalculatedValue<AttackerMap, AttackerMapProvider>(this, &AttackerMapProvider::provideAttackers);
}

AttackerMapProvider::~AttackerMapProvider()
{
    if (attackers)
        delete attackers;
}

AttackerMap AttackerMapProvider::provideAttackers()
{
    AttackerMap result;

    Group* group = master->GetGroup();
    if (!group)
    {
        addAttackersOf(master, result);
        return result;
    }

    for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next()) 
    {
        Player* player = ref->getSource();
        addAttackersOf(player, result);
    }
    
    return result;
}

bool AttackerMapProvider::hasRealThreat(Unit *attacker)
{
    return attacker && 
        !attacker->isDead() && 
        !attacker->IsPolymorphed() && 
        !attacker->isFrozen() && 
        !attacker->IsFriendlyTo(master);
}

void AttackerMapProvider::addAttackersOf(Player *player, AttackerMap &out)
{
    for (HostileReference *ref = player->getHostileRefManager().getFirst(); ref; ref = ref->next()) 
    {
		ThreatManager *threatManager = ref->getSource();
		Unit *attacker = threatManager->getOwner();

        if (hasRealThreat(attacker))
            out[attacker] = threatManager;
	}
}

AttackerMap AttackerMapProvider::GetAttackers() 
{
    return attackers->GetValue(); 
}

void AttackerMapProvider::Reset() 
{
    attackers->Reset(); 
}
