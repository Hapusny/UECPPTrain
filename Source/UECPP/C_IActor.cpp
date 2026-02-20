// Fill out your copyright notice in the Description page of Project Settings.


#include "C_IActor.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "C_Character.h"



// Sets default values
AC_IActor::AC_IActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// 如果你想让Actor移动同步，还需要
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AC_IActor::BeginPlay()
{
	Super::BeginPlay();
	AC_Character* MYC;
	if (GetNetConnection())
	{
		MYC = Cast<AC_Character>(Cast<APlayerController>(GetNetConnection()->PlayerController)->GetPawn());
	}
	else
	{
		MYC = Cast<AC_Character>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	}
	if (MYC)
	{
		MYC->TargetActor.BindUObject(this, &AC_IActor::MoveActorToPlayer);
	}
}

void AC_IActor::MoveActorToPlayer()
{
	APlayerController* PC;
	if (GetNetConnection())
	{
		PC = Cast<APlayerController>(GetNetConnection()->PlayerController);
	}
	else
	{
		PC = UGameplayStatics::GetPlayerController(this, 0);
	}
	if (PC)
	{
		FVector NewPlace = PC->GetPawn()->GetActorLocation();

		const FRotator Rotation = PC->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		NewPlace = NewPlace + ForwardDirection * 500;
		SetActorLocation(NewPlace);
	}
}

// Called every frame
void AC_IActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_IActor::ShowWidget_Implementation()
{
	APlayerController* PC;
	if (GetNetConnection())
	{
		PC = Cast<APlayerController>(GetNetConnection()->PlayerController);
	}
	else
	{
		PC = UGameplayStatics::GetPlayerController(this, 0);
	}
	if (PC)
	{
		if (ShowWidget)
		{
			SpawnedWidget = CreateWidget<UUserWidget>(PC, ShowWidget);
			if (SpawnedWidget)
			{
				SpawnedWidget->AddToViewport();
			}
		}
	}
}

void AC_IActor::HideWidget_Implementation()
{
	if (SpawnedWidget)
	{
		SpawnedWidget->RemoveFromParent();
	}
}

void AC_IActor::PickUp_Implementation()
{
	Destroy();
}

