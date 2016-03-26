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

class Game : public ao::Ao
{
private:
	ao::BatchRenderer2D* m_BatchRenderer;
	ao::ShapeRenderer2D* shapeRenderer;
	ao::Camera* m_Camera;
	ao::Sprite* m_Player, *m_Box;
	ao::Group* m_Group;
	ao::Label* label;
	
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
		//ao::SoundManager::loadMusic("temple", "Resources/Sounds/scherzo.mp3", 1.0f);
		//ao::SoundManager::getMusic("temple")->play();
		m_BatchRenderer = new ao::BatchRenderer2D();
		m_Camera = new ao::Camera(960, 540);
		m_BatchRenderer->setProjectionMatrix(m_Camera->getCombinedMatrix());
		m_Player = new ao::Sprite(ao::vec3(100, 100, 0), ao::vec2(150, 100.0f), ao::Color::colorAlpha(ao::Color::GREEN, 0.5f), ao::TextureManager::get("wtf"));
		label = new ao::Label("ABCI", 100, 100, "arial", ao::Color::PURPLE);
		//label->rotate(90);
		//m_Player->rotate(90);
		m_Group = new ao::Group();
		m_Group->add(m_Player);
		m_Group->add(label);
		m_Group->setOrigin(m_Player->getCenter());

		shapeRenderer = new ao::ShapeRenderer2D();
	}

	void input(float dt) override
	{

		float speed = 100;
		if (ao::Input::isKeyDown(AO_KEY_LEFT))
		{
			m_Group->translate(-speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_RIGHT))
		{
			m_Group->translate(speed * dt, 0);
		}

		if (ao::Input::isKeyDown(AO_KEY_UP))
		{
			m_Group->translate(0, speed * dt);
		}

		if (ao::Input::isKeyDown(AO_KEY_DOWN))
		{
			m_Group->translate(0, -speed * dt);
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
		/*ao::vec2 bounds = label->getBounds();
		std::cout << "Width = " << bounds.x << ", Height = " << bounds.y << std::endl;*/
	}


	void render() override
	{
		m_BatchRenderer->setProjectionMatrix(m_Camera->getCombinedMatrix());
		m_BatchRenderer->begin();
		m_Group->submit(m_BatchRenderer);
		m_BatchRenderer->end();

		shapeRenderer->setProjectionMatrix(m_Camera->getCombinedMatrix());
		shapeRenderer->begin(ao::ShapeType::Filled);
		shapeRenderer->drawCircle(100, 100, 50, ao::Color::BLUE);
		shapeRenderer->drawCircle(200, 250, 100, ao::Color::GREEN);
		shapeRenderer->drawLine(100, 100, 200, 250, ao::Color::YELLOW);
		shapeRenderer->end();
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