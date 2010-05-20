#include "pch.h"
#include "MockAiSpellManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

void MockAiSpellManager::InterruptSpell()
{
}

void MockAiSpellManager::RemoveAura(const char* name)
{
	Unit* target = MockedTargets::GetSelf();
	if (HasAura(name, target)) {
		auras[target].remove(name);
		buffer->append(">-");
		buffer->append(name);
	}
}

bool MockAiSpellManager::CanCastSpell(const char* name, Unit* target)
{
	for (list<string>::iterator i = spellCooldowns.begin(); i != spellCooldowns.end(); i++)
	{
		string s = *i;
		if (!strcmp(s.c_str(), name))
			return false;
	}
	return true;
}

bool MockAiSpellManager::CastSpell(const char* name, Unit* target)
{
	buffer->append(">").append(name); 
	if (target == MockedTargets::GetPartyMember()) 
		buffer->append(" on party"); 

	spellCooldowns.push_back(name); 

	return true; 
}

bool MockAiSpellManager::HasAura(const char* spellName, Unit* player)
{
	for (list<string>::iterator i = auras[player].begin(); i != auras[player].end(); i++)
	{
		string s = *i;
		if (!strcmp(s.c_str(), spellName))
			return TRUE;
	}
	return false;

}
bool MockAiSpellManager::IsSpellCasting(Unit* player)
{
	return targetIsCastingNonMeleeSpell;
}

bool MockAiSpellManager::HasAuraToDispel(Unit* player, uint32 dispelType)
{
	return dispels[player];
}
