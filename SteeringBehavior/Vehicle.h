#ifndef VEHICLE_H
#define VEHICLE_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   Vehicle.h
//
//  Desc:   Definition of a simple vehicle that uses steering behaviors
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "MovingEntity.h"
#include "2d/Vector2D.h"
#include "misc/Smoother.h"

#include <vector>
#include <list>
#include <string>

class GameWorld;
class SteeringBehavior;



class Vehicle : public MovingEntity
{
protected:
	// color of the vehicle
	enum ColorVehicle { RED, BROWN, ORANGE, BLUE };

	// current color of the vehicle
	ColorVehicle currentColor = BLUE;
private:

	//a pointer to the world data. So a vehicle can access any obstacle,
	//path, wall or agent data
	GameWorld*            m_pWorld;

	//the steering behavior class
	SteeringBehavior*     m_pSteering;


	//some steering behaviors give jerky looking movement. The
	//following members are used to smooth the vehicle's heading
	Smoother<Vector2D>*  m_pHeadingSmoother;

	//this vector represents the average of the vehicle's heading
	//vector smoothed over the last few frames
	Vector2D             m_vSmoothedHeading;

	//when true, smoothing is active
	bool                  m_bSmoothingOn;


	//keeps a track of the most recent update time. (some of the
	//steering behaviors make use of this - see Wander)
	double                m_dTimeElapsed;


	//buffer for the vehicle shape
	std::vector<Vector2D> m_vecVehicleVB;

	//fills the buffer with vertex data
	void InitializeBuffer();

	//disallow the copying of Vehicle types
	Vehicle(const Vehicle&);
	Vehicle& operator=(const Vehicle&);

	// The target of this agent
	Vehicle* m_pTarget;

	// The follower of this agent
	Vehicle* m_pFollower;

	// to know if it's a leader
	bool m_isLeader;

	//for manual mode clampedx and clampedy
	double m_dclampedx;
	double m_dclampedy;

public:

	Vehicle(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	~Vehicle();

	//updates the vehicle's position and orientation
	void        Update(double time_elapsed);

	void        Render();

	ColorVehicle getCurrentColor() { return this->currentColor; }


	//-------------------------------------------accessor methods
	SteeringBehavior*const  Steering()const { return m_pSteering; }
	GameWorld*const         World()const { return m_pWorld; }


	Vector2D    SmoothedHeading()const { return m_vSmoothedHeading; }

	bool        isSmoothingOn()const { return m_bSmoothingOn; }
	void        SmoothingOn() { m_bSmoothingOn = true; }
	void        SmoothingOff() { m_bSmoothingOn = false; }
	void        ToggleSmoothing() { m_bSmoothingOn = !m_bSmoothingOn; }

	double       TimeElapsed()const { return m_dTimeElapsed; }

	//get the target
	Vehicle* getTarget() { return this->m_pTarget; };

	// Set the target
	void setTarget(Vehicle * pnewTarget) { 
		if (m_pTarget != NULL) {
			// if there is an actual target we remove ourself
			m_pTarget->setFollower(NULL);
		}
		// we change our target
		m_pTarget = pnewTarget;

		// we add ourself
		m_pTarget->setFollower(this);
	};

	// target leader
	Vehicle* getTargetLeader() { 
		if (this->getTarget() == nullptr) {
			return nullptr;
		}

		Vehicle* pV = this;
		while (! pV->isLeader()) {
			pV = pV->getTarget();
		}
		return pV;
	}

	//get the follower
	Vehicle* getFollower() { return this->m_pFollower; };

	// Set the follower
	void setFollower(Vehicle * pnewFollower){m_pFollower = pnewFollower;};

	// Useful to know if an agent is a leader
	void setAsLeader(bool leader) {
		m_isLeader = leader;
	};
	bool isLeader() {
		return m_isLeader;
	};

	//for manual mode with the clamped
	void setClampedx(double x) { m_dclampedx = x; };
	void setClampedy(double y) { m_dclampedy = y; };
	double getClampedx() { return m_dclampedx; };
	double getClampedy() { return m_dclampedy; };


	//change the color of the vehicle
	void setColor(ColorVehicle color) {
		this->currentColor = color;
	}

	void setColorByInt(int numColor) {
		this->currentColor = static_cast<ColorVehicle>(numColor);
	}
};

#endif