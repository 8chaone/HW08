#include "SpawnVolume.h"

// 생성자
ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 🔥 스폰 함수
void ASpawnVolume::SpawnItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			TEXT("Spawn!")
		);
	}
}