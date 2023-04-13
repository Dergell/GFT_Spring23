// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTSaveGame.h"

float UGFTSaveGame::GetHighscore() const
{
	return Highscore;
}

void UGFTSaveGame::SetHighscore(float InHighscore)
{
	this->Highscore = InHighscore;
}