#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "src/Ao.h"
#include "src/Math/AoMath.h"
#include "src/Managers/AoManagers.h"
#include "src/Graphics/BatchRenderer2D.h"
#include "src/Graphics/Camera.h"
#include "src/Graphics/Sprite.h"
#include "src/Graphics/Group.h"

class Game : public ao::Ao
{
private:
	ao::BatchRenderer2D* m_BatchRenderer;
	ao::Camera* m_Camera;
	ao::Sprite* m_Player, *m_Box;
	ao::Group* m_Group;
	
public:
	Game(const char* title, int width, int height) : Ao(title, width, height)
	{

	}

	virtual ~Game()
	{

	}

	void init() override
	{
		std::cout << "We're back!" << std::endl;
		ao::TextureManager::load("wtf", "Resources/Textures/wtf_face.png");
		/*SoundManager::loadMusic("temple", "Resources/Sounds/forest_temple.ogg", 0.1f);
		SoundManager::getMusic("temple")->play();*/
		m_BatchRenderer = new ao::BatchRenderer2D();
		m_Camera = new ao::Camera(960, 540);
		m_BatchRenderer->setProjectionMatrix(m_Camera->getCombinedMatrix());
		//m_Player = new ao::Sprite(ao::vec3(0, 0, 0), ao::vec2(200, 100), ao::vec4(1, 0, 0, 1));
		m_Player = new ao::Sprite(ao::vec3(200, 200, 0), ao::TextureManager::get("wtf"));
		m_Box = new ao::Sprite(ao::vec3(50, 50, 0), ao::vec2(100, 25), ao::vec4(0, 0, 1, 1));
		m_Group = new ao::Group();
		m_Group->add(m_Player);
		m_Group->add(m_Box);
		m_Group->setOrigin(m_Player->getCenter());
	}

	bool interpolating = false;
	float accum = 0;
	ao::vec2 startPos = ao::vec2(-1.0f, -1.0f);
	ao::vec2 currentPos = startPos;
	ao::vec2 endPos = ao::vec2(0.5f, 0.5f);

	void input(float dt) override
	{
		if (ao::Input::isKeyJustPressed(SDLK_SPACE))
		{
			interpolating = true;
			accum = 0;
			currentPos = startPos;
		}

		using namespace ao;
		if (Input::isKeyJustPressed(SDLK_q))
		{
			std::cout << "Position: " << m_Player->getPosition().x << ", " << m_Player->getPosition().y << std::endl;
		}

		float speed = 100;
		if (ao::Input::isKeyDown(SDLK_LEFT))
		{
			m_Player->translate(-speed * dt, 0);
		}

		if (ao::Input::isKeyDown(SDLK_RIGHT))
		{
			m_Player->translate(speed * dt, 0);
		}

		if (ao::Input::isKeyDown(SDLK_UP))
		{
			m_Player->translate(0, speed * dt);
		}

		if (ao::Input::isKeyDown(SDLK_DOWN))
		{
			m_Player->translate(0, -speed * dt);
		}

		if (ao::Input::isKeyDown(SDLK_a))
		{
			m_Camera->translate(-speed * dt, 0);
		}

		if (ao::Input::isKeyDown(SDLK_d))
		{
			m_Camera->translate(speed * dt, 0);
		}

		if (ao::Input::isKeyDown(SDLK_w))
		{
			m_Camera->translate(0, speed * dt);
		}

		if (ao::Input::isKeyDown(SDLK_s))
		{
			m_Camera->translate(0, -speed * dt);
		}

		static float zoom = 1;
		if (ao::Input::isKeyJustPressed(SDLK_p))
		{
			m_Camera->setZoom(zoom -= 0.1f);
		}

		if (ao::Input::isKeyJustPressed(SDLK_o))
		{
			m_Camera->setZoom(zoom += 0.1f);
		}

		if (ao::Input::isKeyDown(SDLK_r))
		{
			m_Group->rotate(90 * dt);
		}

		if (ao::Input::isKeyDown(SDLK_t))
		{
			m_Group->rotate(-90 * dt);
		}

		if (ao::Input::isKeyJustPressed(SDLK_y))
		{
			m_Player->setPosition(ao::vec2(0, 0));
		}
	}

	void update(float dt) override
	{
		if (interpolating && accum < 1)
		{
			accum += dt / 2;
			currentPos = ao::vec2::lerp(startPos, endPos, accum);
		}

		//m_Player->rotate(ao::vec3(0, 0, 1), 90 * dt);
	}


	void render() override
	{
		m_BatchRenderer->setProjectionMatrix(m_Camera->getCombinedMatrix());
		m_BatchRenderer->begin();
		m_Player->submit(m_BatchRenderer);
		//m_Group->submit(m_BatchRenderer);
		m_BatchRenderer->end();
		/*glBegin(GL_QUADS);
		glColor3f(0, 0, 1);
		glVertex2f(currentPos.x, currentPos.y);
		glColor3f(1, 0, 1);
		glVertex2f(currentPos.x + .5f, currentPos.y);
		glColor3f(0, 1, 0);
		glVertex2f(currentPos.x + .5f, currentPos.y + .5f);
		glColor3f(1, 0, 0);
		glVertex2f(currentPos.x, currentPos.y + .5f);
		glEnd();*/
	}

	void finish() override
	{

	}
};

int main(int argc, char* argv[])
{
	Game game("My Awesome Game", 960, 540);
	game.start();
	return 0;
}