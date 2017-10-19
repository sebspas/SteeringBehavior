#include "AgentPoursuiveur.h"
#include "GameWorld.h"
#include <iostream>


Vehicle * AgentPoursuiveur::findWhoFollow(Vehicle* pToFollow)
{
	numFollower = 0;
	Vehicle* pLeader = pToFollow;
	while (pToFollow->getFollower() != NULL)
	{
		pToFollow = pToFollow->getFollower();
		pToFollow->setColor(pLeader->getCurrentColor());
		numFollower++;
	}

	return pToFollow;
}

void AgentPoursuiveur::updateFollowers() {

	AgentPoursuiveur* pFollower = this;
	int num = this->numFollower;
	while (pFollower->getFollower() != NULL)
	{
		pFollower = (AgentPoursuiveur*)pFollower->getFollower();

		pFollower->numFollower = ++num;
		pFollower->adaptBehavior();

	}
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
		this->Steering()->FlockingOn();

		if (this->numFollower % 2 == 0) {
			this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(-6, 12 * (this->numFollower+1)));
		}
		else {
			this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(18, -12 * (this->numFollower+1)));
		}

		// update the offset for all the following agent
		this->updateFollowers();

		break;

	default:
		break;
	}
}
