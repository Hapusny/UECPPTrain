// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C_MyGM.generated.h"

/**
 * 
 */
UCLASS()
class UECPP_API AC_MyGM : public AGameMode
{
	GENERATED_BODY()
	
public:
	AC_MyGM();

	virtual void BeginPlay()override;

	virtual void PostLogin(APlayerController* NewPlayer)override;

	virtual void StartMatch()override;

	FTimerHandle MakeMatchStart;
};
