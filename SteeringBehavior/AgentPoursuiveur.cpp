#include "AgentPoursuiveur.h"
#include "GameWorld.h"
#include <iostream>


Vehicle * AgentPoursuiveur::findWhoFollow(Vehicle* pToFollow)
{
	numFollower = 0;
	while (pToFollow->getFollower() != NULL)
	{
		pToFollow = pToFollow->getFollower();
		numFollower++;
	}
	return pToFollow;
}


// UPDATE OVERRIDE
void AgentPoursuiveur::Update(double time_elapsed)
{
	Vehicle * pTargetLeader = NULL;
	// Iterate of all the vehicle
	std::vector<Vehicle*> neighbors = this->World()->Agents();
	for (unsigned int a = 0; a < neighbors.size(); ++a)
	{
		if ((neighbors[a] != this) && neighbors[a]->isLeader())
		{
			// if agent is close enough
			Vector2D ToAgent = this->Pos() - neighbors[a]->Pos();
			if (ToAgent.Length() < Prm.ViewDistance)
			{
				pTargetLeader = neighbors[a];
			};
		}
	}

	// If the agent isn't following and a leader is near 
	if (pTargetLeader != NULL && this->getTargetLeader() != pTargetLeader) {
		this->setTarget(findWhoFollow(pTargetLeader));
		this->Steering()->WanderOff();

		// attempt at V-flocking beahvior
		this->adaptBehavior();

		// change the color of the vehicle to the color of the followed leader
		this->setColor(pTargetLeader->getCurrentColor());
	};

	Vehicle::Update(time_elapsed);
}


void AgentPoursuiveur::adaptBehavior() {

	switch (this->currentBehavior)
	{
	case Behavior::INLINE:
		this->Steering()->FlockingOff();
		this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(-5, 0));
		break;

	case Behavior::VFLOCKING:
		/*
		// set agent before last as target
		this->setTarget(pBeforeLast);
		this->Steering()->FlockingOn();

		if (numFollower == 0) {
			this->Steering()->OffsetPursuitOn(this->getTargetLeader(), Vector2D(-8, 12));
		}
		else if (numFollower == 1) {
			this->Steering()->OffsetPursuitOn(this->getTargetLeader(), Vector2D(-8, -12));
		}
		else if (this->numFollower % 2 == 0) {
			this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(-3, 12 * this->numFollower));
		}
		else {
			this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(3, -12 * this->numFollower));
		}
		break;

	default:
		break;
		*/
	}
}
