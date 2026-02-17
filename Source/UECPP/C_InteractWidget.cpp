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

    IsLeftDown = false;

	return false;
}

FReply UC_InteractWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    // 检查是否是左键按下
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        // 获取鼠标位置
        FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

        // 在这里处理左键按下逻辑
        UE_LOG(LogTemp, Warning, TEXT("Left mouse button pressed at: %s"), *LocalPosition.ToString());

        IsLeftDown = true;
        InitPosition = LocalPosition;

        if (CatchCamera)
        {
            InitRotator = CatchCamera->GetActorRotation();
        }

        // 返回表示事件已被处理
        return FReply::Handled();
    }

    // 返回未处理，让事件继续传递
    return FReply::Unhandled();
}

FReply UC_InteractWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("Left mouse button released"));
        IsLeftDown = false;
        return FReply::Handled();
    }

    return FReply::Unhandled();
}

FReply UC_InteractWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
    UE_LOG(LogTemp, Warning, TEXT("Mouse moving at: %s"), *LocalPosition.ToString());
    if (IsLeftDown)
    {
        float NewPicth = InitRotator.Pitch - (LocalPosition - InitPosition).Y;
        float NewYaw = InitRotator.Yaw + (LocalPosition - InitPosition).X;
        if (CatchCamera)
        {
            CatchCamera->SetActorRotation(FRotator(NewPicth, NewYaw, InitRotator.Roll));
        }
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

void UC_InteractWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    IsLeftDown = false;
}

void UC_InteractWidget::OnMyButtonClicked()
{
    RemoveFromParent();
    FInputModeGameOnly InputMode;
    GetOwningPlayer()->SetInputMode(InputMode);
    GetOwningPlayer()->bShowMouseCursor = false;
}
