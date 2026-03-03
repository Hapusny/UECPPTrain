// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyPS.h"
#include "Net/UnrealNetwork.h"

int AC_MyPS::GetPlayerScore()
{
	return PlayerScore;
}

void AC_MyPS::AddPlayerScore()
{
	PlayerScore++;
}

void AC_MyPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,PlayerScore);
}
