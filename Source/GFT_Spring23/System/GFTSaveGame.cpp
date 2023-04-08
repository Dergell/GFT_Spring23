// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTSaveGame.h"

float UGFTSaveGame::GetHighscore() const
{
	return Highscore;
}

void UGFTSaveGame::SetHighscore(float InHighscore)
{
	this->Highscore = InHighscore;
}