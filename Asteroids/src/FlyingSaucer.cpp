#include "FlyingSaucer.h"
#include <Ao/Graphics/Window.h>
#include <Ao/Math/MathUtils.h>
#include <Ao/Graphics/Color.h>
#include <Ao/Managers/Timer.h>
#include <Ao/Managers/SoundManager.h>
#include <Ao/Audio/Sound.h>
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"

const float FlyingSaucer::SIDE_RADIUS = 30.0f;
const float FlyingSaucer::TOP_RADIUS = 18.0f;
const float FlyingSaucer::TOP_ANGLE = 40.0f;
const unsigned long FlyingSaucer::FIRE_DELAY = 1500;
const unsigned long FlyingSaucer::LARGE_SAUCER_SOUND_TIME = 650;
const unsigned long FlyingSaucer::SMALL_SAUCER_SOUND_TIME = 395;

FlyingSaucer::FlyingSaucer(bool leftSide, float y, float speed, bool willGoUp, FlyingSaucerType type, Ship* player)
{
	this->player = player;
	this->leftSide = leftSide;
	if (leftSide)
	{
		position.set(0, y);
		this->speed = speed;
	}
	else
	{
		position.set(Window::getWidth(), y);
		this->speed = -speed;
	}
	this->willGoUp = willGoUp;
	this->type = type;
	pathAngles.push_back(0);
	if (willGoUp)
	{
		pathAngles.push_back(30);
	}
	else
	{
		pathAngles.push_back(-30);
	}
	pathAngles.push_back(0);
	float straightDistance = Window::getWidth() * 0.33f;
	pathDistances.push_back(straightDistance);
	pathDistances.push_back(straightDistance / sinf(toRadians(60)));
	pathDistances.push_back(straightDistance);
	for (int i = 0; i < 8; i++)
	{
		shape.push_back(vec2());
	}
	updateShape();
	fireTime = Timer::getTime() + FIRE_DELAY / 2;
}

void FlyingSaucer::updateShape()
{
	float sideRadius = SIDE_RADIUS;
	float topRadius = TOP_RADIUS;
	if (type == FlyingSaucerType::SMALL)
	{
		sideRadius *= 0.65f;
		topRadius *= 0.65f;
	}
	shape[0] = position + vec2::polar(0, sideRadius);
	shape[1] = position + vec2::polar(TOP_ANGLE, topRadius);
	shape[2] = position + vec2::polar(180 - TOP_ANGLE, topRadius);
	shape[3] = position + vec2::polar(180, sideRadius);
	shape[4] = position + vec2::polar(180 + TOP_ANGLE, topRadius);
	shape[5] = position + vec2::polar(-TOP_ANGLE, topRadius);
	shape[6] = position + vec2::polar(0, sideRadius);
	shape[7] = position + vec2::polar(180, sideRadius);
}

FlyingSaucer* FlyingSaucer::createRandomFlyingSaucer(Ship* player)
{
	bool leftSide = MathUtils::randomIntInclusive(0, 1) == 1;
	float y = MathUtils::randomFloat(0, Window::getHeight());
	float speed = MathUtils::randomFloat(140, 200);
	bool willGoUp = MathUtils::randomIntInclusive(0, 1) == 1;
	FlyingSaucerType type = MathUtils::randomIntInclusive(0, 1) == 1 ? FlyingSaucerType::LARGE : FlyingSaucerType::SMALL;
	return new FlyingSaucer(leftSide, y, speed, willGoUp, type, player);
}

void FlyingSaucer::update(float dt)
{
	if (!dead)
	{
		if (Timer::getTime() >= soundTime)
		{
			if (type == FlyingSaucerType::SMALL)
			{
				soundTime = Timer::getTime() + SMALL_SAUCER_SOUND_TIME;
				SoundManager::getSound("smallsaucer")->play();
			}
			else
			{
				soundTime = Timer::getTime() + LARGE_SAUCER_SOUND_TIME;
				SoundManager::getSound("largesaucer")->play();
			}
		}
		if (distanceTraveled >= pathDistances[pathIndex])
		{
			pathIndex++;
			distanceTraveled = 0;
		}

		if (pathIndex < pathDistances.size())
		{
			vec2 travelAmount = vec2::polar(pathAngles[pathIndex], speed * dt);
			position += travelAmount;
			distanceTraveled += travelAmount.length();
			checkOnScreen();
			updateShape();
			if (!player->isDead() && Timer::getTime() >= fireTime)
				fire();
		}
		else
		{
			dead = true;
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
}

void FlyingSaucer::render(ShapeRenderer2D* renderer)
{
	if (!dead)
		renderer->drawPolygon(shape, Color::WHITE);
	for (Bullet* bullet : bullets)
		bullet->render(renderer);
}

void FlyingSaucer::checkOnScreen()
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

void FlyingSaucer::fire()
{
	float theta = toRadians(MathUtils::randomFloat(0, 360));
	if (type == FlyingSaucerType::SMALL)
		theta = atan2f(player->getPosition().y - position.y, player->getPosition().x - position.x);
	Bullet* b = new Bullet(position, toDegrees(theta), Bullet::BULLET_VELOCITY / 2, Bullet::BULLET_DURATION * 2);
	bullets.push_back(b);
	fireTime = Timer::getTime() + FIRE_DELAY;
	SoundManager::getSound("saucershoot")->play();
}

int FlyingSaucer::destroy(std::vector<Bullet*>& particles)
{
	const int numParticles = 12;
	for (int i = 0; i < numParticles; i++)
	{
		Bullet* b = new Bullet(position, toDegrees(i * (2 * PI / numParticles)), 75, 700);
		b->setIsParticle(true);
		particles.push_back(b);
	}
	dead = true;

	if (type == FlyingSaucerType::LARGE)
		return 100;
	else
		return 250;
}

bool FlyingSaucer::isHitByBullet(Bullet* b)
{
	return MathUtils::shapesIntersect(b->getShape(), b->getNumVertices(), shape.data(), shape.size());
}

bool FlyingSaucer::isHitByAsteroid(Asteroid* asteroid)
{
	bool intersected = false;
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < Asteroid::ASTEROID_VERTICES; j++)
		{
			if (MathUtils::linesIntersect(shape[i], shape[(i + 1) % shape.size()],
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
		intersected = MathUtils::shapesIntersect(shape.data(), shape.size(), asteroid->getShape(), Asteroid::ASTEROID_VERTICES);
	}

	return intersected;
}