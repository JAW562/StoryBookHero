// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeSBH.h"

AGameModeSBH::AGameModeSBH() 
{

}

void AGameModeSBH::SwitchGameState(EGameState NewState)
{
	CurrentGameState = NewState;

	switch (CurrentGameState)
	{
	case EGameState::Overworld:

		break;

	case EGameState::Dialogue:

		break;

	case EGameState::Battle:

		break;

	case EGameState::GameOver:

		break;

	default:
		break;
	}
}