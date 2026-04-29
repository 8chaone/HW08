#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.generated.h"

class ASpawnVolume;

UCLASS()
class HW08_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	// SpawnVolume
	UPROPERTY()
	ASpawnVolume* SpawnVolume;

	// 웨이브
	int32 CurrentWave = 0;
	int32 CurrentLevel = 1;
	int32 MaxLevel = 3;

	FTimerHandle WaveTimer;

	// UI 값
	UPROPERTY(BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(BlueprintReadWrite)
	float TimeRemaining = 60.f;

	UPROPERTY(BlueprintReadWrite)
	float PlayerHP = 100.f;

	// HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* HUDWidget;

	// ⭐ 게임오버 UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidget;

	// 시작
	UFUNCTION(BlueprintCallable)
	void StartGame();

	// ⭐ 게임오버
	UFUNCTION(BlueprintCallable)
	void GameOver();

	// 함수
	void StartWave();
	void EndWave();
};
