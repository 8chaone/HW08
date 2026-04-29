#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class HW08_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 🔥 스폰 함수
	void SpawnItem();
};
