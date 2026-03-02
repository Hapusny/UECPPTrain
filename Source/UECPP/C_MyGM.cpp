// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyGM.h"
#include "C_MyGS.h"

AC_MyGM::AC_MyGM()
{
	bDelayedStart = true;
}

void AC_MyGM::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MakeMatchStart, this, &AC_MyGM::StartMatch, 4.f);
}

void AC_MyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	AC_MyGS* MyGS = GetGameState<AC_MyGS>();
	if (IsValid(MyGS)) {
		MyGS->JoinTeam(NewPlayer);
	}
}

void AC_MyGM::StartMatch()
{
	Super::StartMatch();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("StartMatch")));
}
