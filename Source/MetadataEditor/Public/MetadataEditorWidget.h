// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetadataEditorWidget.generated.h"

/**
 * 
 */
UCLASS()
class METADATAEDITOR_API UMetadataEditorWidget : public UUserWidget
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
