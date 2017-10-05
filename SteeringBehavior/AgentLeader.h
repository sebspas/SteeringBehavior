#ifndef AGENT_LEADER_H
#define AGENT_LEADER_H

#include "Vehicle.h"
#include "2d/Vector2D.h"
#include "SteeringBehaviors.h"

class AgentLeader : public Vehicle
{

public:

	AgentLeader(GameWorld* world,
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
			max_speed, max_turn_rate, scale) {

		// set as leader
		this->setAsLeader(true);

		// we set the size of our leader
		this->SetScale(Vector2D(15, 15));

		// we set the movement to wanderOn
		this->Steering()->WanderOn();

		this->SetMaxSpeed(90);
	};

};

#endif // !AGENT_LEADER_H