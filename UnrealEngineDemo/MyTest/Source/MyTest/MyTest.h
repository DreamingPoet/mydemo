// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyTest, Log, All);


//使用方式参考：  DEBUG_MSG("loaded the file '%s'.", *projectPath)；
//LOG 代表会显示在Log中
//SCREEN 代表会显示在屏幕上
//MSG 代表白色的通知信息
//DEBUG 代表DEBUG 特殊信息用的青色信息
//WARNING 代表黄色警告信息
//ERROR 代表红色错误信息


/**
 * Log 信息通知  白色
 */
#define LOG_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_WHITE); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Log, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}

/**
 * Log Debug 信息 青色
 */
#define LOG_DEBUG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Log, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}


/**
 * Log警告 黄色
 */
#define LOG_WARNING(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Warning, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}

/**
 * Log错误信息 红色
 */
#define LOG_ERROR(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Error, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}


/**
 * 只显示在屏幕上的通知信息 白色
 */
#define SCREEN_MSG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, Msg); \
}


/**
 * 只显示在屏幕上的 Debug 信息 青色
 */
#define SCREEN_DEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, Msg); \
}


/**
 * 只显示在屏幕上的 警告 信息 黄色
 */
#define SCREEN_WARNING(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg); \
}



/**
 * 只显示在屏幕上的 错误 信息 红色
 */
#define SCREEN_ERROR(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, Msg); \
}

