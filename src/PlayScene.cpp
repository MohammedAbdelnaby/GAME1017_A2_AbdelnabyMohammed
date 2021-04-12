#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	m_objectScrolling();
	for (int i = 0; i < 2; i++)
	{
		if (int(m_pPlayer->getTransform()->position.y + m_pPlayer->getHeight() - m_pPlayer->getRigidBody()->velocity.y) >= m_pGround[i]->getTransform()->position.y)
		{
			m_pPlayer->getRigidBody()->velocity.y = 0.0f;
			m_pPlayer->getTransform()->position.y = m_pGround[i]->getTransform()->position.y - m_pPlayer->getHeight();
			m_pPlayer->setisGorunded(true);
			std::cout << "yes";
		}
		else
		{
			m_pPlayer->setisGorunded(false);
		}

	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->move();
		m_pPlayer->setCurrentDirection(glm::vec2(-1.0f, m_pPlayer->getCurrentDirection().y));
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->move();
		m_pPlayer->setCurrentDirection(glm::vec2(1.0f, m_pPlayer->getCurrentDirection().y));
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && m_pPlayer->getisGrounded())
	{
		m_pPlayer->PlayerJump();
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBackground1 = new Background();
	m_pBackground1->getTransform()->position = glm::vec2(400.f, 250.0f);
	addChild(m_pBackground1);

	m_pGround[0] = new Ground();
	m_pGround[0]->getTransform()->position = glm::vec2(400.0f, 555.0f);
	addChild(m_pGround[0]);

	m_pGround[1] = new Ground();
	m_pGround[1]->getTransform()->position = glm::vec2(1200.0f, 555.0f);
	addChild(m_pGround[1]);

	m_pPlayer = new Player();
	m_pPlayer->getTransform()->position = glm::vec2(300.0, 100.0);
	addChild(m_pPlayer);

	m_pObstacle = new Obstacle();
	addChild(m_pObstacle);
}

void PlayScene::m_objectScrolling()
{
	m_pGround[0]->getTransform()->position.x -= 5;
	m_pGround[1]->getTransform()->position.x -= 5;
	if (m_pGround[0]->getTransform()->position.x <= -(m_pGround[0]->getWidth() / 2))
	{
		m_pGround[0]->getTransform()->position.x = 400;
		m_pGround[1]->getTransform()->position.x = 1200;
	}
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
