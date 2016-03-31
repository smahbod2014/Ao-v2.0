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
#include "Bullet.h"
#include "FlyingSaucer.h"


using namespace ao;

class Asteroids : public Ao
{
private:
	Camera* camera;
	ShapeRenderer2D* renderer;
	BatchRenderer2D* batchRenderer;
	Ship* ship;
	std::vector<Asteroid*> asteroids;
	std::vector<std::vector<vec2>> lifeDisplays;
	std::vector<Bullet*> particles;
	std::vector<FlyingSaucer*> flyingSaucers;
	int currentLevel;
	int livesRemaining;
	float currentScore;
	float livesScore;
	Label* scoreLabel;
	Label* levelLabel;
	Label* livesLabel;
	const unsigned long SAUCER_SPAWN_TIME = 20000;
	unsigned long saucerTime;
public:
	Asteroids(const char* title, int width, int height) : Ao(title, width, height)
	{

	}

	virtual ~Asteroids()
	{
		
	}

	float getMultiplier(int amount)
	{
		return amount * (1.0f + 0.1f * (currentLevel - 1));
	}

	void generateLevel(int level)
	{
		currentLevel = level;
		levelLabel->setText("Lv. " + std::to_string(currentLevel));
		//vec2 safeZonePos(ship->position, Window::getHeight() / 2);
		float safeZoneRadius = Asteroid::largeAsteroidData.radius * 3;
		int numAsteroids = 4 + level * 2;
		while (numAsteroids > 0)
		{
			vec2 location(
				MathUtils::randomFloat(0, Window::getWidth()),
				MathUtils::randomFloat(0, Window::getHeight()));
			if (!MathUtils::pointInsideCircle(ship->getPosition(), safeZoneRadius, location))
			{
				asteroids.push_back(Asteroid::createRandomAsteroid(location.x, location.y, AsteroidType::LARGE));
				numAsteroids--;
			}
		}
		saucerTime = Timer::getTime() + SAUCER_SPAWN_TIME;
	}

	void createLife(const vec2& position)
	{
		float rotation = 90.0f;
		float noseRotation = rotation;
		float leftWingRotation = rotation + Ship::WING_ANGLE;
		float engineRotation = rotation + 180;
		float rightWingRotation = rotation - Ship::WING_ANGLE;

		std::vector<vec2> shape;
		shape.push_back(vec2::polar(noseRotation, Ship::NOSE_RADIUS / 2) + position);
		shape.push_back(vec2::polar(leftWingRotation, Ship::WING_RADIUS / 2) + position);
		shape.push_back(vec2::polar(engineRotation, Ship::ENGINE_RADIUS / 2) + position);
		shape.push_back(vec2::polar(rightWingRotation, Ship::WING_RADIUS / 2) + position);
		lifeDisplays.push_back(shape);
		livesRemaining++;
		livesLabel->setText("x " + std::to_string(livesRemaining));
	}

	void setLives(int n)
	{
		livesRemaining = n;
		livesLabel->setText("x " + std::to_string(livesRemaining));
	}

	void updateLivesDisplay()
	{
		livesLabel->setText("x " + std::to_string(livesRemaining));
	}
	
	void updateScoreDisplay()
	{
		std::string s = std::to_string((int)currentScore);
		while (s.length() < 7)
			s = "0" + s;
		scoreLabel->setText(s);
	}

	void init() override
	{
		Asteroid::init();
		SoundManager::loadSound("thruster", "Sounds/thruster.ogg");
		SoundManager::loadSound("explode", "Sounds/explode.ogg");
		SoundManager::loadSound("shoot", "Sounds/shoot.ogg");
		SoundManager::loadSound("smallsaucer", "Sounds/smallsaucer.ogg");
		SoundManager::loadSound("largesaucer", "Sounds/largesaucer.ogg");
		SoundManager::loadSound("saucershoot", "Sounds/saucershoot.ogg");
		SoundManager::loadSound("extralife", "Sounds/extralife.ogg");
		camera = new Camera(Window::getWidth(), Window::getHeight());
		renderer = new ShapeRenderer2D();
		renderer->setProjectionMatrix(camera->getCombinedMatrix());
		batchRenderer = new BatchRenderer2D();
		batchRenderer->setProjectionMatrix(camera->getCombinedMatrix());
		ship = new Ship(Window::getWidth() / 2, Window::getHeight() / 2, 90);
		//asteroids.push_back(Asteroid::createRandomAsteroid(200, 200, AsteroidType::LARGE));
		//asteroids[0]->velocity.set(0, 0);
		scoreLabel = new Label("0000000", 15, Window::getHeight() - 30, "magnetob", Color::YELLOW);
		levelLabel = new Label("", 20, Window::getHeight() - 60, Color::YELLOW);
		livesLabel = new Label("x0", 50, Window::getHeight() - 90, Color::YELLOW);
		createLife(vec2(30, Window::getHeight() - 80));
		//createLife(vec2(50, Window::getHeight() - 80));
		//createLife(vec2(70, Window::getHeight() - 80));
		setLives(3);
		generateLevel(1);
	}

	void input(float dt) override
	{
		if (!ship->isDead())
			ship->input(dt);

		if (Input::isKeyDown(AO_KEY_T))
		{
			camera->rotate(vec3(0, 0, 1), 90 * dt);
			renderer->setProjectionMatrix(camera->getCombinedMatrix());
		}

		if (Input::isKeyJustPressed(AO_KEY_1))
			flyingSaucers.push_back(
			new FlyingSaucer(false, 500, 150, false, FlyingSaucerType::SMALL, ship));
		if (Input::isKeyJustPressed(AO_KEY_2))
		{
			ship->destroy();
		}
		if (Input::isKeyJustPressed(AO_KEY_3))
			flyingSaucers.push_back(
			new FlyingSaucer(false, 500, 150, false, FlyingSaucerType::LARGE, ship));
		if (Input::isKeyJustPressed(AO_KEY_4))
		{
			livesScore = 4000;
		}
	}

	void update(float dt) override
	{
		if (Timer::getTime() >= saucerTime)
		{
			flyingSaucers.push_back(FlyingSaucer::createRandomFlyingSaucer(ship));
			saucerTime = Timer::getTime() + SAUCER_SPAWN_TIME;
		}

		if (ship->isDead() && ship->isReadyToRespawn())
		{
			if (livesRemaining > 0)
			{
				ship->respawn();
				livesRemaining--;
				updateLivesDisplay();
				//lifeDisplays.pop_back();
			}
		}

		ship->update(dt);
		std::vector<Bullet*>& bullets = ship->getBullets();
		for (int i = asteroids.size() - 1; i >= 0; i--)
		{
			asteroids[i]->update(dt);
			for (int j = bullets.size() - 1; j >= 0; j--)
			{
				if (asteroids[i]->isHitByBullet(bullets[j]))
				{
					float amount = getMultiplier(asteroids[i]->destroy(asteroids, particles));
					currentScore += amount;
					livesScore += amount;
					updateScoreDisplay();
					delete asteroids[i];
					asteroids.erase(asteroids.begin() + i);
					delete bullets[j];
					bullets.erase(bullets.begin() + j);
					SoundManager::getSound("explode")->play();
					break;
				}
			}
		}

		for (int i = flyingSaucers.size() - 1; i >= 0; i--)
		{
			flyingSaucers[i]->update(dt);
			std::vector<Bullet*>& saucerBullets = flyingSaucers[i]->getBullets();
			for (int j = asteroids.size() - 1; j >= 0; j--)
			{
				for (int k = saucerBullets.size() - 1; k >= 0; k--)
				{
					if (asteroids[j]->isHitByBullet(saucerBullets[k]))
					{
						asteroids[j]->destroy(asteroids, particles);
						delete asteroids[j];
						asteroids.erase(asteroids.begin() + j);
						delete saucerBullets[k];
						saucerBullets.erase(saucerBullets.begin() + k);
						SoundManager::getSound("explode")->play();
						break;
					}
				}
			}
			if (flyingSaucers[i]->isDead() && flyingSaucers[i]->getBullets().size() == 0)
			{
				delete flyingSaucers[i];
				flyingSaucers.erase(flyingSaucers.begin() + i);
			}
			else if (!flyingSaucers[i]->isDead())
			{
				//bullet-saucer collision
				for (int j = bullets.size() - 1; j >= 0; j--)
				{
					if (flyingSaucers[i]->isHitByBullet(bullets[j]))
					{
						float amount = getMultiplier(flyingSaucers[i]->destroy(particles));
						currentScore += amount;
						livesScore += amount;
						updateScoreDisplay();
						delete bullets[j];
						bullets.erase(bullets.begin() + j);
						SoundManager::getSound("explode")->play();
						break;
					}
				}

				//saucer-asteroid collision
				for (int j = asteroids.size() - 1; j >= 0; j--)
				{
					if (!flyingSaucers[i]->isDead() && flyingSaucers[i]->isHitByAsteroid(asteroids[j]))
					{
						flyingSaucers[i]->destroy(particles);
						asteroids[j]->destroy(asteroids, particles);
						delete asteroids[j];
						asteroids.erase(asteroids.begin() + j);
						SoundManager::getSound("explode")->play();
						break;
					}
				}
			}
		}

		vec2* shipShape = ship->getShape();
		if (!ship->isDead() && !ship->isInvincible())
		{
			//ship-asteroid collision
			for (int i = asteroids.size() - 1; i >= 0; i--)
			{
				if (ship->isHitByAsteroid(asteroids[i]))
				{
					ship->destroy();
					asteroids[i]->destroy(asteroids, particles);
					delete asteroids[i];
					asteroids.erase(asteroids.begin() + i);
					SoundManager::getSound("explode")->play();
				}
			}

			//ship-flying saucer collision
			for (int i = flyingSaucers.size() - 1; i >= 0; i--)
			{
				if (!ship->isDead() && ship->isHitByFlyingSaucer(flyingSaucers[i]))
				{
					ship->destroy();
					flyingSaucers[i]->destroy(particles);
					SoundManager::getSound("explode")->play();
				}
			}
		}

		//flying-saucer-bullet to ship collision
		if (!ship->isDead() && !ship->isInvincible())
		{
			for (int i = 0; i < flyingSaucers.size(); i++)
			{
				std::vector<Bullet*>& saucerBullets = flyingSaucers[i]->getBullets();
				for (int j = saucerBullets.size() - 1; j >= 0; j--)
				{
					if (ship->isHitByBullet(saucerBullets[j]))
					{
						delete saucerBullets[j];
						saucerBullets.erase(saucerBullets.begin() + j);
						ship->destroy();
						SoundManager::getSound("explode")->play();
						break;
					}
				}
			}
		}

		if (asteroids.size() == 0)
		{
			generateLevel(currentLevel + 1);
		}

		for (int i = particles.size() - 1; i >= 0; i--)
		{
			particles[i]->update(dt);
			if (particles[i]->isDead())
			{
				Bullet* b = particles[i];
				particles.erase(particles.begin() + i);
				delete b;
			}
		}

		if (livesScore >= 4000)
		{
			livesScore -= 4000;
			livesRemaining++;
			updateLivesDisplay();
			SoundManager::getSound("extralife")->play();
		}
	}


	void render() override
	{
		renderer->begin(ShapeType::Line);
		ship->render(renderer);
		for (Asteroid* asteroid : asteroids)
			asteroid->render(renderer);
		for (FlyingSaucer* flyingSaucer : flyingSaucers)
			flyingSaucer->render(renderer);
		for (Bullet* particle : particles)
			particle->render(renderer);
		for (std::vector<vec2>& shape : lifeDisplays)
			renderer->drawPolygon(shape, Color::YELLOW);
		renderer->end();

		batchRenderer->begin();
		scoreLabel->submit(batchRenderer);
		levelLabel->submit(batchRenderer);
		livesLabel->submit(batchRenderer);
		batchRenderer->end();
	}

	void finish() override
	{

	}
};

int main(int argc, char* argv[])
{
	Asteroids game("Asteroids", 1100, 650);
	game.start();
	return 0;
}