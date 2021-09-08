// Fill out your copyright notice in the Description page of Project Settings.


#include "ESpectBPFLibrary.h"
#include "Misc/FileHelper.h"
#include "DesktopPlatformEx/Public/IDesktopPlatformEx.h"
#include "DesktopPlatformEx/Public/DesktopPlatformExModule.h"


FString UESpectBPFLibrary::OpenFileDialog()
{

	void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatformEx* DesktopPlatform = FDesktopPlatformExModule::Get();

	TArray<FString> OutFileNames;

	if (DesktopPlatform)
	{
		EFileDialogFlags::Type SelectionFlag = EFileDialogFlags::None;
		
		DesktopPlatform->OpenFileDialog(ParentWindowPtr,
			TEXT("请选择资源"),
			TEXT("/"),
			TEXT(""),
			TEXT("(Image Files)|*.BMP;*.JPG;*.PNG;*.mp4;*.rar;*.zip;*.txt;*.JPEG;*.ppt;*.xlsx;*.doc;)"), 
			SelectionFlag,
			OutFileNames);
	}
	
	
	if (OutFileNames.Num() > 0)
	{
		return FString(OutFileNames[0]);
	}
	else
	{
		return TEXT("");
	}
	
}

