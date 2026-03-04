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
#include "Net/UnrealNetwork.h"
#include "C_HealthComponent.h"
#include "C_MyGS.h"
#include "C_MyPS.h"

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
	HealthComponent = CreateDefaultSubobject<UC_HealthComponent>("HealthComponent");
	HealthComponent->SetIsReplicated(true);

	PickedUpNum = 0;
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();
	Client_PrintMessage("111");
	GetWorldTimerManager().SetTimer(PrintMessage, this, &ThisClass::OnPrintMessage, 4.f, false);
	if (PC && PC->IsLocalController())
	{
		MySpawnWidget = CreateWidget<UUserWidget>(PC, MyShowWidgetClass);
	}
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
			PickedUpNum++;
		}
	}
}

void AC_Character::MoveActor_Implementation()
{
	/*if (TargetActor.IsBound())
	{
		TargetActor.Execute(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("no targetactor")));
	}
	Mult_PrintMessage("Mult");*/
	AC_MyGS* GameState = Cast<AC_MyGS>(UGameplayStatics::GetGameState(this));
	FString TeamMessage = "Team ";
	if (IsValid(GameState)) {
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) {
			if (GameState->IsTeamOne(PlayerController))TeamMessage += "One";
			else TeamMessage += "Two";
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TeamMessage);
		}
	}
	AC_MyPS* PS = Cast<AC_MyPS>(GetPlayerState());
	if(PS)GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), PS->GetPlayerScore()));
}

void AC_Character::OverlapWithActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (HasAuthority())
	{
		if (OtherActor->Implements<UC_I>())
		{
			IC_I::Execute_ShowWidget(OtherActor,this);
			PickUpActor = OtherActor;
		}
	}*/
	if (OtherActor->Implements<UC_I>()) {
		if (IsValid(MySpawnWidget))MySpawnWidget->AddToViewport();
	}
}

void AC_Character::EndOverlapWithActor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (HasAuthority())
	{
		if (OtherActor->Implements<UC_I>())
		{
			IC_I::Execute_HideWidget(OtherActor);
			PickUpActor = nullptr;
		}
	}*/
	if (OtherActor->Implements<UC_I>()) {
		if (IsValid(MySpawnWidget))MySpawnWidget->RemoveFromParent();
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
		EnhancedInputComponent->BindAction(MoveActorAction, ETriggerEvent::Triggered, this, &AC_Character::MoveActor_Implementation);
	}
}

void AC_Character::SpawnArmor_Implementation(float ArmorAmount)
{
	Armor = ArmorAmount;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Armor: %f"), Armor));
	Serevr_AddPlayerScore();
}

void AC_Character::ChangeHealth_Implementation(float Change)
{
	HealthComponent->Health = HealthComponent->Health + Change;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Health: %f"), HealthComponent->Health));
}

void AC_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, Armor);
	DOREPLIFETIME_CONDITION(ThisClass, PickedUpNum,COND_Custom);
}

void AC_Character::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);
	DOREPLIFETIME_ACTIVE_OVERRIDE(ThisClass,PickedUpNum, true);
}

void AC_Character::OnRep_PickUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("PickedUpNum: %d"), PickedUpNum));
}

void AC_Character::Client_PrintMessage_Implementation(const FString& Message)
{
	FString MessagePrint = HasAuthority() ? "Sereve:" : "Client:";
	MessagePrint += Message;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, MessagePrint);
	PC = Cast<APlayerController>(GetController());
}

void AC_Character::Mult_PrintMessage_Implementation(const FString& Message)
{
	FString MessagePrint = HasAuthority() ? "Sereve:" : "Client:";
	MessagePrint += Message;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, MessagePrint);
}

void AC_Character::OnPrintMessage()
{
	if (HasAuthority())
	{
		Client_PrintMessage("aaa");
	}
}

void AC_Character::Serevr_AddPlayerScore_Implementation()
{
	AC_MyPS* PS = Cast<AC_MyPS>(GetPlayerState());
	if (PS)
	{
		PS->AddPlayerScore();
	}
}


