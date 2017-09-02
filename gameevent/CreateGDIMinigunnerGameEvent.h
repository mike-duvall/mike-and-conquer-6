#pragma once

#include "GameEvent.h"

class CreateGDIMinigunnerGameEvent : public GameEvent {

public:
	CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY);
	virtual GameState * Process();

private:
	int x;
	int y;

};