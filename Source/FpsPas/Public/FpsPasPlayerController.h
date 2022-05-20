// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FpsPasPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPAS_API AFpsPasPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Fps Pas | Character Interface")
	TSubclassOf<UUserWidget> CharacterInterfaceClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* CharacterInterface;
};
