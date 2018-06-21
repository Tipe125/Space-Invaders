#include "Player.h"
#include <Engine/Renderer.h>


Player::Player(std::shared_ptr<ASGE::Renderer> temp_renderer)
{
	renderer = temp_renderer;
	playerSprite = renderer->createSprite();
	playerSprite->loadTexture("..\\..\\Resources\\Textures\\Ship.png");
	playerSprite->size[0] = 60;
	playerSprite->size[1] = 60;
	
	SetPosX(250);
	SetPosY(500);
	SetLives(3);

	bullets.reserve(1);

	createBulletArray();
	
}

Player::~Player()
{
	for (int i = 0; i < 1; i++)
	{
		bullets[i] = nullptr;
		
	}
}

void Player::Attack()
{
	for (int i = 0; i < 1; i++)
	{
		
		if (!bullets[i]->GetIsAlive())
		{
			int newPos = GetPosX() + 25;
			bullets[i]->SetPosX(newPos);
			bullets[i]->SetPosY(490);
			bullets[i]->SetIsAlive(true);
			break;
		}
	}
}

void Player::MoveLeft()
{
	moveSpeed = 10.0f;
	float position = GetPosX();
	if (position >= 0)
	{
		position -= moveSpeed;
		SetPosX(position);
	}
}

void Player::MoveRight()
{
	moveSpeed = 10.0f;
	float position = GetPosX();
	
	if (position <= (640 - 60))
	{
		position += moveSpeed;
		SetPosX(position);
	}
}

bool Player::render()
{
	
	playerSprite->position[0] = GetPosX();

	playerSprite->position[1] = GetPosY();
	playerSprite->render(renderer);

	
	return true;
}

void Player::createBulletArray()
{
	for (int i = 0; i < 1; i++)
	{
		bullets.push_back(std::make_unique<Bullet>(renderer));
	}
}

int Player::GetScore()
{
	return score;
}

void Player::SetScore(float newScore)
{
	score = newScore;
}

int Player::GetLives()
{
	return lives;
}

void Player::SetLives(int newLives)
{
	lives = newLives;
}

