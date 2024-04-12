// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameRules/D_GameModeBase.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/D_Drone.h"

AD_GameModeBase::AD_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bGameEnded = false;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> EndGameWidget(TEXT("/Game/Blueprints/UI/WBP_EndGameMenu"));
	if (!ensure(EndGameWidget.Class != nullptr)) return;
	EndGameWidgetClass = EndGameWidget.Class;
}

void AD_GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameEnded)
		return;

	for (AActor* Enemy : EnemyArray)
		if (!IsValid(Enemy))
		{
			EnemyArray.Remove(Enemy);
			break;
		}

	if (EnemyArray.IsEmpty() || !IsValid(Player))
		ShowEndGameScreen();
}

void AD_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	EndGameWidgetObj = CreateWidget<UUserWidget>(GetGameInstance(), EndGameWidgetClass);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyActor, EnemyArray);

	Player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
}

void AD_GameModeBase::ShowEndGameScreen()
{
	bGameEnded = true;

	EndGameWidgetObj->AddToViewport();

	FInputModeUIOnly InputModeData;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
	PlayerController->bBlockInput = true;

	Cast<AD_Drone>(Player)->StopMoving();
}
