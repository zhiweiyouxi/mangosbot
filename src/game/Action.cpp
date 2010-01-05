#include "pchdef.h"
#include "PlayerbotAIFacade.h"
#include "Action.h"

using namespace ai;

NextAction** Action::getNextActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getNextAction();
    actions[1] = NULL;
    return actions;
}

NextAction** Action::getAlternativeActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getAlternativeAction();
    actions[1] = NULL;
    return actions;
}

NextAction** Action::getPrerequisiteActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getPrerequisiteAction();
    actions[1] = NULL;
    return actions;
}

NextAction** NextAction::clone(NextAction** actions)
{
    if (!actions)
        return NULL;

    int size;
    for (size=0; size<10 && actions[size]; ) 
        size++;

    NextAction** res = new NextAction*[size + 1];
    for (int i=0; i<size; i++)
        res[i] = new NextAction(*actions[i]);
    res[size] = NULL;
    return res;
}

NextAction** NextAction::array(uint8 nil, ...)
{
    va_list vl;
    va_start(vl, nil);
    
    int size = 0;
    NextAction* cur = NULL;
    do 
    {
        cur = va_arg(vl, NextAction*);
        size++;
    }
    while (cur);

    va_end(vl);

    NextAction** res = new NextAction*[size];
    va_start(vl, nil);
    for (int i=0; i<size; i++)
        res[i] = va_arg(vl, NextAction*);
    va_end(vl);

    return res;
}
