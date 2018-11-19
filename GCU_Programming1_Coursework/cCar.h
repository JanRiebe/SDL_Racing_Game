#pragma once
#include "cSpriteAnimation.h"
#include "cCollider.h"
class cCar :
	public cSpriteAnimation, public cCollider
{
private:
	// Physical state
	fpoint acceleration;	// Forces acting at a single time point.
	fpoint impulse;			// Forces acting over the time of a frame.
	fpoint velocity;
	fpoint physPos;			// Pixelindependent physical position.
	float steering;			// The angle the steering wheel is turned.

	// Attributes of the car
	float mass;
	float airResist;
	float engine;	// How strong the engine is.
	float slipping;	// The force at which the tires slip.
	float steerReactive;
	// Calculates a unit vector in the sprite's forward direction.
	fpoint forwardVector();

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

	// Called by the collision manager when this collider collides with another.
	void onCollision(cCollider* other);

	// Returns the current velocity.
	fpoint getVelocity();
	// Returns the mass.
	float getMass();
	// Returns the current rotation angle of the sprite.
	float getAngle();
	// Returns the current position of the sprite.
	SDL_Point getPosition();
};

