#include "Bullet.h"
#include <Ao/Managers/Timer.h>
#include <Ao/Graphics/Color.h>
#include <Ao/Graphics/Window.h>

const float Bullet::BULLET_VELOCITY = 400.0f;
const unsigned long Bullet::BULLET_DURATION = 1100;
const float Bullet::BULLET_RADIUS = 2.0f;

Bullet::Bullet(const vec2& position, float degreesDirection)
	: Bullet(position, degreesDirection, BULLET_VELOCITY, BULLET_DURATION)
{
	
}

Bullet::Bullet(const vec2& position, float degreesDirection, float velocity, unsigned long duration)
{
	this->position.set(position);
	this->velocity.setPolar(degreesDirection, velocity);
	timeCreated = Timer::getTime();
	removalTime = timeCreated + duration;
	color = Color::WHITE;

	numVertices = 6;
	shape = new vec2[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		float theta = i * (2 * PI / numVertices);
		shape[i].setPolar(toDegrees(theta), BULLET_RADIUS);
		shape[i] += position;
	}
}

Bullet::~Bullet()
{
	delete[] shape;
}

void Bullet::updateShape()
{
	for (int i = 0; i < numVertices; i++)
	{
		float theta = i * (2 * PI / 6);
		shape[i].setPolar(toDegrees(theta), BULLET_RADIUS);
		shape[i] += position;
	}
}

void Bullet::update(float dt)
{
	if (!dead)
	{
		position += velocity * dt;
		checkOnScreen();
		updateShape();
		if (isParticle)
		{
			alpha = 1.0f - (float)(Timer::getTime() - timeCreated) / (removalTime - timeCreated);
			color = Color::colorAlpha(color, alpha);
		}
		if (Timer::getTime() >= removalTime)
			dead = true;
	}
}

void Bullet::render(ShapeRenderer2D* renderer)
{
	renderer->drawCircle(position.x, position.y, 2, color);
}

void Bullet::checkOnScreen()
{
	//place asteroid back in bounds
	if (position.x > Window::getWidth())
		position.x = 0;
	if (position.x < 0)
		position.x = Window::getWidth();
	if (position.y > Window::getHeight())
		position.y = 0;
	if (position.y < 0)
		position.y = Window::getHeight();
}