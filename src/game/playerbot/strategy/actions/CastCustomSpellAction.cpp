#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "CastCustomSpellAction.h"

using namespace ai;

bool CastCustomSpellAction::Execute(Event event)
{
    ObjectGuid targetGuid = master->GetSelectionGuid();
    Unit* target = targetGuid ? ai->GetUnit(targetGuid) : bot;

    string text = event.getParam();
    uint32 spell = chat->parseSpell(text);

    if (spell)
        return ai->CastSpell(spell, target);

    return ai->CastSpell(text, target);
}
