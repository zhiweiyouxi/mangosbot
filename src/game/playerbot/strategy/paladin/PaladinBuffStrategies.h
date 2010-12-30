#pragma once

#include "GenericPaladinStrategy.h"

namespace ai
{
    class PaladinBuffManaStrategy : public Strategy
    {
    public:
        PaladinBuffManaStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "bmana"; }
    };

    class PaladinBuffHealthStrategy : public Strategy
    {
    public:
        PaladinBuffHealthStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "bhealth"; }
    };

    class PaladinBuffDpsStrategy : public Strategy
    {
    public:
        PaladinBuffDpsStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "bdps"; }
    };

	class PaladinBuffArmorStrategy : public Strategy
	{
	public:
		PaladinBuffArmorStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "barmor"; }
	};

	class PaladinShadowResistanceStrategy : public Strategy
	{
	public:
		PaladinShadowResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rshadow"; }
	};

	class PaladinFrostResistanceStrategy : public Strategy
	{
	public:
		PaladinFrostResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rfrost"; }
	};

	class PaladinFireResistanceStrategy : public Strategy
	{
	public:
		PaladinFireResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rfire"; }
	};
}
