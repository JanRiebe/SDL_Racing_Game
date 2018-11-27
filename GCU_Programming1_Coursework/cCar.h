#pragma once
#include "cSpriteState.h"

class cPlayer;

class cCar :
	public cSpriteState
{
private:
	// Physical state
	fpoint acceleration;	// Forces acting at a single time point.
	//fpoint impulse;			// Forces acting over the time of a frame.
	fpoint velocity;
	fpoint physPos;			// Pixelindependent physical position.
	fpoint lastPos;
	float steering;			// The angle the steering wheel is turned.

	float damage;		// How much this car has been harmed by collisions.

	// Attributes of the car
	float mass;
	float airResist;
	float engine;	// How strong the engine is.
	float tireFriction;	// The force at which the tires slip.
	float steerReactive;
	// Calculates a unit vector in the sprite's forward direction.
	fpoint forwardVector();
	// Calculates and returns the effective velocity in the forward direction.
	fpoint calculateForwardVelocity(fpoint velocity);

	cPlayer* controller;		// Who controls this car.

public:
	cCar(float mass, float airResistance, float enginePower, float tireSlippingPoint, float steerReactiveness);
	~cCar();
	// Adds a one time force in both directions.
	void addImpulse(fpoint force);
	// Adds a force in the forward direction of the car that acts over the whole time of the frame.
	void accelerate(float force);
	// Steers the car into a direction. The parameter "angle" can be seen as the angle the steering wheel is being turned.
	void steer(float angle);
	void update(double deltaTime);

	// Overwrites function in cSprite, to set the physics position as well.
	void setSpritePos(SDL_Point worldPos);

	// Called by the collision manager when this has collided with another ICollidable.
	void onCollision(fpoint impulse);
	// Returns the current impulse.
	fpoint getImpulse();

	// Informs this car that it is now controlled by a player.
	void setController(cPlayer* c);
};

