#include <iostream>
#include <Ao/Ao.h>
#include <Ao/Math/AoMath.h>
#include <Ao/Managers/AoManagers.h>
#include <Ao/Graphics/BatchRenderer2D.h>
#include <Ao/Graphics/ShapeRenderer2D.h>
#include <Ao/Graphics/Camera.h>
#include <Ao/Graphics/Sprite.h>
#include <Ao/Graphics/Group.h>
#include <Ao/Graphics/Label.h>
#include <Ao/Graphics/Color.h>

#include "Ship.h"
#include "Asteroid.h"

using namespace ao;

class Asteroids : public Ao
{
private:
	Camera* camera;
	ShapeRenderer2D* renderer;
	Ship* ship;
	std::vector<Asteroid*> asteroids;
public:
	Asteroids(const char* title, int width, int height) : Ao(title, width, height)
	{

	}

	virtual ~Asteroids()
	{
		
	}

	void init() override
	{
		camera = new Camera(Window::getWidth(), Window::getHeight());
		renderer = new ShapeRenderer2D();
		renderer->setProjectionMatrix(camera->getCombinedMatrix());
		ship = new Ship(Window::getWidth() / 2, Window::getHeight() / 2, 90);
		asteroids.push_back(Asteroid::createRandomAsteroid(200, 200, 80));
		asteroids[0]->velocity.set(0, 0);
	}

	void input(float dt) override
	{
		ship->input(dt);
	}

	void update(float dt) override
	{
		ship->update(dt);
		for (Asteroid* asteroid : asteroids)
			asteroid->update(dt);

		vec2* shipShape = ship->getShape();
		vec2* asteroidShape = asteroids[0]->getShape();
		bool intersected = false;
#if 0
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < asteroids[0]->ASTEROID_VERTICES; j++)
			{
				if (MathUtils::linesIntersect(shipShape[i], shipShape[(i + 1) % 4],
					asteroidShape[j], asteroidShape[(j + 1) % asteroids[0]->ASTEROID_VERTICES]))
				{
					intersected = true;
					break;
				}
			}
			if (intersected)
				break;
		}
#endif
		
		if (!intersected)
		{
			intersected = MathUtils::shapesIntersect(shipShape, 4, asteroidShape, asteroids[0]->ASTEROID_VERTICES);
		}
		
		if (intersected)
			ship->setColor(Color::RED);
		else
			ship->setColor(Color::WHITE);
	}


	void render() override
	{
		renderer->begin(ShapeType::Line);
		ship->render(renderer);
		for (Asteroid* asteroid : asteroids)
			asteroid->render(renderer);
		renderer->end();
	}

	void finish() override
	{

	}
};

int main(int argc, char* argv[])
{
	Asteroids game("Asteroids", 600, 600);
	game.start();
	return 0;
}