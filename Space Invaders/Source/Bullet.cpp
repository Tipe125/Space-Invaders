#include "Bullet.h"
#include "Engine/Renderer.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet(std::shared_ptr<ASGE::Renderer> temp_renderer)
{
	renderer = temp_renderer;
	bulletSprite = renderer->createSprite();
	bulletSprite->loadTexture("..\\..\\Resources\\Textures\\Bullet.png");
	bulletSprite->size[0] = 10;
	bulletSprite->size[1] = 25;
	SetPosX(500);
	SetPosY(490);
	SetIsAlive(false);
}

Bullet::~Bullet()
{
	
}

void Bullet::Move()
{
	//SetPosX(_newPosX);
	int newPos = GetPosY() - 5;

	SetPosY(newPos);

	if(newPos <= 0)
	{
		SetIsAlive(false);
	}
}



bool Bullet::render()
{
	bulletSprite->position[0] = GetPosX();
	bulletSprite->position[1] = GetPosY();
	bulletSprite->render(renderer);

	return true;
}

void Bullet::EnemyMove()
{
	int newPos = GetPosY() + 5;

	SetPosY(newPos);

	if (newPos >= 600)
	{
		SetIsAlive(false);
	}
}
