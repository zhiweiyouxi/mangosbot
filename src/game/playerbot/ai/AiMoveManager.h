#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiMoveManager : public AiManagerBase
	{
	public:
		AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);

	public:
		virtual float GetDistanceTo(Unit* target);
        virtual void MoveTo(uint32 mapId, float x, float y, float z);
		virtual void MoveTo(Unit* target, float distance = 0.0f);
        virtual void MoveTo(WorldObject* target);
		virtual float GetFollowAngle();
		virtual void Follow(Unit* target, float distance = 2.0f);
		virtual bool Flee(Unit* target, float distance = SPELL_DISTANCE);
		virtual void Stay();
		virtual bool IsMoving(Unit* target);
		virtual void Attack(Unit* target);
		virtual void ReleaseSpirit();
		virtual void Resurrect();
		virtual void Revive();
        virtual void Summon();
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void HandleMasterIncomingPacket(const WorldPacket& packet);

    private:
        bool IsMovingAllowed(Unit* target);
        bool IsMovingAllowed(uint32 mapId, float x, float y, float z);
        bool IsMovingAllowed();

    private:
        vector<uint32> taxiNodes;
        uint64 taxiMaster;
	};

};