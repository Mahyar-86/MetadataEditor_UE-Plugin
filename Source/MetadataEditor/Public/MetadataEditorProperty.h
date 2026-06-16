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
	UObject* OwnerObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "MetadataEditor")
	TMap<FName, FString> Metadata;
	
	/** Constructors **/
	
	FMetadataEditorProperty(UObject* OwnerObject, const TMap<FName, FString>& Metadata):
		OwnerObject(OwnerObject), Metadata(Metadata){}
	
	FMetadataEditorProperty() = default; 
};
