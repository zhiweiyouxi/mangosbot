#pragma once

class Player;
#include "LazyCalculatedValue.h"

using namespace std;

namespace ai 
{
    typedef map<ObjectGuid, ThreatManager*> AttackerMap;
    typedef map<ObjectGuid, ThreatManager*>::const_iterator AttackerMapIterator;

	class AttackerMapProvider 
	{
	public:
		AttackerMapProvider(Player* master);
        virtual ~AttackerMapProvider();

    public:
        AttackerMap GetAttackers();
        void Reset();

    private:
        AttackerMap provideAttackers();
		void addAttackersOf(Player *player, AttackerMap &out);
        bool hasRealThreat(Unit *attacker);

    private:
        Player* master;
        LazyCalculatedValue<AttackerMap, AttackerMapProvider> *attackers;
	};

};