#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"
#include "TextureManager.h"

class Obstacle final : public DisplayObject
{
public:
	Obstacle();
	~Obstacle();

	// Life Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;

private:

};
#endif // !__OBSTACLE__