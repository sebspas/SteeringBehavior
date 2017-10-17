#ifndef AGENT_POURSUIVEUR_H
#define AGENT_POURSUIVEUR_H

#include "Vehicle.h"
#include "2d/Vector2D.h"
#include "SteeringBehaviors.h"

class AgentPoursuiveur : public Vehicle
{

public :

	int numFollower = 1;
	enum class Behavior { INLINE, VFLOCKING };

	// Find target to follow
	Vehicle * AgentPoursuiveur::findWhoFollow(Vehicle* pToFollow);

	// Override Update
	void Update(double time_elapsed);

	AgentPoursuiveur(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale) :
		Vehicle(world, position, rotation,
			velocity, mass, max_force,
			max_speed, max_turn_rate, scale)
	{
		// smart follower
		this->Steering()->WanderOn();
	};


private:
	void AgentPoursuiveur::adaptBehavior(Behavior behave, Vehicle* pTargetLeader);

};

#endif // !AGENT_POURSUIVEUR_H