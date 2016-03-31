#pragma once

#include <vector>
#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>

using namespace ao;

class Ship;
class Bullet;
class Asteroid;

enum class FlyingSaucerType { LARGE, SMALL };
class FlyingSaucer
{
public:
	FlyingSaucer(bool leftSide, float y, float speed, bool willGoUp, FlyingSaucerType type, Ship* player);
	void updateShape();
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	void checkOnScreen();
	void fire();
	bool isHitByBullet(Bullet* bullet);
	bool isHitByAsteroid(Asteroid* asteroid);
	int destroy(std::vector<Bullet*>& particles);
	static FlyingSaucer* createRandomFlyingSaucer(Ship* player);
	inline bool isDead() const { return dead; }
	std::vector<Bullet*>& getBullets() { return bullets; }
	std::vector<vec2>& getShape() { return shape; }
private:
	vec2 position;
	std::vector<Bullet*> bullets;
	std::vector<vec2> shape;
	FlyingSaucerType type;
	bool willGoUp;
	float movementDirection;
	float speed;
	float distanceTraveled;
	int pathIndex;
	bool dead;
	bool leftSide;
	unsigned long fireTime;
	unsigned long soundTime;
	Ship* player;
	std::vector<float> pathDistances;
	std::vector<float> pathAngles;
public:
	static const float SIDE_RADIUS;
	static const float TOP_RADIUS;
	static const float TOP_ANGLE;
	static const unsigned long FIRE_DELAY;
	static const unsigned long LARGE_SAUCER_SOUND_TIME;
	static const unsigned long SMALL_SAUCER_SOUND_TIME;
};