#include "cCar.h"




cCar::cCar(float mass, float airResistance, float enginePower, float tireSlippingPoint, float steerReactiveness): mass(mass), airResist(airResistance), engine(enginePower), slipping(tireSlippingPoint), steerReactive(steerReactiveness)
{
}


cCar::~cCar()
{
}

void cCar::addImpulse(fpoint force)
{
	// Using the overwritten operators of fpoint
	// to add the external force to the impulse.
	impulse += force / mass;
}

void cCar::accelerate(float force)
{
	// Adding a force in the forward direction of the sprite.
	acceleration += forwardVector() * force * engine / mass;
}

void cCar::steer(float angle)
{
	// Adding angle to the steering angle.
	// Will be reset on update.
	steering = angle;
}

void cCar::update(double deltaTime)
{
	// Calculating velocity.
	// Adding forces that act at one point in time.
	velocity += impulse;
	// Adding forces that act over the whole frame.
	velocity += acceleration * deltaTime;
	// Subtracting air resistance.
	velocity -= velocity*(airResist*deltaTime);
	
	// Calculating new rotation.
	// velocity.length() is the current speed
	spriteRotationAngle += steering * steerReactive * sqrt(velocity.length())* deltaTime;

	// Calculating new position.
	// If velocity is over tire slipping point,
	// the velocity is simply applied in both dimentions.
	if (velocity.length()* deltaTime > slipping)
	{
		//physPos += velocity * deltaTime;
		//cout << "slipping\n";
	}
	// Else the velocity is only applyied in the forward direction.
	else
	{
		//cout << ".\n";
		fpoint forwards = forwardVector();
		velocity = forwards * forwards.dotProduct(&velocity);
	}
	physPos += velocity * deltaTime;

	// Apply the physical position to the sprite pixel position.
	transform.x = physPos.X;
	transform.y = physPos.Y;

	// Resetting impulse.
	impulse = { 0,0 };
	// Resetting acceleration.
	acceleration = { 0,0 };
	// Resetting steering.
	steering = 0;


	cSpriteAnimation::update(deltaTime);
}

void cCar::setSpritePos(SDL_Point worldPos)
{
	physPos.X = worldPos.x;
	physPos.Y = worldPos.y;
	cSprite::setSpritePos(worldPos);
}

void cCar::onCollision(cCollider * other)
{
	velocity = { 0,0 };
	addImpulse(other->getVelocity()*other->getMass());
}

fpoint cCar::getVelocity()
{
	return velocity;
}

float cCar::getMass()
{
	return mass;
}

float cCar::getAngle()
{
	return spriteRotationAngle;
}

SDL_Point cCar::getPosition()
{
	SDL_Rect r = getSpritePos();
	return{ r.x, r.y };
}



fpoint cCar::forwardVector()
{
	fpoint v;
	v.X = -sin(spriteRotationAngle * 2 * PI / 360);
	v.Y = cos(spriteRotationAngle * 2 * PI / 360);
	return v;
}