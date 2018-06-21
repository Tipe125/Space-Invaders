#include "Actions.h"

/**< Queued Game Action. The next action to be processed as determined by user input. */
std::atomic<GameAction> game_action = GameAction::MENU;
std::atomic<PlayerAction> player_action = PlayerAction::NONE;
std::atomic<EnemyAction> enemy_action = EnemyAction::LEFT;