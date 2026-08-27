// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MetadataEditorUtilityWidget.generated.h"

struct FMetadataEditorProperty;
/**
 *
 */
UCLASS()
class METADATAEDITOR_API UMetadataEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "MetadataEditor")
	static FMetadataEditorProperty GetMetadataPropertyFromAsset(UObject* Asset);
	
	UFUNCTION(BlueprintCallable, Category = "MetadataEditor")
	static void ApplyMetadataPropertyToAsset(const FMetadataEditorProperty& MetadataProperty);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MetadataEditor")
	void InitializeWithAsset(const UObject* Asset);
	
};
