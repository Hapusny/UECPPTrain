// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_I.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_IActor.generated.h"

UCLASS()
class UECPP_API AC_IActor : public AActor,public IC_I
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_IActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoSomething_Implementation() override;

};
