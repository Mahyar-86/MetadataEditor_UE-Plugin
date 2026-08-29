// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#include "MetadataEditor.h"

#include "ContentBrowserMenuContexts.h"
#include "MetadataEditorStyle.h"
#include "MetadataEditorWidget.h"
#include "Dialog/SCustomDialog.h"


DEFINE_LOG_CATEGORY(LogMetadataEditor);

#define LOCTEXT_NAMESPACE "FMetadataEditorModule"


void FMetadataEditorModule::StartupModule()
{
	FMetadataEditorStyle::Initialize();
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMetadataEditorModule::RegisterMenus));
}

void FMetadataEditorModule::ShutdownModule()
{
	FMetadataEditorStyle::Shutdown();
}

void FMetadataEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.AssetActionsSubMenu");

	FToolMenuSection& Section = Menu->FindOrAddSection("AssetContextMetadataEditor");

	Section.AddDynamicEntry("EditMetadata", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
	{
		const UContentBrowserAssetContextMenuContext* Context = InSection.FindContext<UContentBrowserAssetContextMenuContext>();
		// Just work if one asset selected
		if (!Context || Context->SelectedAssets.IsEmpty() || Context->SelectedAssets.Num() > 1)
		{
			return;
		}

		// Get the first index as user can select only one asset
		FAssetData SelectedAsset = Context->SelectedAssets[0];

		InSection.AddMenuEntry(
			"EditMetadata",
			NSLOCTEXT("FMetadataEditorModule", "MetadataEditorLabel", "Edit Metadata"),
			NSLOCTEXT("FMetadataEditorModule", "MetadataEditorTooltip", "Edit metadatas of this asset."),
			FSlateIcon(FMetadataEditorStyle::GetStyleSetName(), "MetadataEditor.Menu"),
			FUIAction(FExecuteAction::CreateStatic(&FMetadataEditorModule::OnEditMetadataClicked, SelectedAsset))
		);
	}));
}

void FMetadataEditorModule::OnEditMetadataClicked(FAssetData SelectedAsset)
{
	UClass* WidgetClass = LoadClass<UMetadataEditorWidget>(nullptr,TEXT("/MetadataEditor/Widgets/EUW_MetadataEditorMainWidget.EUW_MetadataEditorMainWidget_C"));

	if (!WidgetClass)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	UMetadataEditorWidget* WidgetInstance = CreateWidget<UMetadataEditorWidget>(World, WidgetClass);

	if (!WidgetInstance)
	{
		return;
	}
	
	// Call Initialize event of the widget to fill itself with asset data
	WidgetInstance->InitializeWithAsset(SelectedAsset.GetAsset());

	const TSharedPtr<SCustomDialog> CustomDialog = SNew(SCustomDialog)
		.Title(FText::FromString(FString::Printf(TEXT("Edit %s Metadata"), *SelectedAsset.GetAsset()->GetName())))
		.UseScrollBox(true)
		.HAlignContent(HAlign_Fill)
		.VAlignContent(VAlign_Fill)
		.Content()
		[
			WidgetInstance->TakeWidget()
		]
		.Buttons({
			SCustomDialog::FButton(FText::FromString(TEXT("Save"))).SetPrimary(true),
			SCustomDialog::FButton(FText::FromString(TEXT("Cancel")))
	});
	
	FWindowSizeLimits WindowSizeLimits = FWindowSizeLimits();

	WindowSizeLimits.SetMinHeight(200);
	WindowSizeLimits.SetMaxHeight(800);
	WindowSizeLimits.SetMinWidth(500);
	WindowSizeLimits.SetMaxWidth(500);
	
	CustomDialog->SetSizeLimits(WindowSizeLimits);
	
	// Call save event if user clicked on save button
	if (CustomDialog->ShowModal() == 0)
	{
		WidgetInstance->RequestSave();
	}

	WidgetInstance->RemoveFromRoot();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMetadataEditorModule, MetadataEditor)
