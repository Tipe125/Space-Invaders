#pragma once
#include "Gameobject.h"
#include <vector>
#include <Engine/Sprite.h>


class Barrier : public GameObject
{
public:

	Barrier(std::shared_ptr<ASGE::Renderer> temp_renderer);
	~Barrier();

	bool render();

private:
	std::shared_ptr<ASGE::Renderer> renderer;
	std::unique_ptr<ASGE::Sprite> barrierSprite = nullptr;
};