#pragma once
#include "Gameobject.h"
#include <string>
#include <Engine/Sprite.h>
#include <vector>

#include "Bullet.h"




class Player : public GameObject
{
public:
	 Player(std::shared_ptr<ASGE::Renderer> temp_renderer);
	 ~Player();

	 void Attack() override;
	 void MoveLeft();
	 void MoveRight();
	 bool render();
	 void createBulletArray();
	 int GetScore();
	 void SetScore(float newScore);
	 int GetLives();
	 void SetLives(int newLives);
	 std::vector<std::unique_ptr<Bullet>> bullets;



private:
	std::shared_ptr<ASGE::Renderer> renderer;
	std::unique_ptr<ASGE::Sprite> playerSprite = nullptr;
	int lives;
	int score;
	float moveSpeed;
	
	

};

