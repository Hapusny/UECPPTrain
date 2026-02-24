// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Armor.h"
#include "Components/SphereComponent.h"
#include "C_IPC.h"

// Sets default values
AC_Armor::AC_Armor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AC_Armor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (HasAuthority())
	{
		AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		if (OtherActor->Implements<UC_IPC>())
		{
			IC_IPC::Execute_SpawnArmor(OtherActor, ArmorValue);
		}
	}
}

