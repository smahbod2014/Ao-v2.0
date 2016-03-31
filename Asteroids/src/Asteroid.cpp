#include "Asteroid.h"
#include <Ao/Graphics/Color.h>
#include <Ao/Graphics/Window.h>
#include "Bullet.h"

const int Asteroid::ASTEROID_VERTICES = 10;
AsteroidData Asteroid::largeAsteroidData;
AsteroidData Asteroid::mediumAsteroidData;
AsteroidData Asteroid::smallAsteroidData;

Asteroid::Asteroid(float x, float y, float rotation, float movementDirection, AsteroidType type)
{
	AsteroidData* data = nullptr;
	switch (type)
	{
	case AsteroidType::LARGE:
		data = &largeAsteroidData;
		break;
	case AsteroidType::MEDIUM:
		data = &mediumAsteroidData;
		break;
	case AsteroidType::SMALL:
		data = &smallAsteroidData;
		break;
	}

	rotationSpeed = MathUtils::randomFloat(data->rotationSpeedMin, data->rotationSpeedMax);
	float velocity = MathUtils::randomFloat(data->velocityMin, data->velocityMax);
	radius = data->radius;

	position.x = x;
	position.y = y;
	this->velocity.x = cosf(toRadians(movementDirection)) * velocity;
	this->velocity.y = sinf(toRadians(movementDirection)) * velocity;
	this->rotation = rotation;
	this->rotationSpeed = rotationSpeed;
	this->type = type;

	shape = new vec2[ASTEROID_VERTICES];
	vertexDistances = new float[ASTEROID_VERTICES];
	for (int i = 0; i < ASTEROID_VERTICES; i++)
		vertexDistances[i] = MathUtils::randomFloat(radius / 2, radius);
	updateShape();
}

Asteroid::~Asteroid()
{
	delete[] shape;
	delete[] vertexDistances;
}

Asteroid* Asteroid::createRandomAsteroid(float x, float y, AsteroidType type)
{
	float rotation = MathUtils::randomFloat(0, 360);
	float velocity = MathUtils::randomFloat(5, 20);
	//velocity = 100;
	float movementDirection = MathUtils::randomFloat(0, 360);
	return new Asteroid(x, y, rotation, movementDirection, type);
}

void Asteroid::updateShape()
{
	for (int i = 0; i < ASTEROID_VERTICES; i++)
	{
		float theta = i * (2 * PI / ASTEROID_VERTICES) + toRadians(rotation);
		shape[i].x = position.x + cosf(theta) * vertexDistances[i];
		shape[i].y = position.y + sinf(theta) * vertexDistances[i];
	}
}

void Asteroid::update(float dt)
{
	rotation += rotationSpeed * dt;
	position += velocity * dt;
	checkOnScreen();
	if (rotation >= 360)
		rotation -= 360;
	if (rotation < 0)
		rotation += 360;
	updateShape();
}

void Asteroid::render(ShapeRenderer2D* renderer)
{
	for (int i = 0; i < ASTEROID_VERTICES; i++)
		renderer->drawLine(shape[i], shape[(i + 1) % ASTEROID_VERTICES], Color::WHITE);
}

void Asteroid::checkOnScreen()
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

int Asteroid::destroy(std::vector<Asteroid*>& asteroids, std::vector<Bullet*>& particles)
{
	//play pretty particle effect
	//remember to award points too
	const int numParticles = 12;
	for (int i = 0; i < numParticles; i++)
	{
		Bullet* b = new Bullet(position, toDegrees(i * (2 * PI / numParticles)), 75, 700);
		b->setIsParticle(true);
		particles.push_back(b);
	}

	switch (type)
	{
	case AsteroidType::LARGE:
		for (int i = 0; i < largeAsteroidData.asteroidsOnDeath; i++)
			asteroids.push_back(Asteroid::createRandomAsteroid(position.x, position.y, AsteroidType::MEDIUM));
		return largeAsteroidData.score;
	case AsteroidType::MEDIUM:
		for (int i = 0; i < mediumAsteroidData.asteroidsOnDeath; i++)
			asteroids.push_back(Asteroid::createRandomAsteroid(position.x, position.y, AsteroidType::SMALL));
		return mediumAsteroidData.score;
	case AsteroidType::SMALL:
		return smallAsteroidData.score;
	}
}

bool Asteroid::isHitByBullet(Bullet* b)
{
	//shapesIntersect should be enough...may have to use linesIntersect for the small asteroids
	return MathUtils::shapesIntersect(b->getShape(), b->getNumVertices(), shape, ASTEROID_VERTICES);
}

void Asteroid::init()
{	
	largeAsteroidData.asteroidsOnDeath = 2;
	largeAsteroidData.velocityMin = 10;
	largeAsteroidData.velocityMax = 25;
	largeAsteroidData.rotationSpeedMin = -20;
	largeAsteroidData.rotationSpeedMax = 20;
	largeAsteroidData.radius = 80;
	largeAsteroidData.score = 5;

	mediumAsteroidData.asteroidsOnDeath = 2;
	mediumAsteroidData.velocityMin = 30;
	mediumAsteroidData.velocityMax = 45;
	mediumAsteroidData.rotationSpeedMin = -45;
	mediumAsteroidData.rotationSpeedMax = 45;
	mediumAsteroidData.radius = 40;
	mediumAsteroidData.score = 10;

	smallAsteroidData.asteroidsOnDeath = 0;
	smallAsteroidData.velocityMin = 50;
	smallAsteroidData.velocityMax = 70;
	smallAsteroidData.rotationSpeedMin = -60;
	smallAsteroidData.rotationSpeedMax = 60;
	smallAsteroidData.radius = 20;
	smallAsteroidData.score = 20;
}