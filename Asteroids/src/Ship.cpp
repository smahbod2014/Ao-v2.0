#include "Ship.h"
#include <Ao/Graphics/ShapeRenderer2D.h>
#include <Ao/Managers/Input.h>
#include <Ao/Math/MathUtils.h>
#include <Ao/Graphics/Color.h>
#include <Ao/Graphics/Window.h>
#include <Ao/Managers/SoundManager.h>
#include <Ao/Audio/Sound.h>
#include "Bullet.h"
#include "Asteroid.h"
#include "FlyingSaucer.h"

const float Ship::TURN_RATE = 150.0f;
const float Ship::NOSE_RADIUS = 24.0f;
const float Ship::WING_RADIUS = 24.0f;
const float Ship::ENGINE_RADIUS = 15.0f;
const float Ship::WING_ANGLE = 144.0f;
const float Ship::ACCELERATION = 200.0f;
const float Ship::MAX_VELOCITY = 200.0f;
const float Ship::DEATH_SPREAD_SPEED = 20.0f;
const unsigned long Ship::DEATH_TIME = 2500;
const unsigned long Ship::INVINCIBILITY_TIME = 3000;
const unsigned long Ship::SHOOT_COOLDOWN = 200;

Ship::Ship(float x, float y, float rotation)
{
	position = vec2(x, y);
	this->rotation = rotation;
	shape = new vec2[4];
	deathShape = new vec2[8];
	flameShape = new vec2[3];
	updateShape();
}

Ship::~Ship()
{
	delete[] shape;
	delete[] flameShape;
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

void Ship::updateFlameShape()
{
	flameShape[0] = vec2::polar(rotation - 150, 19) + position;
	flameShape[1] = vec2::polar(rotation - 180, 25 + acceleratingTimer * 50) + position;
	flameShape[2] = vec2::polar(rotation + 150, 19) + position;
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
		if (Timer::getTime() >= thrusterSoundTime)
			SoundManager::getSound("thruster")->play();
		if (thrusterSoundTime < Timer::getTime())
			thrusterSoundTime = Timer::getTime() + 418;
		float rad = toRadians(rotation);
		velocity.x += cosf(rad) * ACCELERATION * dt;
		velocity.y += sinf(rad) * ACCELERATION * dt;
		acceleratingTimer += dt;
		if (acceleratingTimer > 0.1f)
			acceleratingTimer = 0;
		if (velocity.length() > MAX_VELOCITY)
			velocity = velocity.normalized() * MAX_VELOCITY;
		updateFlameShape();
		isAccelerating = true;
	}
	else
	{
		acceleratingTimer = 0;
		isAccelerating = false;
	}
	if (Input::isKeyDown(AO_KEY_SPACE))
	{
		spaceKeyHeld = true;
		if (shootTime < Timer::getTime())
		{
			shootTime = Timer::getTime() + SHOOT_COOLDOWN;
			fire();
		}
	}
	if (!Input::isKeyDown(AO_KEY_SPACE) && spaceKeyHeld)
	{
		spaceKeyHeld = false;
		shootTime = Timer::getTime();
	}
}

void Ship::fire()
{
	Bullet* bullet = new Bullet(position + vec2::polar(rotation, NOSE_RADIUS), rotation);
	bullets.push_back(bullet);
	SoundManager::getSound("shoot")->play();
}

void Ship::update(float dt)
{
	if (dead)
	{
		for (int i = 0; i < 4; i++)
		{
			vec2 lineCenter = (deathShape[i * 2] + deathShape[i * 2 + 1]) / 2;
			float theta = atan2f(lineCenter.y - position.y, lineCenter.x - position.x);
			vec2 pushOut = vec2::polar(theta, DEATH_SPREAD_SPEED, false) * dt;
			deathShape[i * 2] += pushOut;
			deathShape[i * 2 + 1] += pushOut;
		}
	}
	else
	{
		position += velocity * dt;
		if (invincible && Timer::getTime() >= invincibilityTime)
		{
			invincible = false;
			color = Color::WHITE;
		}
	}

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

	if (!dead)
		updateShape();
}

void Ship::render(ShapeRenderer2D* renderer)
{

	if (!dead)
	{
		for (int i = 0; i < 4; i++)
			renderer->drawLine(shape[i], shape[(i + 1) % 4], color);
		if (isAccelerating)
		{
			for (int i = 0; i < 3; i++)
				renderer->drawLine(flameShape[i], flameShape[(i + 1) % 3], color);
		}
	}
	else
		for (int i = 0; i < 8; i += 2)
			renderer->drawLine(deathShape[i], deathShape[i + 1], color);

	for (Bullet* bullet : bullets)
		bullet->render(renderer);
}

bool Ship::isHitByAsteroid(Asteroid* asteroid)
{
	bool intersected = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < Asteroid::ASTEROID_VERTICES; j++)
		{
			if (MathUtils::linesIntersect(shape[i], shape[(i + 1) % 4],
				asteroid->getShape()[j], asteroid->getShape()[(j + 1) % Asteroid::ASTEROID_VERTICES]))
			{
				intersected = true;
				break;
			}
		}
		if (intersected)
			break;
	}

	if (!intersected)
	{
		intersected = MathUtils::shapesIntersect(shape, 4, asteroid->getShape(), Asteroid::ASTEROID_VERTICES);
	}

	return intersected;
}

bool Ship::isHitByFlyingSaucer(FlyingSaucer* flyingSaucer)
{
	bool intersected = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < flyingSaucer->getShape().size(); j++)
		{
			if (MathUtils::linesIntersect(shape[i], shape[(i + 1) % 4],
				flyingSaucer->getShape()[j], flyingSaucer->getShape()[(j + 1) % flyingSaucer->getShape().size()]))
			{
				intersected = true;
				break;
			}
		}
		if (intersected)
			break;
	}

	if (!intersected)
	{
		intersected = MathUtils::shapesIntersect(shape, 4, flyingSaucer->getShape().data(), flyingSaucer->getShape().size());
	}

	return intersected;
}

void Ship::destroy()
{
	dead = true;
	respawnTime = Timer::getTime() + DEATH_TIME;
	for (int i = 0; i < 4; i++)
	{
		deathShape[i * 2 + 0].x = shape[i].x;
		deathShape[i * 2 + 0].y = shape[i].y;
		deathShape[i * 2 + 1].x = shape[(i + 1) % 4].x;
		deathShape[i * 2 + 1].y = shape[(i + 1) % 4].y;
	}
}

void Ship::respawn()
{
	dead = false;
	position.set(Window::getWidth() / 2, Window::getHeight() / 2);
	velocity.set(0, 0);
	invincibilityTime = Timer::getTime() + INVINCIBILITY_TIME;
	color = Color::GREEN;
	invincible = true;
}

bool Ship::isHitByBullet(Bullet* b)
{
	return MathUtils::shapesIntersect(b->getShape(), b->getNumVertices(), shape, 4);
}