#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>

using namespace ao;

class Asteroid
{
public:
	Asteroid(float x, float y, float radius, float rotation, float rotationSpeed,
			 float velocity, float movementDirection);
	~Asteroid();
	void updateShape();
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	void checkOnScreen();
	static Asteroid* createRandomAsteroid(float x, float y, float radius);
	vec2* getShape() { return shape; }
public:
	vec2 position;
	vec2 velocity;
	vec2* shape;
	float* vertexDistances;
	float radius;
	float rotation;
	float rotationSpeed;
public:
	const int ASTEROID_VERTICES = 10;
};