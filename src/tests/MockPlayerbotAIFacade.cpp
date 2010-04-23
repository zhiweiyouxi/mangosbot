#include "pch.h"
#include "MockPlayerbotAIFacade.h"

using namespace std;
using namespace ai;

BOOL MockPlayerbotAIFacade::canCastSpell(const char* spell)
{
    for (list<string>::iterator i = spellCooldowns.begin(); i != spellCooldowns.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return FALSE;
    }
    return TRUE;
}

BOOL MockPlayerbotAIFacade::CastSpell(const char* spell, Unit* target) 
{
    if (distanceToEnemy > SPELL_DISTANCE)
        return FALSE;

    buffer.append(">").append(spell); 
    if (target) buffer.append(" on party"); 

    spellCooldowns.push_back(spell); 
    
    return TRUE; 
}

BOOL MockPlayerbotAIFacade::CastSpellOnCurrentTarget(const char* spell) 
{
    if (distanceToEnemy > SPELL_DISTANCE)
        return FALSE;

    buffer.append(">").append(spell); 
    buffer.append(" on target"); 

    spellCooldowns.push_back(spell); 

    return TRUE; 
}

BOOL MockPlayerbotAIFacade::HasAura(const char* spell)
{
    for (list<string>::iterator i = auras.begin(); i != auras.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return TRUE;
    }
    return FALSE;
}

BOOL MockPlayerbotAIFacade::TargetHasAura(const char* spell)
{
    for (list<string>::iterator i = targetAuras.begin(); i != targetAuras.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return TRUE;
    }
    return FALSE;
}

BOOL MockPlayerbotAIFacade::PetHasAura(const char* spell)
{
    for (list<string>::iterator i = petAuras.begin(); i != petAuras.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return TRUE;
    }
    return FALSE;
}

BOOL MockPlayerbotAIFacade::IsAllPartyHasAura(const char* spell)
{
    for (list<string>::iterator i = partyAuras.begin(); i != partyAuras.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return TRUE;
    }
    return FALSE;
}
