#include "Obstacle.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/PineapplePiller.png", "Pineapple");
	auto size = TextureManager::Instance()->getTextureSize("Pineapple");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.f, 300.0f);
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	TextureManager::Instance()->draw("Pineapple", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
