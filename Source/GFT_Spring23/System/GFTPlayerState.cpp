// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTPlayerState.h"

void AGFTPlayerState::UpdateScore(int32 Points)
{
	SetScore(GetScore() + Points);
}

int32 AGFTPlayerState::GetLives()
{
	return Lives;
}

void AGFTPlayerState::SetLives(int32 NewLives)
{
	Lives = NewLives;
}