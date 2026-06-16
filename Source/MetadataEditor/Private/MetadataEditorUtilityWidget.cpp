// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.


#include "MetadataEditorUtilityWidget.h"

#include "MetadataEditorProperty.h"
#include "MetadataEditor.h"


TArray<FMetadataEditorProperty> UMetadataEditorUtilityWidget::GetMetadataPropertiesFromAssets(const TArray<UObject*> Assets)
{
	TArray<FMetadataEditorProperty> MetaDataProperties;

	if (Assets.IsEmpty())
	{
		UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertiesFromAssets] Assets is empty!"));
		return MetaDataProperties;
	}
	
	for (UObject* Asset : Assets)
	{
		if (Asset == nullptr)
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertiesFromAssets] Asset is null!"));
			continue;
		}
		
		TMap<FName, FString> Metadata;
		if (Asset->GetPackage()->GetMetaData().GetMapForObject(Asset) != nullptr)
		{
			Metadata = *Asset->GetPackage()->GetMetaData().GetMapForObject(Asset);
		}
		
		MetaDataProperties.Add(FMetadataEditorProperty(Asset, Metadata));
	}
	
	return MetaDataProperties;
}

void UMetadataEditorUtilityWidget::ApplyMetadataPropertiesToAssets(const TArray<FMetadataEditorProperty>& MetaDataProperties)
{
	if (MetaDataProperties.IsEmpty())
	{
		UE_LOG(LogMetadataEditor, Error, TEXT("[ApplyMetadataPropertiesToAssets] MetaDataProperties is empty!"));
		return;
	}
	
	for (const FMetadataEditorProperty& MetadataProperty : MetaDataProperties)
	{
		if (MetadataProperty.OwnerObject == nullptr)
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[ApplyMetadataPropertiesToAssets] OwnerObject of is null!"));
			continue;
		}
		
		MetadataProperty.OwnerObject->Modify();
		MetadataProperty.OwnerObject->GetPackage()->GetMetaData().SetObjectValues(MetadataProperty.OwnerObject, MetadataProperty.Metadata);
	}
	
	UE_LOG(LogMetadataEditor, Display, TEXT("[ApplyMetadataPropertiesToAssets] MetadataProperties applied to the assets."));
}
