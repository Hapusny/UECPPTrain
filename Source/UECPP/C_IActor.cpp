// Fill out your copyright notice in the Description page of Project Settings.


#include "C_IActor.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AC_IActor::AC_IActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_IActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_IActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_IActor::ShowWidget_Implementation()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
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

