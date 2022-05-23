// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalAI.generated.h"


UCLASS(Abstract)
class ANIMALS_API AAnimalAI : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalAI();

protected:
	UFUNCTION(BlueprintNativeEvent)
	bool IsInterestedInPawn(APawn* const& Pawn);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "FpsPas | Behavior Tree")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "FpsPas | Behavior Tree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint;

	UPROPERTY(EditAnywhere, Category = "FpsPas | Behavior Tree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint2;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class AAnimalController* AnimalController;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UPawnSensingComponent* PawnSensingComp;

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};
