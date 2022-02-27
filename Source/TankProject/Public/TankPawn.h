// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

class ACannon;
UCLASS(Blueprintable)
class TANKPROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* TankBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TankTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* ArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Fire parans")
	TSubclassOf<ACannon>CannonType;

	UPROPERTY()
	ACannon* Cannon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementAcceleration = 0.06;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed =90;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationAcceleration = 0.06;
	
    float TurretAcceleration = 0.1;
	

	void MoveForward(float Scale);
	void RotateRight(float Scale);
	
	void Shoot();
	void Spray();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveTank(float DeltaTime);
    void RotateTank(float DeltaTime);
    void RotateCannon(float DeltaTime);
	
	float MoveScaleTarget = 0;
	float MoveScaleCurrent = 0;
	float RotationScaleTarget = 0;
	float RotationScaleCurrent = 0;

	int AmmoBB = 30;
	int AmmoAK = 55;

	UPROPERTY()
	class ATankPlayerController* TankController;

};
