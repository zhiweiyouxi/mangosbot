#ifndef _PLAYERBOTCLASSAI_H
#define _PLAYERBOTCLASSAI_H

using namespace ai;
using namespace std;

#include "../strategy/Strategy.h"

namespace ai
{
	class AiManagerRegistry;
    class AiManagerBase;
    class Engine;

	class AiStrategyManager : public AiManagerBase
	{
	public:
		AiStrategyManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);
		virtual ~AiStrategyManager();

	public:
		virtual void DoNextAction();
		virtual void DoSpecificAction(const char* name);
		virtual void ChangeStrategy( const char* name, Engine* e );
		virtual void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, combatEngine); }
		virtual void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }
		virtual bool ContainsStrategy(StrategyType type);

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

    private:
        void ReInitCurrentEngine();

	protected:
		Engine* currentEngine;
		Engine* combatEngine;
		Engine* nonCombatEngine;
	};

}
#endif
