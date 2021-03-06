// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterAI.h"
#include "AnimalController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AHunterAI::AHunterAI()
{
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ThisClass::OnPawnSeen);

	// Initialize the noise emitter component
	NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
}


void AHunterAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PawnMakeNoise(1, GetActorLocation(), true, this);

	FindPlayerTargetTimer += DeltaSeconds;
	if (FindPlayerTargetTimer >= ChasingTimer)
	{
		if (AnimalController)
		{
			if (AnimalController->GetBlackboardComponent())
			{
				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetPlayer"),
					nullptr);

				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetPrey"),
					nullptr);

				bChasing = false;
				GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			}
		}
	}
}

void AHunterAI::BeginPlay()
{
	Super::BeginPlay();

	// Get the AI Controller
	AnimalController = Cast<AAnimalController>(GetController());
	if (AnimalController)
	{
		AnimalController->GetBlackboardComponent()->SetValueAsBool(
			TEXT("CanAttack"),
			true);
	}
}

void AHunterAI::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn || !IsInterestedInPawn(SeenPawn))
		return;
	
	if (AnimalController)
	{
		if (AnimalController->GetBlackboardComponent())
		{
			AnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), SeenPawn);

			bChasing = true;
			GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
			FindPlayerTargetTimer = 0.0f;
		}
	}
}

void AHunterAI::ResetCanAttack()
{
	bCanAttack = true;
	if (AnimalController)
	{
		AnimalController->GetBlackboardComponent()->SetValueAsBool(
			TEXT("CanAttack"),
			true);
	}
}


void AHunterAI::PlayAttackMontage(FName Section, float PlayRate)
{
	if (bDead)
		return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
	
	bCanAttack = false;
	GetWorldTimerManager().SetTimer(
		AttackWaitTimer,
		this,
		&ThisClass::ResetCanAttack,
		AttackWaitTime);

	if (AnimalController)
	{
		AnimalController->GetBlackboardComponent()->SetValueAsBool(
			TEXT("CanAttack"),
			false);
	}
}