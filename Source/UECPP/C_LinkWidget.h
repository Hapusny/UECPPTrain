// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_LinkWidget.generated.h"

class UEditableTextBox;
class UButton;

/**
 * 
 */
UCLASS()
class UECPP_API UC_LinkWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized()override;
	
private:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableTextBox>InputTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>HostButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>LinkButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld>HostLevel;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void LinkButtonClicked();

};
