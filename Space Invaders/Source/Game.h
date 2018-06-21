#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include <vector>

struct GameFont;
class Player;
class Enemy;
class Bullet;
class Barrier;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

class InvadersGame:
	public ASGE::OGLGame
{
public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();
	void createEnemyArray();
	void createBarrierArray();
	bool CheckForCollision(float objectPosX, float objectPosY, float bulletPosX, float bulletPosY);
	bool CheckForBarrierCollision(float barrierPosX, float barrierPosY, float bulletPosX, float bulletPosY);
	void RespawnEnemies(bool newRound);
	

private:
	void processGameActions(); 
	void input(int key, int action) const;
	int framesPassed = 0;
	int  callback_id = -1;                             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                                 /**< Exit boolean. If true the game loop will exit. */
	bool gameStart = false;
	int baseX = 50;
	int randomNumber;
	int baseY = 50;
	int barrierbaseX = 40;
	int enemyX = baseX;
	int enemyY = baseY;
	int level = 1;
	bool nextLevel;
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;  /**< Sprite Object. The space invader sprite. */
	std::unique_ptr<ASGE::Sprite> sprite1 = nullptr;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Barrier>> barriers;
	std::unique_ptr<Player> player_one = nullptr;

	
	
};

