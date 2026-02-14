// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "C_I.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AC_Character::AC_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	PlayerCamera->SetupAttachment(CameraBoom);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(50.0f);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AC_Character::OverlapWithActor);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AC_Character::EndOverlapWithActor);
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Character::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AC_Character::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (GetController() != nullptr)
	{
		AddControllerPitchInput(LookVector.Y);
		AddControllerYawInput(LookVector.X);
	}
}

void AC_Character::Jump()
{
	if (GetController() != nullptr)
	{
		Super::Jump();
	}
}

void AC_Character::StopJump()
{
	if (GetController() != nullptr)
	{
		Super::StopJumping();
	}
}

void AC_Character::PickUp()
{
	if (PickUpActor)
	{
		if (PickUpActor->Implements<UC_I>())
		{
			MySpawnActor = GetWorld()->SpawnActor<AActor>(PickUpActor->GetClass(), SpawnLocation, FRotator::ZeroRotator);
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				MySpawnWidget = CreateWidget<UUserWidget>(PC, ShowWidget);
				MySpawnWidget->AddToViewport();
				FInputModeUIOnly InputMode;
				PC->SetInputMode(InputMode);
				PC->SetShowMouseCursor(true);
			}
			IC_I::Execute_PickUp(PickUpActor);
			PickUpActor = nullptr;
		}
	}
}

void AC_Character::OverlapWithActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UC_I>())
	{
		IC_I::Execute_ShowWidget(OtherActor);
		PickUpActor = OtherActor;
	}
}

void AC_Character::EndOverlapWithActor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UC_I>())
	{
		IC_I::Execute_HideWidget(OtherActor);
		PickUpActor = nullptr;
	}
}

// Called every frame
void AC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_Character::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AC_Character::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AC_Character::StopJump);
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this, &AC_Character::PickUp);
	}
}

