// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyGS.h"
#include "Net/UnrealNetwork.h"

void AC_MyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, TeamOne);
	DOREPLIFETIME(ThisClass, TeamTwo);
}

void AC_MyGS::JoinTeam(APlayerController* NewPlayer)
{
	if (TeamOne.Num() > TeamTwo.Num()) {
		TeamTwo.Add(NewPlayer);
	}
	else {
		TeamOne.Add(NewPlayer);
	}
}

bool AC_MyGS::IsTeamOne(APlayerController* PlayerController)
{
	return TeamOne.Contains(PlayerController);
}
