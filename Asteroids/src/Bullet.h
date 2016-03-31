#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>

using namespace ao;

class Bullet
{
public:
	Bullet(const vec2& position, float degreesDirection);
	Bullet(const vec2& position, float degreesDirection, float velocity, unsigned long duration);
	~Bullet();
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	void updateShape();
	void checkOnScreen();
	vec2* getShape() { return shape; }
	void setIsParticle(bool particle) { isParticle = particle; }
	inline bool isDead() const { return dead; }
	inline int getNumVertices() const { return numVertices; }
private:
	vec2 position;
	vec2 velocity;
	unsigned long removalTime;
	unsigned long timeCreated;
	bool dead = false;
	vec2* shape;
	int numVertices;
	float alpha = 1.0f;
	bool isParticle = false;
	unsigned int color;
public:
	static const unsigned long BULLET_DURATION;
	static const float BULLET_VELOCITY;
	static const float BULLET_RADIUS;
};

