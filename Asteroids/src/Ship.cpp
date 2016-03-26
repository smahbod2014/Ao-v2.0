#include "Ship.h"
#include <Ao/Graphics/ShapeRenderer2D.h>
#include <Ao/Managers/Input.h>
#include <Ao/Math/MathUtils.h>
#include <Ao/Graphics/Color.h>
#include <Ao/Graphics/Window.h>
#include "Bullet.h"

Ship::Ship(float x, float y, float rotation)
{
	position = vec2(x, y);
	this->rotation = rotation;
	shape = new vec2[4];
	updateShape();
}

Ship::~Ship()
{
	delete[] shape;
}

void Ship::updateShape()
{
	float noseRotation = toRadians(rotation);
	shape[0].x = position.x + cosf(noseRotation) * NOSE_RADIUS;
	shape[0].y = position.y + sinf(noseRotation) * NOSE_RADIUS;

	float leftWingRotation = toRadians(rotation + WING_ANGLE);
	shape[1].x = position.x + cosf(leftWingRotation) * WING_RADIUS;
	shape[1].y = position.y + sinf(leftWingRotation) * WING_RADIUS;

	float engineRotation = toRadians(rotation + 180);
	shape[2].x = position.x + cosf(engineRotation) * ENGINE_RADIUS;
	shape[2].y = position.y + sinf(engineRotation) * ENGINE_RADIUS;

	float rightWingRotation = toRadians(rotation - WING_ANGLE);
	shape[3].x = position.x + cosf(rightWingRotation) * WING_RADIUS;
	shape[3].y = position.y + sinf(rightWingRotation) * WING_RADIUS;
}

void Ship::input(float dt)
{
	if (Input::isKeyDown(AO_KEY_LEFT))
	{
		rotation += TURN_RATE * dt;
		if (rotation >= 360)
			rotation -= 360;
	}
	if (Input::isKeyDown(AO_KEY_RIGHT))
	{
		rotation -= TURN_RATE * dt;
		if (rotation < 0)
			rotation += 360;
	}
	if (Input::isKeyDown(AO_KEY_UP))
	{
		float rad = toRadians(rotation);
		velocity.x += cosf(rad) * ACCELERATION * dt;
		velocity.y += sinf(rad) * ACCELERATION * dt;
		if (velocity.length() > MAX_VELOCITY)
			velocity = velocity.normalized() * MAX_VELOCITY;
	}
	if (Input::isKeyJustPressed(AO_KEY_SPACE))
	{
		fire();
	}
}

void Ship::fire()
{
	Bullet* bullet = new Bullet(position, rotation);
	bullets.push_back(bullet);
}

void Ship::update(float dt)
{
	position += velocity * dt;
	for (int i = bullets.size() - 1; i >= 0; i--)
	{
		bullets[i]->update(dt);
		if (bullets[i]->isDead())
		{
			Bullet* b = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete b;
		}
	}

	//place ship back in bounds
	if (position.x > Window::getWidth())
		position.x = 0;
	if (position.x < 0)
		position.x = Window::getWidth();
	if (position.y > Window::getHeight())
		position.y = 0;
	if (position.y < 0)
		position.y = Window::getHeight();

	updateShape();
}

void Ship::render(ShapeRenderer2D* renderer)
{
	for (int i = 0; i < 4; i++)
		renderer->drawLine(shape[i], shape[(i + 1) % 4], color);

	for (Bullet* bullet : bullets)
		bullet->render(renderer);
}