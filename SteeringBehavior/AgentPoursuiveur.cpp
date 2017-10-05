#include "AgentPoursuiveur.h"
#include "GameWorld.h"
#include <iostream>





Vehicle * AgentPoursuiveur::findWhoFollow(Vehicle* pToFollow)
{
	while (pToFollow->getFollower() != NULL)
	{
		pToFollow = pToFollow->getFollower();
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
		this->Steering()->OffsetPursuitOn(this->getTarget(), Vector2D(-20, 0));
	};

	Vehicle::Update(time_elapsed);
}
