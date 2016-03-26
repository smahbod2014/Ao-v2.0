#include "Bullet.h"
#include <Ao/Managers/Timer.h>
#include <Ao/Graphics/Color.h>

const float Bullet::BULLET_VELOCITY = 300.0f;
const unsigned long Bullet::BULLET_DURATION = 1000;

Bullet::Bullet(const vec2& position, float degreesDirection)
	: Bullet(position, degreesDirection, BULLET_VELOCITY, BULLET_DURATION)
{

}

Bullet::Bullet(const vec2& position, float degreesDirection, float velocity, unsigned long duration)
{
	this->position.set(position);
	this->velocity.setPolar(degreesDirection, velocity);
	removalTime = Timer::getTime() + duration;
}

void Bullet::update(float dt)
{
	if (!dead)
	{
		position += velocity * dt;
		if (Timer::getTime() >= removalTime)
			dead = true;
	}
}

void Bullet::render(ShapeRenderer2D* renderer)
{
	renderer->drawCircle(position.x, position.y, 2, Color::WHITE);
}