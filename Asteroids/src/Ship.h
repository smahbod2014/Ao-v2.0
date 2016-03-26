#pragma once

#include <Ao/Math/vec2.h>
#include <Ao/Graphics/ShapeRenderer2D.h>
#include <Ao/Graphics/Color.h>

class Bullet;

using namespace ao;

class Ship
{
public:
	Ship(float x, float y, float rotation);
	~Ship();
	void updateShape();
	void input(float dt);
	void update(float dt);
	void render(ShapeRenderer2D* renderer);
	void setColor(unsigned int c) { color = c; }
	vec2* getShape() { return shape; }
private:
	void fire();
private:
	vec2 position;
	vec2 velocity;
	vec2* shape;
	float rotation;
	std::vector<Bullet*> bullets;
	unsigned int color = Color::WHITE;
public:
	const float TURN_RATE = 120.0f;
	const float NOSE_RADIUS = 24.0f;
	const float WING_RADIUS = 24.0f;
	const float ENGINE_RADIUS = 15.0f;
	const float WING_ANGLE = 144.0f;
	const float ACCELERATION = 125.0f;
	const float MAX_VELOCITY = 200;
};