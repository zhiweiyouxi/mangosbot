#pragma once;

#include "Engine.h"
#include "Action.h"
#include "MageActions.h"

namespace ai
{

class MageEngine : public Engine
{
public:
    MageEngine(PlayerbotAIFacade* const ai) : Engine(ai) {}
    virtual ~MageEngine(void) {}

public:
	virtual void InitTriggers();
    virtual void InitQueue();
    virtual void InitActionFactory();
    virtual void InitMultipliers();
};

}