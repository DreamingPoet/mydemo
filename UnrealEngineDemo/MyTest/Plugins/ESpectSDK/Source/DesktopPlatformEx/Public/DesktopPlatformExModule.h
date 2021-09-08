// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "IDesktopPlatformEx.h"

class FDesktopPlatformExModule : public IModuleInterface
{
public:
	virtual void StartupModule();
	virtual void ShutdownModule();

	static IDesktopPlatformEx* Get()
	{
		FDesktopPlatformExModule& DesktopPlatformExModule = FModuleManager::Get().LoadModuleChecked<FDesktopPlatformExModule>("DesktopPlatformEx");
		return DesktopPlatformExModule.GetSingleton();
	}

private:
	virtual IDesktopPlatformEx* GetSingleton() const { return DesktopPlatformEx; }

	IDesktopPlatformEx* DesktopPlatformEx;
};
