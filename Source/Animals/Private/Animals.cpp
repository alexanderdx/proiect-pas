// Copyright Epic Games, Inc. All Rights Reserved.

#include "Animals.h"
#include "Modules/ModuleManager.h"


IMPLEMENT_GAME_MODULE(FAnimalsModule, Animals);

DEFINE_LOG_CATEGORY(LogAnimals);

#define LOCTEXT_NAMESPACE "Animals"

void FAnimalsModule::StartupModule()
{
	UE_LOG(LogAnimals, Warning, TEXT("Animals: Log Started"));
}

void FAnimalsModule::ShutdownModule()
{
	UE_LOG(LogAnimals, Warning, TEXT("Animals: Log Ended"));
}

#undef LOCTEXT_NAMESPACE
