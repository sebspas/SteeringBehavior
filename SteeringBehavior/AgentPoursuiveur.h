#ifndef AGENT_POURSUIVEUR_H
#define AGENT_POURSUIVEUR_H

#include "Vehicle.h"
#include "2d/Vector2D.h"
#include "SteeringBehaviors.h"

class AgentPoursuiveur : public Vehicle
{

public :
	

	// Find target to follow
	Vehicle* findWhoFollow(Vehicle* pToFollow);

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
		double    scale/*,
		Vehicle* target*/) :
		Vehicle(world, position, rotation,
			velocity, mass, max_force,
			max_speed, max_turn_rate, scale)
	{

		/*this->Steering()->OffsetPursuitOn(target, Vector2D(-20, 0));*/

		// smart follower
		this->Steering()->WanderOn();
	};

};

#endif // !AGENT_POURSUIVEUR_H