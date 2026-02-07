// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CM.h"
#include "Kismet/GameplayStatics.h"

void AC_CM::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(false);
	}
}
