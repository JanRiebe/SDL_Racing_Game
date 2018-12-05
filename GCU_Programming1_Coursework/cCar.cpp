#include "cCar.h"
#include "cPlayer.h"
#include "cSoundMgr.h"


cCar::cCar(float mass, float airResistance, float enginePower, float tireSlippingPoint, float steerReactiveness): mass(mass), airResist(airResistance), engine(enginePower), tireFriction(tireSlippingPoint), steerReactive(steerReactiveness)
{
	controller = NULL;
}


cCar::~cCar()
{
}

void cCar::addImpulse(fpoint force)
{
	// Using the overwritten operators of fpoint
	// to add the external force to the impulse.
	velocity += force / mass;
}

void cCar::accelerate(float force)
{
	// Adding a force in the forward direction of the sprite.
	acceleration += forwardVector() * (force * engine / mass) / ((damage+200)/200);
}

void cCar::steer(float angle)
{
	// Adding angle to the steering angle.
	// Will be reset on update.
	steering = angle;
}

void cCar::update(double deltaTime)
{
	// Storing the position before this update.
	lastPos = physPos;
	
	// Calculating velocity.
	// Adding forces that act at one point in time.
	//velocity += impulse;
	// Adding forces that act over the whole frame.
	velocity += acceleration * deltaTime;
	// Subtracting air resistance.
	velocity -= velocity*(airResist/mass)*deltaTime;
	
	// Calculating new rotation.
	// velocity.length() is the current speed
	spriteRotationAngle += steering * steerReactive * sqrt(velocity.length())* deltaTime;

	// Calculating new position.
	// Calculating effect of tire friction, between 0 and 1.
	float slippingFactor = min(1, max(0, (velocity.length() * deltaTime / tireFriction)));
	// The velocity that the car actually travels at.
	// Different than the variable "velocity", since that one does not account for tire friction.
	// Interpolates between velocity independent of tires and forward velocity that is fully dependent on tires.
	fpoint effectiveVel = velocity * slippingFactor + calculateForwardVelocity(velocity) * (1 - slippingFactor);
	
	// Easing the velocity to the effective velocity.
	// Comparable with loosing centrifugal force due to tire friction.
	velocity = velocity / (2) + effectiveVel / (2);

	// Calculating the physics position based on the vlocity.
	physPos += effectiveVel * deltaTime;
	
	// Apply the physical position to the sprite pixel position.
	transform.x = physPos.X;
	transform.y = physPos.Y;

	// Resetting acceleration.
	acceleration = { 0,0 };
	// Resetting steering.
	steering = 0;

	// Calling base class update.
	cSpriteSheet::update(deltaTime);
}

void cCar::setSpritePos(SDL_Point worldPos)
{
	physPos.X = worldPos.x;
	physPos.Y = worldPos.y;
	cSprite::setSpritePos(worldPos);
}

void cCar::onCollision(CollisionMessage message, fpoint impulse)
{

	// If this car is controlled by someone and it has reached the target.
	if (controller && message == CHECKPOINT)
	{
		cout << "Reached finish\n";
		// Inform this someone that he reached the safehouse.
		controller->OnReachedCheckpoint();
	}
	else if (message == COLLISION)
	{
		cSoundMgr::getInstance()->getSnd("crash_fx")->play(0);

		// Resetting the position from the last update.
		// This helps avoiding cars getting stuck within each other.
		physPos = lastPos;

		// Calculating force
		fpoint force = impulse - getImpulse()*1.1;

		// Applying force
		addImpulse(force);

		damage += force.length();
		setState(damage / 300);
	}

}



fpoint cCar::getImpulse()
{
	return calculateForwardVelocity(velocity) * mass;
}

void cCar::setController(cPlayer * c)
{
	controller = c;
}





fpoint cCar::forwardVector()
{
	fpoint v;
	v.X = -sin(spriteRotationAngle * 2 * PI / 360);
	v.Y = cos(spriteRotationAngle * 2 * PI / 360);
	return v;
}

fpoint cCar::calculateForwardVelocity(fpoint velocity)
{
	fpoint forwards = forwardVector();
	return forwards * forwards.dotProduct(&velocity);
}
