// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	Mesh->SetupAttachment(RootComponent);
}

void ACannon::Shoot(int& AmmoBB)
{
	if(!bReadyToShoot)
		return;
	
	switch (Type)
	{
	case ECannonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 1,FColor::Red,FString(TEXT("BooM")));
		AmmoBB--;
		GEngine->AddOnScreenDebugMessage(1234, 999999, FColor::Blue, FString::Printf(TEXT("AmmoBB - %i"), AmmoBB));
		break;
	
	case ECannonType::FireType:
		GEngine->AddOnScreenDebugMessage(-1, 1,FColor::Green,FString(TEXT("VzZzZz")));
		break;
	}
		
	bReadyToShoot = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState), 1 / FireRate, false);

}

	void ACannon::Spray(int& AmmoAK)
	{
	if(!bReadyToShoot)
		return;
	
		switch (Type2)
		{
		case ECannonType2::FireProjectile2:
			GEngine->AddOnScreenDebugMessage(-1, 1.5,FColor::Red,FString(TEXT("Ratatatata")));
			AmmoAK--;
			GEngine->AddOnScreenDebugMessage(1235, 999999, FColor::Blue, FString::Printf(TEXT("AmmoAK - %i"), AmmoAK));
			break;
			
	case ECannonType2::FireType2:
		GEngine->AddOnScreenDebugMessage(-1, 1.5,FColor::Green,FString(TEXT("Vziiii")));
	break;
	}
	bReadyToShoot = false;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState),  FireRate2,  false);
	
}
	
void ACannon::ResetShootState()
{
	bReadyToShoot = true;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(12345, -1, FColor::Purple,FString::Printf(TEXT("Recharge - %f"), GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle)));
};