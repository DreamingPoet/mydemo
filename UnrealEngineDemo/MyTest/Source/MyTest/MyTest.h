// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyTest, Log, All);


//ʹ�÷�ʽ�ο���  DEBUG_MSG("loaded the file '%s'.", *projectPath)��
//LOG �������ʾ��Log��
//SCREEN �������ʾ����Ļ��
//MSG �����ɫ��֪ͨ��Ϣ
//DEBUG ����DEBUG ������Ϣ�õ���ɫ��Ϣ
//WARNING �����ɫ������Ϣ
//ERROR �����ɫ������Ϣ


/**
 * Log ��Ϣ֪ͨ  ��ɫ
 */
#define LOG_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_WHITE); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Log, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}

/**
 * Log Debug ��Ϣ ��ɫ
 */
#define LOG_DEBUG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Log, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}


/**
 * Log���� ��ɫ
 */
#define LOG_WARNING(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Warning, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}

/**
 * Log������Ϣ ��ɫ
 */
#define LOG_ERROR(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogMyTest, Error, TEXT("%s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}


/**
 * ֻ��ʾ����Ļ�ϵ�֪ͨ��Ϣ ��ɫ
 */
#define SCREEN_MSG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, Msg); \
}


/**
 * ֻ��ʾ����Ļ�ϵ� Debug ��Ϣ ��ɫ
 */
#define SCREEN_DEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, Msg); \
}


/**
 * ֻ��ʾ����Ļ�ϵ� ���� ��Ϣ ��ɫ
 */
#define SCREEN_WARNING(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg); \
}



/**
 * ֻ��ʾ����Ļ�ϵ� ���� ��Ϣ ��ɫ
 */
#define SCREEN_ERROR(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, Msg); \
}

