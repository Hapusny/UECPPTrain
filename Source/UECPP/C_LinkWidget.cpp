// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LinkWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"


void UC_LinkWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = true;

	HostButton->OnClicked.AddDynamic(this, &UC_LinkWidget::HostButtonClicked);
	LinkButton->OnClicked.AddDynamic(this, &UC_LinkWidget::LinkButtonClicked);
}

void UC_LinkWidget::HostButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = false;

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostLevel, true, TEXT("listen"));
}

void UC_LinkWidget::LinkButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = false;
	const FString Address = InputTextBox->GetText().ToString();
	UGameplayStatics::OpenLevel(this, *Address);
}
