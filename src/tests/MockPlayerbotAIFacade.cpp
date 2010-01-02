#include "pch.h"
#include "MockPlayerbotAIFacade.h"

using namespace std;
using namespace ai;

BOOL MockPlayerbotAIFacade::canCastSpell(const char* spell)
{
    for (list<string>::iterator i = alreadyCast.begin(); i != alreadyCast.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
            return FALSE;
    }
    return TRUE;
}

void MockPlayerbotAIFacade::resetSpell(const char* spell)
{
    for (list<string>::iterator i = alreadyCast.begin(); i != alreadyCast.end(); i++)
    {
        string s = *i;
        if (!strcmp(s.c_str(), spell))
        {
            alreadyCast.remove(s);
            break;
        }
    }
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
