// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "D_GameModeBase.generated.h"

class AD_MechaBase;
/**
 * 
 */
UCLASS()
class DRONEGAME_API AD_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AD_GameModeBase();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	void ShowEndGameScreen();

private:
	bool bGameEnded;

	AActor* Player;

	TArray<AActor*> EnemyArray;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> EnemyActor;

	TSubclassOf<UUserWidget> EndGameWidgetClass;

	TObjectPtr<UUserWidget> EndGameWidgetObj;

};
