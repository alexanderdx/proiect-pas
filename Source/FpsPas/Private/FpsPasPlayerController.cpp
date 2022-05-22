// Fill out your copyright notice in the Description page of Project Settings.

#include "FpsPasPlayerController.h"
#include "Blueprint/UserWidget.h"


void AFpsPasPlayerController::BeginPlay()
{
	if (CharacterInterfaceClass)
	{
		CharacterInterface = CreateWidget<UUserWidget>(this, CharacterInterfaceClass);
		if (CharacterInterface)
		{
			CharacterInterface->AddToViewport();
			CharacterInterface->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
