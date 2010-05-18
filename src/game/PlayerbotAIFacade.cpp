#include "pchdef.h"
#include "DBCStructure.h"
#include "Spell.h"
#include "Group.h"
#include "Creature.h"
#include "Unit.h"
#include "SpellAuras.h"
#include "PlayerbotAIFacade.h"
#include "FleeManager.h"

using namespace ai;

void PlayerbotAIFacade::Melee() 
{ 
	Unit* target = ai->GetCurrentTarget();
	ai->Attack(target); 

	Player* bot = ai->GetPlayerBot();
	if (!bot->isInFrontInMap(target, 5.0f))
		bot->SetInFront(target);
}

void PlayerbotAIFacade::MoveToTarget(float distance) 
{ 
	Player* bot = ai->GetPlayerBot();
	
	Stay();
	
	Unit* target = ai->GetCurrentTarget();
	bot->GetMotionMaster()->MoveFollow(target, distance, 0); 	
}

void PlayerbotAIFacade::Stay() 
{
	Player* bot = ai->GetPlayerBot();

	bot->GetMotionMaster()->Clear( true );
	bot->clearUnitState( UNIT_STAT_CHASE );
	bot->clearUnitState( UNIT_STAT_FOLLOW );

	if (!bot->IsStandState())
		bot->SetStandState(UNIT_STAND_STATE_STAND);
}

float PlayerbotAIFacade::GetDistanceToEnemy(float ifNoTarget)
{
    Unit *target = ai->GetCurrentTarget();
    if (target && !target->isDead())
    {
        return ai->GetPlayerBot()->GetDistance(target); 
    }
    return ifNoTarget;
}

bool PlayerbotAIFacade::canCastSpell( const char* name )
{
    uint32 spellid = ai->getSpellId(name);
    Player* bot = ai->GetPlayerBot();

    bool res = bot->HasSpell(spellid) && !bot->HasSpellCooldown(spellid);
    if (!res)
        return FALSE;

    SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
    Spell *spell = new Spell(bot, spellInfo, false );
    res = (spell->CheckPower() == SPELL_CAST_OK);
    delete spell;

    return res;
}

uint8 PlayerbotAIFacade::GetRage()
{
    return ai->GetRagePercent();
}

uint8 PlayerbotAIFacade::GetEnergy()
{
	return ai->GetEnergyAmount();
}

bool PlayerbotAIFacade::HasAura(const char* spell)
{
    return ai->HasAura(spell);
}

bool PlayerbotAIFacade::PetHasAura(const char* spell)
{
    return ai->HasAura(spell, *ai->GetPlayerBot()->GetPet());
}

bool PlayerbotAIFacade::TargetHasAura(const char* spell)
{
    return ai->HasAura(spell, *ai->GetCurrentTarget());
}

Unit* PlayerbotAIFacade::findPlayer(bool predicate(Unit*, FindPlayerParam*), void* param)
{
	Player* bot = ai->GetPlayerBot();
    Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	FindPlayerParam pp; pp.ai = ai; pp.param = param;
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) {
		Player* player = gref->getSource();
		if (checkPredicate(player, predicate, &pp))
			return player;
		
		Pet* pet = player->GetPet();
		if (pet && pet->IsPermanentPetFor(player) && checkPredicate(player, predicate, &pp))
			return player;
	}
	return NULL;
}

bool PlayerbotAIFacade::checkPredicate(Unit* player, bool predicate(Unit*, FindPlayerParam*), FindPlayerParam *param) {
	Player* bot = ai->GetPlayerBot();

    return (player != bot && 
		bot->GetDistance(player) < BOT_REACT_DISTANCE &&
		bot->IsWithinLOS(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()) &&
		(predicate==NULL || predicate(player, param)));
}

bool PlayerbotAIFacade::isPlayerWithoutAura(Unit* player, FindPlayerParam *param )
{
    return player->isAlive() && !param->ai->HasAura((const char*)param->param, *player);
}

void PlayerbotAIFacade::RemoveAura(const char* name)
{
    uint32 spellid = ai->getSpellId(name);
    ai->GetPlayerBot()->RemoveAurasDueToSpell(spellid);
}

bool PlayerbotAIFacade::HasAggro()
{
    Unit* currentTarget = ai->GetCurrentTarget();
    if (currentTarget)
    {
        HostileReference *ref = ai->GetPlayerBot()->getHostileRefManager().getFirst();
        if (!ref)
            return TRUE; // simulate as target is not atacking anybody yet
        while( ref )
        {
            ThreatManager *target = ref->getSource();
            Unit *attacker = target->getOwner();
            Unit *victim = attacker->getVictim();
            if (victim == ai->GetPlayerBot() && currentTarget == attacker)
                return TRUE;
            ref = ref->next();
        }
    }
    return FALSE;
}

bool PlayerbotAIFacade::FindAndUse(bool predicate(const ItemPrototype*, const void*), const void* param, uint8 ignore_time)
{
    Item* item = ai->FindUsableItem(predicate, param);
    if (item)
    {
        ai->UseItem(*item);
        if (ignore_time)
            ai->SetIgnoreUpdateTime(ignore_time);
        return TRUE;
    }
    return FALSE;
}

void PlayerbotAIFacade::UseFood() 
{
    if (!FindAndUse(isFood, NULL, 30))
        ai->TellMaster("I need some food");
}

void PlayerbotAIFacade::UseDrink() 
{
    if (!FindAndUse(isDrink, NULL, 30))
        ai->TellMaster("I need some water");
}


bool PlayerbotAIFacade::isPanicPotion(const ItemPrototype* pItemProto, const void* param)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

bool PlayerbotAIFacade::isHealingPotion(const ItemPrototype* pItemProto, const void* param)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 441;
}

bool PlayerbotAIFacade::isManaPotion(const ItemPrototype* pItemProto, const void* param)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 438;
}

bool PlayerbotAIFacade::isFood(const ItemPrototype* pItemProto, const void* param)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 11);
}

bool PlayerbotAIFacade::isDrink(const ItemPrototype* pItemProto, const void* param)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 59);
}


char * __cdecl strstri (
					   const char * str1,
					   const char * str2
					   )
{
	char *cp = (char *) str1;
	char *s1, *s2;

	if ( !*str2 )
		return((char *)str1);

	while (*cp)
	{
		s1 = cp;
		s2 = (char *) str2;

		while ( *s1 && *s2 && !(tolower(*s1)-tolower(*s2)) )
			s1++, s2++;

		if (!*s2)
			return(cp);

		cp++;
	}

	return(NULL);

}

bool PlayerbotAIFacade::isTheSameName(const ItemPrototype* pItemProto, const void* param)
{
	const char* name = (const char*)param;
	return pItemProto && pItemProto->Name1 && strstri(pItemProto->Name1, name);
}

Unit* PlayerbotAIFacade::GetPartyMinHealthPlayer()
{
	Player* bot = ai->GetPlayerBot();
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

    MinValueCalculator calc(100);
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) {
		Player* player = gref->getSource();
		if (!checkPredicate(player, NULL, NULL) || !player->isAlive())
			continue;

        uint8 health = ai->GetHealthPercent(*player);
        if (health < 25 || !IsTargetOfHealingSpell(player))
            calc.probe(health, player);

		Pet* pet = player->GetPet();
		if (pet && pet->IsPermanentPetFor(player)) {
			health = ai->GetHealthPercent(*pet);
            if (health < 25 || !IsTargetOfHealingSpell(player))
                calc.probe(health, player);
		}
    }
    return (Unit*)calc.param;
}

Unit* PlayerbotAIFacade::GetDeadPartyMember() {
	Player* bot = ai->GetPlayerBot();

	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) {
		Player* player = gref->getSource();
		if (checkPredicate(player, NULL, NULL) && !player->isAlive() && !IsTargetOfResurrectSpell(player))
			return player;
	}
	return NULL;
}

uint8 PlayerbotAIFacade::GetPartyMinHealthPercent()
{
    Unit* player = GetPartyMinHealthPlayer();
    return player ? ai->GetHealthPercent(*player) : 100;
}


int PlayerbotAIFacade::GetAttackerCount(float distance)
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);
    
    Player* bot = ai->GetPlayerBot();
    int count = 0;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i != attackers.end(); i++) {
        ThreatManager *cur = *i;
        if (bot->GetDistance(cur->getOwner()) <= distance) 
            count++;
    }
    return count;
}


int PlayerbotAIFacade::GetMyAttackerCount()
{
	Player* bot = ai->GetPlayerBot();
    int count = 0;

    HostileReference *ref = bot->getHostileRefManager().getFirst();
    while( ref )
    {
        ThreatManager *target = ref->getSource();
        Unit *attacker = target->getOwner();
        if (attacker && !attacker->isDead() && attacker->getVictim() == bot)
            count++;
        ref = ref->next();
    }
    return count;
}

void PlayerbotAIFacade::findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out)
{
    Player* bot = ai->GetPlayerBot();
    while( ref )
    {
        ThreatManager *source = ref->getSource();
        Unit *attacker = source->getOwner();
        if (attacker && 
            !attacker->isDead() && 
            !attacker->IsPolymorphed() && 
            !attacker->isFrozen() && 
            !attacker->IsFriendlyTo(bot) && 
            bot->IsWithinLOSInMap(attacker))
        {
            bool found = FALSE;
            for (std::list<ThreatManager*>::iterator i = out.begin(); i != out.end(); i++)
            {
                ThreatManager *cur = *i;
                if (cur->getOwner() == attacker)
                {
                    found = TRUE;
                    break;
                }
            }
            if (!found)
                out.push_back(source);
        }
        ref = ref->next();
    }
}

void PlayerbotAIFacade::findAllAttackers(std::list<ThreatManager*> &out)
{
    Player* bot = ai->GetPlayerBot();
    if (bot->GetGroup())
    {
        GroupReference *gref = bot->GetGroup()->GetFirstMember();
        while( gref )
        {
            HostileReference *ref = gref->getSource()->getHostileRefManager().getFirst();
            findAllAttackers(ref, out);
            gref = gref->next();
        }
    }
}

void PlayerbotAIFacade::GoAway(float distance)
{
    Player* bot = ai->GetPlayerBot();

    float rx = bot->GetPositionX();
    float ry = bot->GetPositionY();
    float rz = bot->GetPositionZ();
    float maxDistance = 0;

    for (float r = distance; r>=ATTACK_DISTANCE; r -= ATTACK_DISTANCE)
    {
        for (float angle = 0; angle < 2*M_PI; angle += M_PI / 12)
        {
            float x = bot->GetPositionX() + cos(angle) * r;
            float y = bot->GetPositionY() + sin(angle) * r;
            float z = bot->GetPositionZ();

            if (!bot->IsWithinLOS(x, y, z))
                continue;

            std::list<ThreatManager*> attackers;
            findAllAttackers(attackers);
            for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
            {  
                Unit* unit = (*i)->getOwner();

                float maxPlayerDistance = 0;
                if (ai->GetPlayerBot()->GetGroup())
                {
                    GroupReference *gref = bot->GetGroup()->GetFirstMember();
                    while( gref )
                    {
                        if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
                        {
                            gref = gref->next();
                            continue;
                        }
                        Player* player = gref->getSource();
                        float playerDistance = player->GetDistance(x, y, z);
                        if (playerDistance < SPELL_DISTANCE && maxDistance < playerDistance)
                        {
                            maxDistance = playerDistance;
                            rx = x; ry = y;
                        }

                        gref = gref->next();
                    }
                }

                float distToCreature = unit->GetDistance(x, y, z);
                if (maxPlayerDistance < SPELL_DISTANCE && maxDistance < distToCreature)
                {
                    maxDistance = distToCreature;
                    rx = x; ry = y;
                }
            }
            if (ai->GetPlayerBot()->GetGroup())
            {
                GroupReference *gref = bot->GetGroup()->GetFirstMember();
                while( gref )
                {
                    if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
                    {
                        gref = gref->next();
                        continue;
                    }
                    Player* player = gref->getSource();
                    float playerDistance = player->GetDistance(x, y, z);
                    if (playerDistance < SPELL_DISTANCE && maxDistance < playerDistance)
                    {
                        maxDistance = playerDistance;
                        rx = x; ry = y;
                    }

                    gref = gref->next();
                }
            }
        }
    }

	Stay();
    bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
}

bool PlayerbotAIFacade::Flee(float distance)
{
	std::list<ThreatManager*> attackers;
	findAllAttackers(attackers);
	
	Player* bot = ai->GetPlayerBot();
	FleeManager manager(bot, &attackers, distance, GetFollowAngle());
	
	float rx, ry, rz;
	if (manager.flee(&rx, &ry, &rz)) {
		Stay();
		bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
		return true;
	}
	return false;
}

void PlayerbotAIFacade::AttackLeastThreat()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);

    float minThreat = 1e8;
    Unit* target = NULL;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
    {  
        ThreatManager* attacker = *i;
        float threat = attacker->getThreat(ai->GetPlayerBot());
        if (!target || threat < minThreat)
        {
            minThreat = threat;
            target = attacker->getOwner();
        }
    }
    if (target)
        ai->Attack(target);
}

void PlayerbotAIFacade::AttackBiggerThreat()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);

    float maxThreat = -1;
    Unit* target = NULL;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
    {  
        ThreatManager* attacker = *i;
        float threat = attacker->getThreat(ai->GetPlayerBot());
        if (!target || threat > maxThreat)
        {
            maxThreat = threat;
            target = attacker->getOwner();
        }
    }
    if (target)
        ai->Attack(target);
}

bool PlayerbotAIFacade::IsMounted()
{
    return ai->GetPlayerBot()->IsMounted();
}

void PlayerbotAIFacade::Emote(uint32 emote)
{
    ai->GetPlayerBot()->HandleEmoteCommand(emote);
}

float PlayerbotAIFacade::GetFollowAngle() 
{
    Player* bot = ai->GetPlayerBot();
	Group* group = bot->GetGroup();
    if (group)
    {
        GroupReference *gref = group->GetFirstMember();
        int index = 0;
        while( gref )
        {
            if( gref->getSource() == bot)
            {
                return M_PI / group->GetMembersCount() * index;
            }
            gref = gref->next();
            index++;
        }
    }
    return 0;
}

Unit* PlayerbotAIFacade::GetPartyMemberToDispell(uint32 dispelType)
{
    Group* group = ai->GetMaster()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
                continue;

            if (HasAuraToDispel(player, dispelType))
                return player;

			Pet* pet = player->GetPet();
			if (pet && pet->IsPermanentPetFor(player) && HasAuraToDispel(pet, dispelType))
				return pet;
        }
    }
    return NULL;
}

bool canDispel(const SpellEntry* entry, uint32 dispelType) {
    if (entry->Dispel == dispelType) {
        return !entry->SpellName[0] ||
            (strcmpi((const char*)entry->SpellName[0], "demon skin") &&
               strcmpi((const char*)entry->SpellName[0], "mage armor") &&
               strcmpi((const char*)entry->SpellName[0], "frost armor") &&
               strcmpi((const char*)entry->SpellName[0], "ice armor"));
    }
    return false;
}

bool PlayerbotAIFacade::TargetHasAuraToDispel(uint32 dispelType) {
    Unit* target = ai->GetCurrentTarget();
    if (!target) return false;


    Unit::AuraMap &uAuras = target->GetAuras();
    for (Unit::AuraMap::const_iterator itr = uAuras.begin(); itr != uAuras.end(); ++itr)
    {
        const SpellEntry* entry = itr->second->GetSpellProto();
        uint32 spellId = entry->Id;
        if (!IsPositiveSpell(spellId))
            continue;

        if (canDispel(entry, dispelType))
            return true;
    }
    return false;
}

bool PlayerbotAIFacade::HasAuraToDispel(Unit* player, uint32 dispelType) 
{
    Unit::AuraMap &uAuras = player->GetAuras();
    for (Unit::AuraMap::const_iterator itr = uAuras.begin(); itr != uAuras.end(); ++itr)
    {
        const SpellEntry* entry = itr->second->GetSpellProto();
        uint32 spellId = entry->Id;
        if (IsPositiveSpell(spellId))
            continue;

        if (canDispel(entry, dispelType))
            return TRUE;
    }
    return FALSE;
}

float PlayerbotAIFacade::GetBalancePercent()
{
    uint32 playerLevel = 0,
        attackerLevel = 0;

    Group* group = ai->GetMaster()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
                continue;

            playerLevel += player->getLevel();
        }
    }

    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
    {  
        Unit* unit = (*i)->getOwner();
        if (unit || !unit->isAlive())
            continue;

        uint32 level = unit->getLevel();

        Creature* creature = dynamic_cast<Creature*>(unit);
        if (creature)
        {
            switch (creature->GetCreatureInfo()->rank) {
            case CREATURE_ELITE_RARE:
                level *= 2;
                break;
            case CREATURE_ELITE_ELITE:
                level *= 3;
                break;
            case CREATURE_ELITE_RAREELITE:
                level *= 5;
                break;
            case CREATURE_ELITE_WORLDBOSS:
                level *= 10;
                break;
            }
        }
        attackerLevel += level;
    }

    return !attackerLevel ? 100 : playerLevel * 100 / attackerLevel;
}

bool PlayerbotAIFacade::IsTargetMoving()
{
    Unit *target = ai->GetCurrentTarget();
    return target && target->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE;
}

bool PlayerbotAIFacade::IsTargetCastingNonMeleeSpell() {
    Unit *target = ai->GetCurrentTarget();
    return target && target->IsNonMeleeSpellCasted(true);
}

bool PlayerbotAIFacade::HasAnyAuraOf(const char* first, ...) {
	if (HasAura(first))
		return true;

	va_list vl;
	va_start(vl, first);

	const char* cur = NULL;
	do {
		cur = va_arg(vl, const char*);
		if (cur && HasAura(cur)) {
			va_end(vl);
			return true;
		}
	}
	while (cur);

	va_end(vl);
	return false;
}

bool PlayerbotAIFacade::CastSpell(const char* spell, Unit* target, bool checkAura) {
	Stay();
	return ai->CastSpell(spell, target, checkAura); 
}

bool IsHealingSpell(SpellEntry const* spell) {
    for (int i=0; i<3; i++) {
        if (spell->Effect[i] == SPELL_EFFECT_HEAL ||
            spell->Effect[i] == SPELL_EFFECT_HEAL_MAX_HEALTH ||
            spell->Effect[i] == SPELL_EFFECT_HEAL_MECHANICAL || 
            spell->Effect[i] == SPELL_EFFECT_HEAL_PCT)
            return true;
    }
    return false;
}

bool IsResurrectSpell(SpellEntry const* spell) {
    for (int i=0; i<3; i++) {
        if (spell->Effect[i] == SPELL_EFFECT_RESURRECT || 
            spell->Effect[i] == SPELL_EFFECT_RESURRECT_NEW || 
            spell->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
            return true;
    }
    return false;
}


bool PlayerbotAIFacade::IsTargetOfHealingSpell(Player* target) {
    return IsTargetOfSpellCast(target, IsHealingSpell);
}

bool PlayerbotAIFacade::IsTargetOfResurrectSpell(Player* target) {
    return IsTargetOfSpellCast(target, IsResurrectSpell);
}

bool PlayerbotAIFacade::IsTargetOfSpellCast(Player* target, bool predicate(SpellEntry const*)) {
    Player* bot = ai->GetPlayerBot();
    Group* group = bot->GetGroup();
    uint32 targetGuid = target ? target->GetGUID() : bot->GetGUID();

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) {
        Player* player = gref->getSource();
        if (player == bot)
            continue;

        if (ai->GetCurrentSpellTarget() == targetGuid && player->IsNonMeleeSpellCasted(true)) {
            for (int type = CURRENT_GENERIC_SPELL; type < CURRENT_MAX_SPELL; type++) {
                Spell* spell = player->GetCurrentSpell((CurrentSpellTypes)type);
                if (spell && predicate(spell->m_spellInfo))
                    return true;
            }
        }
    }

    return false;
}