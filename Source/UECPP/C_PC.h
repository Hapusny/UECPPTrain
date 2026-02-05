// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PC.generated.h"


class UInputMappingContext;
/**
 * 
 */
UCLASS()

class UECPP_API AC_PC : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;
	
protected:

	UFUNCTION(BlueprintCallable)
	void C_PCTest();

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;
};
