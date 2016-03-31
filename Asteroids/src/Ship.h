#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>
#include <Ao/Graphics/Color.h>
#include <Ao/Managers/Timer.h>

class Bullet;
class Asteroid;
class FlyingSaucer;

using namespace ao;

class Ship
{
public:
	Ship(float x, float y, float rotation);
	~Ship();
	void updateShape();
	void updateFlameShape();
	void input(float dt);
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	bool isHitByAsteroid(Asteroid* asteroid);
	bool isHitByFlyingSaucer(FlyingSaucer* flyingSaucer);
	bool isHitByBullet(Bullet* b);
	void destroy();
	void respawn();
	void setColor(unsigned int c) { color = c; }
	vec2* getShape() { return shape; }
	const vec2& getPosition() const { return position; }
	std::vector<Bullet*>& getBullets() { return bullets; }
	inline bool isDead() const { return dead; }
	inline bool isInvincible() const { return invincible; }
	inline bool isReadyToRespawn() const { return Timer::getTime() >= respawnTime; }
private:
	void fire();
private:
	vec2 position;
	vec2 velocity;
	vec2* flameShape;
	vec2* shape;
	vec2* deathShape;
	float rotation;
	bool dead = false;
	bool invincible = false;
	bool spaceKeyHeld = false;
	unsigned long respawnTime; //finish this
	unsigned long invincibilityTime;
	unsigned long shootTime;
	std::vector<Bullet*> bullets;
	unsigned int color = Color::WHITE;
	float acceleratingTimer;
	unsigned long thrusterSoundTime;
	bool isAccelerating = false;
public:
	static const float TURN_RATE;
	static const float NOSE_RADIUS;
	static const float WING_RADIUS;
	static const float ENGINE_RADIUS;
	static const float WING_ANGLE;
	static const float ACCELERATION;
	static const float MAX_VELOCITY;
	static const float DEATH_SPREAD_SPEED;
	static const unsigned long DEATH_TIME;
	static const unsigned long INVINCIBILITY_TIME;
	static const unsigned long SHOOT_COOLDOWN;
};