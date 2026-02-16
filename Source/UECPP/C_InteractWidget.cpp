// Fill out your copyright notice in the Description page of Project Settings.


#include "C_InteractWidget.h"
#include "Components/Button.h"

bool UC_InteractWidget::Initialize()
{
    // 先调用父类的Initialize
    if (!Super::Initialize())
    {
        return false;
    }

    // 安全地绑定点击事件。指针会在Initialize之前被自动设置好（因为BindWidget）
    if (Button)
    {
        Button->OnClicked.AddDynamic(this, &UC_InteractWidget::OnMyButtonClicked);
    }

	return false;
}

void UC_InteractWidget::OnMyButtonClicked()
{
    RemoveFromParent();
    FInputModeGameOnly InputMode;
    GetOwningPlayer()->SetInputMode(InputMode);
    GetOwningPlayer()->bShowMouseCursor = false;
}
