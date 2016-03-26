#include "Asteroid.h"
#include <Ao/Graphics/Color.h>
#include <Ao/Graphics/Window.h>

Asteroid::Asteroid(float x, float y, float radius, float rotation, float rotationSpeed,
				   float velocity, float movementDirection)
{
	position.x = x;
	position.y = y;
	this->velocity.x = cosf(toRadians(movementDirection)) * velocity;
	this->velocity.y = sinf(toRadians(movementDirection)) * velocity;
	this->rotation = rotation;
	this->rotationSpeed = rotationSpeed;
	this->radius = radius;

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

Asteroid* Asteroid::createRandomAsteroid(float x, float y, float radius)
{
	float rotation = MathUtils::randomFloat(0, 360);
	float rotationSpeed = MathUtils::randomFloat(10, 20);
	float velocity = MathUtils::randomFloat(5, 20);
	velocity = 100;
	float movementDirection = MathUtils::randomFloat(0, 360);
	return new Asteroid(x, y, radius, rotation, rotationSpeed, velocity, movementDirection);
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