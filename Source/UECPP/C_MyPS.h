// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "C_MyPS.generated.h"

/**
 * 
 */
UCLASS()
class UECPP_API AC_MyPS : public APlayerState
{
	GENERATED_BODY()
	
public:
	int GetPlayerScore();

	void AddPlayerScore();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

private:
	UPROPERTY(Replicated)
	int PlayerScore;
};
