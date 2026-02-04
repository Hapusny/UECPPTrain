// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PC.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()

class UECPP_API AC_PC : public APlayerController
{
	GENERATED_BODY()

public:
	AC_PC();
	
protected:

	UFUNCTION(BlueprintCallable)
	void C_PCTest();

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent>CameraBoom;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent>PlayerCamera;

};
