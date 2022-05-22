// Fill out your copyright notice in the Description page of Project Settings.


#include "PreyAI.h"

#include "AnimalController.h"
#include "FpsPasCharacter.h"
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
	if (SeenPawn == nullptr) return;

	// Try to get Player Character
	AFpsPasCharacter* Character = Cast<AFpsPasCharacter>(SeenPawn);
	if (Character)
	{
		if (AnimalController)
		{
			if (AnimalController->GetBlackboardComponent())
			{
				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetPlayer"), 
					Character);
					
				TargetCharacter = Character;
				bRunAway = true;
				GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
				RunAwayTimer = 0.f;
			}
		}
	}
}

void APreyAI::OnPawnHeard(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	if (InstigatorPawn == nullptr) return;

	// Try to get Player Character
	auto Character = Cast<AFpsPasCharacter>(InstigatorPawn);
	if (Character)
	{
		if (AnimalController)
		{
			if (AnimalController->GetBlackboardComponent())
			{
				AnimalController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("TargetPlayer"), 
					Character);
					
				TargetCharacter = Character;
				bRunAway = true;
				GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
				RunAwayTimer = 0.f;
			}
		}
	}
}