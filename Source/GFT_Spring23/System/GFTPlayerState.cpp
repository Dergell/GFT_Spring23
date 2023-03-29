// Fill out your copyright notice in the Description page of Project Settings.


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