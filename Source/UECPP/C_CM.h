// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_CM.generated.h"

/**
 * 
 */
UCLASS()
class UECPP_API AC_CM : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay()override;

public:
	TObjectPtr<AActor> GetCatchCamera();


	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor>CatchCameraClass;

};
