// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalAI.h"

#include "AnimalController.h"
#include "FpsPasCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

AAnimalAI::AAnimalAI()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Comp"));
}

void AAnimalAI::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_Visibility, 
		ECollisionResponse::ECR_Block);
	// Ignore the camera for Mesh and Capsule
	GetMesh()->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_Camera, 
		ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_Camera,
		ECollisionResponse::ECR_Ignore
	);

	// Get the AI Controller
	AnimalController = Cast<AAnimalController>(GetController());
	if (AnimalController)
	{
		const FVector WorldPatrolPoint = GetActorTransform().TransformPosition(PatrolPoint);
		const FVector WorldPatrolPoint2 = GetActorTransform().TransformPosition(PatrolPoint2);
		
		AnimalController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint"),
			WorldPatrolPoint);

		AnimalController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint2"),
			WorldPatrolPoint2);

		AnimalController->RunBehaviorTree(BehaviorTree);
	}
}


void AAnimalAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
