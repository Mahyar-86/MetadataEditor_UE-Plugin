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
	static TArray<FMetadataEditorProperty> GetMetadataPropertiesFromAssets(const TArray<UObject*> Assets);
	
	UFUNCTION(BlueprintCallable, Category = "MetadataEditor")
	static void ApplyMetadataPropertiesToAssets(const TArray<FMetadataEditorProperty>& MetaDataProperties);

private:

};
