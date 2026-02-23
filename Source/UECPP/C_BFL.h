// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_BFL.generated.h"

/**
 * 
 */
UCLASS()
class UECPP_API UC_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "BFL")
	static void PrintActorNetMessage(AActor* Actor);
	
};
