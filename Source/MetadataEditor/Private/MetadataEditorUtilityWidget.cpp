// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.


#include "MetadataEditorUtilityWidget.h"

#include "MetadataEditorProperty.h"
#include "MetadataEditor.h"


FMetadataEditorProperty UMetadataEditorUtilityWidget::GetMetadataPropertyFromAsset(UObject* Asset)
{
	if (Asset == nullptr)
	{
		UE_LOG(LogMetadataEditor, Error, TEXT("[GetMetadataPropertyFromAsset] Asset is null!"));
		return FMetadataEditorProperty();
	}
		
	TMap<FName, FString> Metadata;
	if (Asset->GetPackage()->GetMetaData().GetMapForObject(Asset) != nullptr)
	{
		Metadata = *Asset->GetPackage()->GetMetaData().GetMapForObject(Asset);
	}

	return FMetadataEditorProperty(Asset, Metadata);
}

void UMetadataEditorUtilityWidget::ApplyMetadataPropertyToAsset(const FMetadataEditorProperty& MetadataProperty)
{
	if (MetadataProperty.OwnerObject == nullptr)
	{
		UE_LOG(LogMetadataEditor, Error, TEXT("[ApplyMetadataPropertyToAsset] OwnerObject is null!"));
		return;
	}

	MetadataProperty.OwnerObject->Modify();
	MetadataProperty.OwnerObject->GetPackage()->GetMetaData().SetObjectValues(MetadataProperty.OwnerObject, MetadataProperty.Metadata);
	
	UE_LOG(LogMetadataEditor, Display, TEXT("[ApplyMetadataPropertyToAsset] MetadataProperty applied to the asset."));
}
