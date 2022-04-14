// Copyright Epic Games, Inc. All Rights Reserved.

#include "FpsPas.h"
#include "Modules/ModuleManager.h"


IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, FpsPas, "FpsPas");

DEFINE_LOG_CATEGORY(LogFpsPas);

#define LOCTEXT_NAMESPACE "FpsPas"

void FFpsPasModule::StartupModule()
{
	UE_LOG(LogFpsPas, Warning, TEXT("FpsPas: Log Started"));
}

void FFpsPasModule::ShutdownModule()
{
	UE_LOG(LogFpsPas, Warning, TEXT("FpsPas: Log Ended"));
}

#undef LOCTEXT_NAMESPACE
