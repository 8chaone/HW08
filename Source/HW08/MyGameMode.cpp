#include "MyGameMode.h"
#include "SpawnVolume.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 30;
	TimeRemaining = 30;
	PlayerHP = 0;

	// HUD 생성
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}

	// SpawnVolume 찾기
	for (TActorIterator<ASpawnVolume> It(GetWorld()); It; ++It)
	{
		SpawnVolume = *It;
		break;
	}
}

void AMyGameMode::StartGame()
{
	CurrentWave = 0;
	CurrentLevel = 1;

	StartWave();
}

void AMyGameMode::StartWave()
{
	CurrentWave++;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 2.f, FColor::Yellow,
			FString::Printf(TEXT("Wave %d 시작!"), CurrentWave)
		);
	}

	if (SpawnVolume)
	{
		for (int i = 0; i < CurrentWave * 3; i++)
		{
			SpawnVolume->SpawnItem();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(
		WaveTimer,
		this,
		&AMyGameMode::EndWave,
		5.f,
		false
	);
}

void AMyGameMode::EndWave()
{
	// ⭐ 체력 체크 (여기서 게임오버 처리)
	if (PlayerHP <= 0)
	{
		GameOver();
		return;
	}

	if (CurrentWave < 3)
	{
		StartWave();
	}
	else
	{
		CurrentLevel++;

		if (CurrentLevel > MaxLevel)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 3.f, FColor::Green,
				TEXT("게임 클리어!")
			);
		}
		else
		{
			CurrentWave = 0;
			StartWave();
		}
	}
}

void AMyGameMode::GameOver()
{
	// 게임 멈춤
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// HUD 제거
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
	}

	// 게임오버 UI 생성
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);

		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
}