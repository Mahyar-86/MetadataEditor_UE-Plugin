// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#include "MetadataEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FMetadataEditorStyle::StyleInstance = nullptr;

FName FMetadataEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MetadataEditorStyle"));
	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FMetadataEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	
	Style->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("MetadataEditor"))->GetBaseDir() / TEXT("Resources"));
	
	Style->Set("MetadataEditor.Menu", new FSlateImageBrush(Style->RootToContentDir(TEXT("MetadataEditorIcon_Menu"), TEXT(".png")), FVector2D(40.f, 40.f)));
	
	return Style;
}

void FMetadataEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FMetadataEditorStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}
}
