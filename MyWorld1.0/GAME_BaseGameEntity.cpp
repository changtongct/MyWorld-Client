#include "GAME_BaseGameEntity.h"

int GAME_BaseGameEntity::g_NextValidID = 0;

void GAME_BaseGameEntity::SetID() {
	g_ID = g_NextValidID;
	g_NextValidID += 1;
}