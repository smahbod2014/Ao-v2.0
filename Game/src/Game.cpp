#include <iostream>
#include <Ao/Ao.h>
#include <Ao/Math/AoMath.h>
#include <Ao/Managers/AoManagers.h>
#include <Ao/Graphics/BatchRenderer2D.h>
#include <Ao/Graphics/Camera.h>
#include <Ao/Graphics/Sprite.h>
#include <Ao/Graphics/Group.h>

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
		ao::SoundManager::loadMusic("temple", "Resources/Sounds/scherzo.mp3", 1.0f);
		ao::SoundManager::getMusic("temple")->play();
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

		//ao::FontManager::load("magnetob2", "Resources/Fonts/MAGNETOB.TTF", 35);
	}

	bool interpolating = false;
	float accum = 0;
	ao::vec2 startPos = ao::vec2(-1.0f, -1.0f);
	ao::vec2 currentPos = startPos;
	ao::vec2 endPos = ao::vec2(0.5f, 0.5f);

	void input(float dt) override
	{
		if (ao::Input::isKeyJustPressed(ao::KeyCode::KEY_SPACE))
		{
			interpolating = true;
			accum = 0;
			currentPos = startPos;
		}

		using namespace ao;
		if (Input::isKeyJustPressed(AO_KEY_A))
		{
			std::cout << "Position: " << m_Player->getPosition().x << ", " << m_Player->getPosition().y << std::endl;
		}

		float speed = 100;
		if (ao::Input::isKeyDown(AO_KEY_LEFT))
		{
			m_Player->translate(-speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_RIGHT))
		{
			m_Player->translate(speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_UP))
		{
			m_Player->translate(0, speed * dt);
		}

		if (ao::Input::isKeyDown(AO_KEY_DOWN))
		{
			m_Player->translate(0, -speed * dt);
		}

		if (ao::Input::isKeyDown(AO_KEY_A))
		{
			m_Camera->translate(-speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_D))
		{
			m_Camera->translate(speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_W))
		{
			m_Camera->translate(0, speed * dt);
		}

		if (ao::Input::isKeyDown(AO_KEY_S))
		{
			m_Camera->translate(0, -speed * dt);
		}

		static float zoom = 1;
		if (ao::Input::isKeyJustPressed(AO_KEY_P))
		{
			m_Camera->setZoom(zoom -= 0.1f);
		}

		if (ao::Input::isKeyJustPressed(AO_KEY_O))
		{
			m_Camera->setZoom(zoom += 0.1f);
		}

		if (ao::Input::isKeyDown(AO_KEY_R))
		{
			m_Group->rotate(90 * dt);
		}

		if (ao::Input::isKeyDown(AO_KEY_T))
		{
			m_Group->rotate(-90 * dt);
		}

		if (ao::Input::isKeyJustPressed(AO_KEY_Y))
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
		m_BatchRenderer->drawString("AVAW", ao::vec3(300, 300, 0), *ao::FontManager::get("magnetob"), 0xffffffff);
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