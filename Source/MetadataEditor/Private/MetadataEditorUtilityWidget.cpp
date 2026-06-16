// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.


#include "MetadataEditorUtilityWidget.h"

#include "MetadataEditorProperty.h"
#include "MetadataEditor.h"


TArray<FMetadataEditorProperty> UMetadataEditorUtilityWidget::GetMetadataPropertiesFromAssets(const TArray<TSoftObjectPtr<UObject>>& Assets)
{
	TArray<FMetadataEditorProperty> MetaDataProperties;

	if (Assets.IsEmpty())
	{
		UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertiesFromAssets] Assets is empty!"));
		return MetaDataProperties;
	}
	
	for (TSoftObjectPtr<UObject> Asset : Assets)
	{
		if (!Asset.IsValid())
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertiesFromAssets] Asset %s is not valid!"), *Asset.ToString());
			continue;
		}
		
		const UObject* LoadedObject= Asset.LoadSynchronous();
		if (LoadedObject == nullptr)
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertiesFromAssets] Faild to load the Object: %s"), *Asset->GetName());
			continue;
		}
		
		TMap<FName, FString> Metadata = *Asset->GetPackage()->GetMetaData().GetMapForObject(LoadedObject);
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
		if (!MetadataProperty.IsValid())
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[ApplyMetadataPropertiesToAssets] MetadataProperty of %s is not valid!"), *MetadataProperty.OwnerObject->GetName());
			continue;
		}
		
		MetadataProperty.OwnerObject->Modify();
		
		const UObject* LoadedObject= MetadataProperty.OwnerObject.LoadSynchronous();
		if (LoadedObject == nullptr)
		{
			UE_LOG(LogMetadataEditor, Error, TEXT("[ApplyMetadataPropertiesToAssets] Faild to load the Object: %s"), *MetadataProperty.OwnerObject->GetName());
			continue;
		}
		
		MetadataProperty.OwnerObject->GetPackage()->GetMetaData().SetObjectValues(LoadedObject, MetadataProperty.Metadata);
	}
	
	UE_LOG(LogMetadataEditor, Display, TEXT("[ApplyMetadataPropertiesToAssets] MetadataProperties applied to the assets."));
}
