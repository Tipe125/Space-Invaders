#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Barrier.h"

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>
#include <time.h>

/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{

	this->inputs->unregisterCallback(callback_id);
	
	

}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	//width = WINDOW_WIDTH;
	width = 640;
	//height = WINDOW_HEIGHT;
	height = 600;
	if (!initAPI())
	{
		return false;
	}

	srand(time(0));
	renderer->setWindowTitle("Invaders - Exercise 1");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	//Create Player Object
	player_one = std::make_unique<Player>(renderer);
	

	//player_one->loadAvatar(renderer);
	//player_one->render();
	
	//Create Array of enemy objects
	enemies.reserve(55);
	
	createEnemyArray();
	
	//create barriers
	barriers.reserve(4);

	createBarrierArray();
	
	
	

	// load space invader sprite
	sprite = renderer->createSprite();
	sprite->position[0] = 350;
	sprite->position[1] = 350;

	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\crabmeat.png"))
	{
		return false;
	}

	sprite1 = renderer->createSprite();
	sprite1->position[0] = 0;
	sprite1->position[1] = 100;

	if (!sprite1->loadTexture("..\\..\\Resources\\Textures\\Ship.png"))
	{
		return false;
	}

	
	

	return true;
}


/**
*   @brief   The main game loop. 
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly. 
*/
bool InvadersGame::run()
{
	while (!shouldExit())
	{
		
		processGameActions();
		render();
	}

	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}


/**
*   @brief   Renders the scene
*   @details Prepares the renderer subsystem before drawing the 
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void InvadersGame::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}


/**
*   @brief   Renderers the contents for this frame 
*   @details All game objects that need rendering should be done
			 in this function, as it ensures they are completed
			 before the buffers are swapped.
*   @return  void
*/
void InvadersGame::drawFrame()
{
	if (game_action == GameAction::GAMEOVER)
	{
		renderer->renderText("The Crabmeat army has taken earth!\n Press Enter to try again\n Press Space to return to menu", 300, 300, 1.0, ASGE::COLOURS::DARKORANGE);
	}

	if (game_action == GameAction::MENU)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		sprite1->render(renderer);
		sprite->render(renderer);
 		renderer->renderText("Crabmeat Invaders\nPRESS ENTER TO BEGIN", 400, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		//sprite->render(renderer);
	}

	if (game_action == GameAction::PAUSE)
	{
		renderer->renderText("PAUSED\nPress enter to continue\nPress Esc to Exit", 400, 300, 1.0, ASGE::COLOURS::DARKORANGE);
	}
	
	if (game_action == GameAction::GAME)
	{
		player_one->render();
		std::string score = std::to_string(player_one->GetScore());
		std::string lives = std::to_string(player_one->GetLives());
		std::string levelCount = std::to_string(level);
		renderer->renderText("Lives: ", 100, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText(lives.c_str(), 250, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText("Score: ", 400, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText(score.c_str(), 550, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText("Level: ", 1000, 0, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText(levelCount.c_str(), 1150, 0, 1.0, ASGE::COLOURS::DARKORANGE);

		for (int i = 0; i < 4; i++)
		{
			barriers[i]->render();
		}
		

		for (int i = 0; i < 1; i++)
		{
			if (player_one->bullets[i]->GetIsAlive())
			{
				player_one->bullets[i]->render();
			}
		}

		
		
		if (framesPassed == 30)
		{
			for (int row = 0; row < 5; row++)
			{
				for (int col = 0; col < 11; col++)
				{
					if (enemies[11 * row + col]->GetIsAlive())
					{
						if (enemies[11 * row + col]->GetPosX() <= 0)
						{
							//FOR LOOP GOING THROUGH EACH ENEMY AND CHANGING ITS Y POSITION
							for (int row1 = 0; row1 < 5; row1++)
							{
								for (int col1 = 0; col1 < 11; col1++)
								{
									int newEnemyPosY = enemies[11 * row1 + col1]->GetPosY();

									enemies[11 * row1 + col1]->SetPosY(newEnemyPosY += 2);

									if (enemies[11 * row1 + col1]->GetPosY() == 500)
									{
										RespawnEnemies(false);
										int newLives = player_one->GetLives() - 1;

										player_one->SetLives(newLives);
									}
									
								}
							}

							enemy_action = EnemyAction::RIGHT;
						}
					}
					if (enemies[11 * row + col]->GetIsAlive())
					{
						if (enemies[11 * row + col]->GetPosX() >= 600)
						{
							//FOR LOOP GOING THROUGH EACH ENEMY AND CHANGING ITS Y POSITION
							for (int row1 = 0; row1 < 5; row1++)
							{
								for (int col1 = 0; col1 < 11; col1++)
								{
									int newEnemyPosY = enemies[11 * row1 + col1]->GetPosY();
									enemies[11 * row1 + col1]->SetPosY(newEnemyPosY += 2);

									if (enemies[11 * row1 + col1]->GetPosY() == 500)
									{
										RespawnEnemies(false);
										int newLives = player_one->GetLives() - 1;

										player_one->SetLives(newLives);
									}
								}
							}


							enemy_action = EnemyAction::LEFT;
						}
					}
					
					enemies[11 * row + col]->Move(enemy_action);
					framesPassed = 0;
					
				}

			}

		}

		else
		{
			framesPassed++;
			
		}

		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 11; col++)
			{
				if (enemies[11 * row + col]->GetIsAlive())
				{
					enemies[11 * row + col]->render();
				}
			}
		}

		for (int i = 0; i < 55; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				if (enemies[i]->enemyBullets[j]->GetIsAlive())
				{
					enemies[i]->enemyBullets[j]->render();
				}
			}
		}
		

	}
	
	

}

void InvadersGame::createEnemyArray()
{
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 11; col++)
		{


			enemies.push_back(std::make_unique<Enemy>(renderer));
			enemies[11 * row + col]->SetPosX(enemyX);
			enemies[11 * row + col]->SetPosY(enemyY);
			enemyX += 50;
			
		}
		enemyX = baseX;
		enemyY += 50;
	}
}

void InvadersGame::createBarrierArray()
{
	for (int i = 0; i < 4; i++)
	{
		barriers.push_back(std::make_unique<Barrier>(renderer));
		barriers[i]->SetPosX(barrierbaseX);
		barrierbaseX += 150;
	}

}




/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void InvadersGame::input(int key, int action) const
{
	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}

		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_action = GameAction::GAME;
		}

		if (key == ASGE::KEYS::KEY_P)
		{
			if (game_action == GameAction::GAME)
			{
				game_action = GameAction::PAUSE;
			}
		}

		
	}

	if (game_action == GameAction::GAMEOVER)
	{
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::MENU;
		}
	}
	if (game_action == GameAction::GAME)
	{
		if (key == ASGE::KEYS::KEY_A)
		{
			
			player_action = PlayerAction::LEFT;

		}
		if (key == ASGE::KEYS::KEY_D)
		{
			
			player_action = PlayerAction::RIGHT;
		}

		if (key == ASGE::KEYS::KEY_SPACE)
		{
			player_action = PlayerAction::ATTACK;
		}
		
	}
}


/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{

	if (game_action == GameAction::EXIT)
	{
		
		this->exit = true;
	}
	if (game_action == GameAction::GAME)
	{
		nextLevel = true;
		if (player_action == PlayerAction::LEFT)
		{
			player_one->MoveLeft();
		}
		if (player_action == PlayerAction::RIGHT)
		{
			player_one->MoveRight();
		}
		if (player_action == PlayerAction::ATTACK)
		{
			player_one->Attack();
		}

		if (framesPassed == 30)
		{
			randomNumber = rand() % 55;
			if (enemies[randomNumber]->GetIsAlive())
			{
				enemies[randomNumber]->Attack();
			}
		}

		for (int i = 0; i < 1; i++)
		{
			if (player_one->bullets[i]->GetIsAlive())
			{

				player_one->bullets[i]->Move();

				for (int j = 0; j < 55; j++)
				{
					if (enemies[j]->GetIsAlive() && player_one->bullets[i]->GetIsAlive())
					{
						if (CheckForCollision(enemies[j]->GetPosX(),
							enemies[j]->GetPosY(),
							player_one->bullets[i]->GetPosX(),
							player_one->bullets[i]->GetPosY()))
						{
							enemies[j]->SetIsAlive(false);
							player_one->bullets[i]->SetIsAlive(false);

							for (int k = 0; k < 55; k++)
							{
								float newSpeed = enemies[k]->GetMoveSpeed() + 0.5f;
								enemies[k]->SetMoveSpeed(newSpeed);
							}

							int tempScore = player_one->GetScore();
							player_one->SetScore(tempScore += 100);

							for (int k = 0; k < 55; k++)
							{

								if (enemies[k]->GetIsAlive())
								{
									nextLevel = false;
								}

							}

							if (nextLevel)
							{
								level++;
								RespawnEnemies(true);

								int newLives = player_one->GetLives();

								player_one->SetLives(newLives + 1);
							}

						}
					}

				}

				for (int k = 0; k < 4; k++)
				{
					if (player_one->bullets[i]->GetIsAlive())
					{
						if (CheckForBarrierCollision(barriers[k]->GetPosX(),
							barriers[k]->GetPosY(),
							player_one->bullets[i]->GetPosX(),
							player_one->bullets[i]->GetPosY()))
						{
							player_one->bullets[i]->SetIsAlive(false);
						}
					}
				}




			}
		}

		for (int i = 0; i < 55; i++)
		{
			enemies[i]->enemyBullets[0]->EnemyMove();

			for (int j = 0; j < 1; j++)
			{
				if(enemies[i]->enemyBullets[j]->GetIsAlive())
				{ 
					if (CheckForCollision(player_one->GetPosX(), player_one->GetPosY(), enemies[i]->enemyBullets[j]->GetPosX(), enemies[i]->enemyBullets[j]->GetPosY()))
					{
						int newLives = (player_one->GetLives()) - 1;
						player_one->SetLives(newLives);
						enemies[i]->enemyBullets[j]->SetIsAlive(false);
						
					}
				}

				if (player_one->GetLives() <= 0)
				{
					RespawnEnemies(true);
					player_one->SetLives(3);
					player_one->SetScore(0);
					player_one->SetPosX(250);
					player_one->SetPosY(500);
					level = 1;
					player_action = PlayerAction::NONE;
					enemy_action = EnemyAction::LEFT;
					game_action = GameAction::GAMEOVER;
				}
				for (int k = 0; k < 4; k++)
				{

					if (CheckForBarrierCollision(barriers[k]->GetPosX(),
						barriers[k]->GetPosY(),
						enemies[i]->enemyBullets[j]->GetPosX(),
						enemies[i]->enemyBullets[j]->GetPosY()))
					{
						enemies[i]->enemyBullets[j]->SetIsAlive(false);
					}

				}
			}
			
		}


		

		player_action = PlayerAction::NONE;
		
	}
}

bool InvadersGame::CheckForCollision(float objectPosX, float objectPosY, float bulletPosX, float bulletPosY)
{
	if ((objectPosX + 40) >= bulletPosX &&
		objectPosX <= (bulletPosX + 10) &&
		(objectPosY + 40) >= bulletPosY &&
		objectPosY <= (bulletPosY + 25))
	{
		return true;
	}

	return false;

		
}

bool InvadersGame::CheckForBarrierCollision(float barrierPosX, float barrierPosY, float bulletPosX, float bulletPosY)
{
	if ((barrierPosX + 75) >= bulletPosX &&
		barrierPosX <= (bulletPosX + 10) &&
		(barrierPosY + 50) >= bulletPosY &&
		barrierPosY <= (bulletPosY + 25))
	{
		return true;
	}

	return false;
}

void InvadersGame::RespawnEnemies(bool newRound)
{
	enemyX = baseX;
	enemyY = baseY;
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 11; col++)
		{

			if (newRound == true)
			{
				enemies[11 * row + col]->SetIsAlive(true);
			}
			
			enemies[11 * row + col]->SetPosX(enemyX);
			enemies[11 * row + col]->SetPosY(enemyY);
			enemyX += 50;
			enemies[11 * row + col]->SetMoveSpeed(5);

		}
		enemyX = baseX;
		enemyY += 50;
	}
}


