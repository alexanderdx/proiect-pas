// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalAnimInstance.h"
#include "AnimalAI.h"
#include "HunterAI.h"
#include "PreyAI.h"

void UAnimalAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!Animal)
	{
		Animal = Cast<AAnimalAI>(TryGetPawnOwner());
	}

	if (Animal)
	{
		FVector Velocity = Animal->GetVelocity();
		Velocity.Z = 0;

		Speed = Velocity.Size();

		AHunterAI* Hunter = Cast<AHunterAI>(Animal);
		if (Hunter)
		{
			bChasing = Hunter->IsChasing();
		}

		APreyAI* Prey = Cast<APreyAI>(Animal);
		if (Prey)
		{
			bRunningAway = Prey->IsRunning();
			bPreyDead = Prey->IsDead();
		}
	}
}
