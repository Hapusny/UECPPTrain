// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PC.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AC_PC::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputMapping)
		{
			InputSystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AC_PC::C_PCTest()
{
	UE_LOG(LogTemp, Warning, TEXT("CPPTest"));
}
