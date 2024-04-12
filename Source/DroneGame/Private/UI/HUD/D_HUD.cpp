// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/D_HUD.h"

#include "Blueprint/UserWidget.h"

void AD_HUD::BeginPlay()
{
	Super::BeginPlay();

	check(OverlayWidgetClass);

	OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}
