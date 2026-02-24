// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Armor.generated.h"

class USphereComponent;

UCLASS()
class UECPP_API AC_Armor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Armor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>SphereMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>SphereCollision;

	UPROPERTY(EditAnywhere)
	float ArmorValue = 100.f;

};
