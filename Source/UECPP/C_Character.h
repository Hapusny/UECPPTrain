// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_IPC.h"
#include "GameFramework/Character.h"
#include "C_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class USphereComponent;
class UC_HealthComponent;
struct FInputActionValue;

DECLARE_DELEGATE(FMoveActor)

UCLASS()
class UECPP_API AC_Character : public ACharacter,public IC_IPC
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	// Sets default values
	AC_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump();

	void StopJump();

	void PickUp();

	void MoveActor();

	UFUNCTION()
	void OverlapWithActor(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlapWithActor(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent>CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>ShowWidget;

	UPROPERTY(VisibleAnywhere, Category = "HealthComponent")
	TObjectPtr<UC_HealthComponent>HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SpawnArmor_Implementation(float ArmorAmount)override;

	virtual void ChangeHealth_Implementation(float Change)override;

	FMoveActor TargetActor;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent>CameraBoom;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveActorAction;

	

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent>PlayerCamera;

	TObjectPtr<AActor>PickUpActor;

	TObjectPtr<AActor>MySpawnActor;

	UPROPERTY()
	TObjectPtr<UUserWidget>MySpawnWidget;

	UPROPERTY(Replicated)
	float Armor;

	UPROPERTY(ReplicatedUsing = OnRep_PickUp)
	int PickedUpNum;

	UFUNCTION()
	void OnRep_PickUp();

	void Client_PrintMessage_Implementation(const FString& Message);

	UFUNCTION(Client,Reliable)
	void Client_PrintMessage(const FString& Message);

	FTimerHandle PrintMessage;

	void OnPrintMessage();

	APlayerController* PC;
};
