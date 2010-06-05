#pragma once

using namespace std;

class Player;

namespace ai 
{
    class Engine;
    class AiManagerRegistry;
    
	class RangePair {
	public:
		RangePair() {
			min = -1.0f;
			max = -1.0f;
		}

	public:
		float min;
		float max;

	public:
		void probe(float d) {
			if (min < 0 || min > d)
				min = d;

			if (max < 0 || max < d)
				max = d;
		}
	};

	class FleePoint {
	public:
		FleePoint(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

	public:
		float x;
		float y;
		float z;

		RangePair toCreatures;
		RangePair toAllPlayers;
		RangePair toMeleePlayers;
		RangePair toRangedPlayers;
	};

	class FleeManager
	{
	public:
		FleeManager(Player* bot, map<Unit*, ThreatManager*> *attackers, float maxAllowedDistance, float followAngle) {
			this->bot = bot;
			this->attackers = attackers;
			this->maxAllowedDistance = maxAllowedDistance;
			this->followAngle = followAngle;
		}

	public:
		bool flee(float* rx, float* ry, float* rz);

	private:
		void calculatePoints(list<FleePoint*> &points);
		void calculateDistanceToPlayers(FleePoint *point);
		void calculateDistanceToCreatures(FleePoint *point);
		void deletePoints(list<FleePoint*> &points);
		FleePoint* selectOptimalPoint(list<FleePoint*> &points);
		bool isAllowed(FleePoint* point);
		bool isBetterThan(FleePoint* point, FleePoint* other);

	private:
		Player* bot;
		map<Unit*, ThreatManager*> *attackers;
		float maxAllowedDistance;
		float followAngle;
	};

};