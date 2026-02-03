// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PC.generated.h"

/**
 * 
 */
UCLASS()
class UECPP_API AC_PC : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void C_PCTest();
};
