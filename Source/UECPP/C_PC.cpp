// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PC.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AC_PC::AC_PC()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	PlayerCamera->SetupAttachment(CameraBoom);

	
}

void AC_PC::C_PCTest()
{
	UE_LOG(LogTemp, Warning, TEXT("CPPTest"));
}
