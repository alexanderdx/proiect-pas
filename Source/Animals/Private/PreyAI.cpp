// Fill out your copyright notice in the Description page of Project Settings.

#include "PreyAI.h"

#include "AnimalController.h"
#include "HunterAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


APreyAI::APreyAI()
{
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ThisClass::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ThisClass::OnPawnHeard);
}

void APreyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	RunAwayTimer += DeltaSeconds;
	if (RunAwayTimer >= RunningAwayTimer)
	{
		if (AnimalController)
		{
			if (AnimalController->GetBlackboardComponent())
			{
				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetPlayer"), 
					nullptr);

				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetHunter"), 
					nullptr);

				bRunAway = false;
				GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			}
		}
	}
}

void APreyAI::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn || !IsInterestedInPawn(SeenPawn))
		return;

	if (AnimalController)
	{
		if (AnimalController->GetBlackboardComponent())
		{
			AnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), SeenPawn);
					
			TargetCharacter = SeenPawn;
			bRunAway = true;
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			RunAwayTimer = 0.0f;
		}
	}
}

void APreyAI::OnPawnHeard(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	if (!InstigatorPawn || !IsInterestedInPawn(InstigatorPawn))
		return;

	if (AnimalController)
	{
		if (AnimalController->GetBlackboardComponent())
		{
			AnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), InstigatorPawn);
					
			TargetCharacter = InstigatorPawn;
			bRunAway = true;
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			RunAwayTimer = 0.0f;
		}
	}
}
