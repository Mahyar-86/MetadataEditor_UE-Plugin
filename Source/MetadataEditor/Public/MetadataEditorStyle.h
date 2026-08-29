// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FMetadataEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get() { return *StyleInstance; }
	static FName GetStyleSetName();

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
