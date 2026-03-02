// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "C_MyGS.generated.h"

class APlayerController;
/**
 * 
 */
UCLASS()
class UECPP_API AC_MyGS : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	void JoinTeam(APlayerController* NewPlayer);

	bool IsTeamOne(APlayerController* PlayerController);

private:

	UPROPERTY(Replicated)
	TArray<TObjectPtr<APlayerController>> TeamOne;

	UPROPERTY(Replicated)
	TArray<TObjectPtr<APlayerController>> TeamTwo;
};
