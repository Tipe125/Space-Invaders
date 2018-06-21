#pragma once
#include "Gameobject.h"
#include <string>
#include <Engine/Sprite.h>


class Bullet : public GameObject
{
public:
	Bullet(std::shared_ptr<ASGE::Renderer> temp_renderer);
	~Bullet();

	void Move();
	void EnemyMove();
	bool render();

private:
	std::shared_ptr<ASGE::Renderer> renderer;
	std::unique_ptr<ASGE::Sprite> bulletSprite = nullptr;
};

