#include "Enemy.h"
#include "Engine/Renderer.h"


Enemy::Enemy(std::shared_ptr<ASGE::Renderer> temp_renderer)
{
	renderer = temp_renderer;
	enemySprite = renderer->createSprite();
	enemySprite->loadTexture("..\\..\\Resources\\Textures\\crabmeat.png");
	enemySprite->size[0] = 40;
	enemySprite->size[1] = 40;
	moveSpeed = 5;
	timeSteps = 0;
	SetIsAlive(true);
	enemyBullets.reserve(1);

	createBulletArray();
	
}

Enemy::~Enemy()
{
	for (int i = 0; i < 1; i++)
	{
		enemyBullets[i] = nullptr;

	}
}

void Enemy::Attack()
{
	for (int i = 0; i < 1; i++)
	{

		if (!enemyBullets[i]->GetIsAlive())
		{
			int newPosX = GetPosX() + 20;
			int newPosY = GetPosY();
			enemyBullets[i]->SetPosX(newPosX);
			enemyBullets[i]->SetPosY(newPosY);
			enemyBullets[i]->SetIsAlive(true);
			break;
		}
	}
}

void Enemy::Move(EnemyAction enemy_action)
{
	//DO all checks for state here and change accordingly, then 
	if (timeSteps <= 60)
	{
		if (enemy_action == EnemyAction::LEFT)
		{
			int newEnemyPosX = GetPosX();
			SetPosX(newEnemyPosX -= moveSpeed);



		}
		if (enemy_action == EnemyAction::RIGHT)
		{
			int newEnemyPosX = GetPosX();
			SetPosX(newEnemyPosX += moveSpeed);


		}
		timeSteps = 0;
	}
	else
	{
		timeSteps++;
	}


	


}

void Enemy::render()
{
	enemySprite->position[0] = GetPosX();
	enemySprite->position[1] = GetPosY();
	enemySprite->render(renderer);
}

int Enemy::GetStartPosX()
{
	return startPosX;
}

int Enemy::GetStartPosY()
{
	return startPosY;
}

void Enemy::SetStartPosX(int newStartPosX)
{
	startPosX = newStartPosX;
}

void Enemy::SetStartPosY(int newStartPosY)
{
	startPosY = newStartPosY;
}

void Enemy::createBulletArray()
{
	for (int i = 0; i < 1; i++)
	{
		enemyBullets.push_back(std::make_unique<Bullet>(renderer));
	}
}

float Enemy::GetMoveSpeed()
{
	return moveSpeed;
}

void Enemy::SetMoveSpeed(float newMoveSpeed)
{
	moveSpeed = newMoveSpeed;
}


