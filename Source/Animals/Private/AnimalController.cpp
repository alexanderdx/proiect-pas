// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalController.h"

#include "AnimalAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AAnimalController::AAnimalController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(BlackboardComponent);
    
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    check(BehaviorTreeComponent);
}


void AAnimalController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	AAnimalAI* Animal = Cast<AAnimalAI>(InPawn);
	if (Animal)
	{
		if (Animal->GetBehaviorTree())
		{
			BlackboardComponent->InitializeBlackboard(*(Animal->GetBehaviorTree()->BlackboardAsset));
		}
	}
}
