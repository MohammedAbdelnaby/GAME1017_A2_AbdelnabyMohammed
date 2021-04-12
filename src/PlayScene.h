#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "BackRound.h"
#include "Ground.h"
#include "Obstacle.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void m_objectScrolling();
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	Obstacle* m_pObstacle;
	glm::vec2 m_mousePosition;
	Background* m_pBackground1;
	Ground* m_pGround[2];
	Player* m_pPlayer;

};

#endif /* defined (__PLAY_SCENE__) */