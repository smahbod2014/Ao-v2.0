#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>

using namespace ao;

struct AsteroidData
{
	int asteroidsOnDeath;
	int score;
	float velocityMin, velocityMax;
	float rotationSpeedMin, rotationSpeedMax;
	float radius;
};

class Bullet;
enum class AsteroidType { LARGE, MEDIUM, SMALL };
class Asteroid
{
public:
	Asteroid(float x, float y, float rotation, float movementDirection, AsteroidType type);
	~Asteroid();
	void updateShape();
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	void checkOnScreen();
	int destroy(std::vector<Asteroid*>& asteroids, std::vector<Bullet*>& particles);
	bool isHitByBullet(Bullet* b);
	static Asteroid* createRandomAsteroid(float x, float y, AsteroidType type);
	vec2* getShape() { return shape; }
	static void init();
public:
	vec2 position;
	vec2 velocity;
	vec2* shape;
	float* vertexDistances;
	float radius;
	float rotation;
	float rotationSpeed;
	AsteroidType type;
	static AsteroidData largeAsteroidData;
	static AsteroidData mediumAsteroidData;
	static AsteroidData smallAsteroidData;
public:
	static const int ASTEROID_VERTICES;
};

