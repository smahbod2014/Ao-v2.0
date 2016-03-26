#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>

using namespace ao;

class Bullet
{
public:
	Bullet(const vec2& position, float degreesDirection);
	Bullet(const vec2& position, float degreesDirection, float velocity, unsigned long duration);
	~Bullet() {}
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	inline bool isDead() const { return dead; }
private:
	vec2 position;
	vec2 velocity;
	unsigned long removalTime;
	bool dead = false;

	static const unsigned long BULLET_DURATION;
	static const float BULLET_VELOCITY;
};