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
		virtual string GetIncompatibleStrategies() { return "-bhealth,-bpds"; }
    };

    class PaladinBuffHealthStrategy : public Strategy
    {
    public:
        PaladinBuffHealthStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "bhealth"; }
		virtual string GetIncompatibleStrategies() { return "-bmana,-bpds"; }
    };

    class PaladinBuffDpsStrategy : public Strategy
    {
    public:
        PaladinBuffDpsStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "bdps"; }
		virtual string GetIncompatibleStrategies() { return "-bhealth,-bmana,-barmor,-rfrost,-rfire,-rshadow"; }
    };

	class PaladinBuffArmorStrategy : public Strategy
	{
	public:
		PaladinBuffArmorStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "barmor"; }
		virtual string GetIncompatibleStrategies() { return "-bdps,-rfrost,-rfire,-rshadow"; }
	};

	class PaladinShadowResistanceStrategy : public Strategy
	{
	public:
		PaladinShadowResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rshadow"; }
		virtual string GetIncompatibleStrategies() { return "-barmor,-bdps,-rfrost,-rfire"; }
	};

	class PaladinFrostResistanceStrategy : public Strategy
	{
	public:
		PaladinFrostResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rfrost"; }
		virtual string GetIncompatibleStrategies() { return "-barmor,-bdps,-rfire,-rshadow"; }
	};

	class PaladinFireResistanceStrategy : public Strategy
	{
	public:
		PaladinFireResistanceStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual const char* getName() { return "rfire"; }
		virtual string GetIncompatibleStrategies() { return "-barmor,-bdps,-rfrost,-rshadow"; }
	};
}
