// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/DesktopPlatformExWindows.h"
#elif PLATFORM_MAC
#include "Mac/DesktopPlatformExMac.h"
#elif PLATFORM_LINUX
#include "Linux/DesktopPlatformExLinux.h"
#else
#include "DesktopPlatformExStub.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogDesktopPlatformEx, Log, All);
