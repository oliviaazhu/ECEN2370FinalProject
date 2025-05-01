/*
 * GameMode.h
 *
 *  Created on: May 1, 2025
 *      Author: olivi
 */

#ifndef INC_GAMEMODE_H_
#define INC_GAMEMODE_H_

enum GAME_MODE {
	SINGLE_PLAYER_MODE,
	TWO_PLAYER_MODE
};

enum GAME_MODE getGameMode();

void setGameMode(enum GAME_MODE mode);


#endif /* INC_GAMEMODE_H_ */
