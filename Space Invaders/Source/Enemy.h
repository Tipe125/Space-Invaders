#pragma once
#pragma once
#include "Gameobject.h"
#include <string>
#include "Engine/Sprite.h"
#include "Actions.h"
#include "Bullet.h"
#include <vector>

class Enemy : public GameObject
{
public:
	Enemy(std::shared_ptr<ASGE::Renderer> temp_renderer);
	~Enemy();

	void Attack() override;
	void Move(EnemyAction enemy_action);
	void render();
	int GetStartPosX();
	int GetStartPosY();
	void SetStartPosX(int newStartPosX);
	void SetStartPosY(int newStartPosY);
	std::vector<std::unique_ptr<Bullet>> enemyBullets;
	void createBulletArray();
	float GetMoveSpeed();
	void SetMoveSpeed(float newMoveSpeed);

private:
	bool movingRight;
	float moveSpeed;
	int timeSteps;
	int startPosX;
	int startPosY;
	std::shared_ptr<ASGE::Renderer> renderer;
	std::unique_ptr<ASGE::Sprite> enemySprite = nullptr;



};