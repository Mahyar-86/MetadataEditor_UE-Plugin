// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "MetadataEditorProperty.generated.h" 

/**
 *
 */
USTRUCT(BlueprintType)
struct METADATAEDITOR_API FMetadataEditorProperty
{
	GENERATED_BODY()
	
	/** Variables **/
	
	UPROPERTY(BlueprintReadWrite, Category = "MetadataEditor")
	TSoftObjectPtr<UObject> OwnerObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "MetadataEditor")
	TMap<FName, FString> Metadata;
	
	/** Utility functions **/
	
	bool IsValid() const
	{
		return !OwnerObject.IsNull();
	}
	
	/** Constructors **/
	
	FMetadataEditorProperty(const TSoftObjectPtr<UObject> OwnerObject, const TMap<FName, FString>& Metadata):
		OwnerObject(OwnerObject), Metadata(Metadata){}
	
	FMetadataEditorProperty() = default; 
};
