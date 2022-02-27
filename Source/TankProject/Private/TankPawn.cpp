// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "TankPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TankProject/TankProject.h"

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	TankBody = CreateDefaultSubobject<USkeletalMeshComponent>("TankBody");
	TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	CannonPosition = CreateDefaultSubobject<UArrowComponent>("CannonPosition");
	CannonPosition->SetupAttachment(TankTurret);
	
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
	ArmComponent->SetupAttachment(RootComponent);
	ArmComponent->SetRelativeRotation(FRotator(-90, 0, 0));
	
	CameraComponent =CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(ArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
}

void ATankPawn::MoveForward(float Scale)
{
	MoveScaleTarget = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RotationScaleTarget = Scale;
}

void ATankPawn::Shoot()
{
	if(Cannon && AmmoBB > 0)
	{
		Cannon->Shoot(AmmoBB);
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(333, 1.5,FColor::Red,FString(TEXT("NO BULLET")));
	}
}



void ATankPawn::Spray()
{
	if(Cannon && AmmoAK > 0)
	{
		Cannon->Spray(AmmoAK);
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(333, 1.5,FColor::Red,FString(TEXT("NO BULLET")));
	}
}



// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());

	if(CannonType)
	{
		auto Transform = CannonPosition->GetComponentTransform();
		Cannon = GetWorld()->SpawnActor<ACannon>(CannonType, Transform);
		Cannon->AttachToComponent(CannonPosition,FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}


// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTank(DeltaTime);
	RotateTank(DeltaTime);
	RotateCannon(DeltaTime);
}

	// Called to bind functionality to input
	void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

	}

void ATankPawn::MoveTank(float DeltaTime)
{
	MoveScaleCurrent = FMath::Lerp(MoveScaleCurrent, MoveScaleTarget,MovementAcceleration);
	const auto Location = GetActorLocation();
	SetActorLocation(Location + GetActorForwardVector() * MoveScaleCurrent * MovementSpeed * DeltaTime, false);
	GEngine->AddOnScreenDebugMessage(-666, -5, FColor::Turquoise, FString::Printf(TEXT("Speed - %f"), MoveScaleCurrent));
	
}

void ATankPawn::RotateTank(float DeltaTime)
{
	RotationScaleCurrent = FMath::Lerp(RotationScaleCurrent, RotationScaleTarget, RotationAcceleration);
	auto Rotation = GetActorRotation();
	Rotation.Yaw += RotationScaleCurrent * RotationSpeed * DeltaTime;
	SetActorRotation(Rotation);
	UE_LOG(LogTankProject, Warning, TEXT("%s"), *Rotation.ToString())
}

void ATankPawn::RotateCannon(float DeltaTime)
{
	if(!TankController)
		return;
	auto OldRotation = TankTurret->GetComponentRotation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TankTurret->GetComponentLocation(),TankController->GetMousePosition());
	OldRotation.Yaw = TurretRotation.Yaw;
	TankTurret->SetWorldRotation(FMath::Lerp(TankTurret->GetComponentRotation(),OldRotation,RotationAcceleration));
	
}




