// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_InteractWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class UECPP_API UC_InteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Catch")
	TObjectPtr<AActor> CatchCamera;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

	// 初始化时绑定点击事件
	virtual bool Initialize() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 可选：重载鼠标释放事件
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 可选：重载鼠标移动事件
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:
	// 按钮点击事件的处理函数
	UFUNCTION()
	void OnMyButtonClicked();

	bool IsLeftDown;

	FVector2D InitPosition;

	FRotator InitRotator;
};
