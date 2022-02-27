// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"
UENUM()
enum class ECannonType:uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	
	FireType = 1 UMETA(DisplayName = "Use trace")
};

UENUM()
enum class ECannonType2:uint8
{
	FireProjectile2 = 0 UMETA(DisplayName = "Use projectile1"),
	
	FireType2 = 1 UMETA(DisplayName = "Use trace1")
};

UCLASS()
class TANKPROJECT_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireRate = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireType = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate2 = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireType2 = 2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType2 Type2 = ECannonType2::FireProjectile2;
	
	
	void Shoot(int& AmmoBB);
	
	void Spray(int& AmmoAK);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ResetShootState();

	FTimerHandle TimerHandle;
	bool bReadyToShoot = true;
	

};
