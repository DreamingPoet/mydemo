// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesktopPlatformExModule.h"
#include "DesktopPlatformExPrivate.h"

IMPLEMENT_MODULE( FDesktopPlatformExModule, DesktopPlatformEx );
DEFINE_LOG_CATEGORY(LogDesktopPlatformEx);

void FDesktopPlatformExModule::StartupModule()
{
	DesktopPlatformEx = new FDesktopPlatformEx();
}

void FDesktopPlatformExModule::ShutdownModule()
{
	if (DesktopPlatformEx != NULL)
	{
		delete DesktopPlatformEx;
		DesktopPlatformEx = NULL;
	}
}
