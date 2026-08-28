// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#include "MetadataEditor.h"

#include "ContentBrowserMenuContexts.h"
#include "MetadataEditorWidget.h"


class UContentBrowserAssetContextMenuContext;
DEFINE_LOG_CATEGORY(LogMetadataEditor);

#define LOCTEXT_NAMESPACE "FMetadataEditorModule"

void FMetadataEditorModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMetadataEditorModule::RegisterMenus));
}

void FMetadataEditorModule::ShutdownModule()
{

}

void FMetadataEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.AssetActionsSubMenu");

	FToolMenuSection& Section = Menu->FindOrAddSection("AssetContextMetadataEditor");

	Section.AddDynamicEntry("EditMetadata", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
	{
		const UContentBrowserAssetContextMenuContext* Context = InSection.FindContext<UContentBrowserAssetContextMenuContext>();
		if (!Context || Context->SelectedAssets.IsEmpty() || Context->SelectedAssets.Num() > 1)
		{
			return;
		}

		FAssetData SelectedAsset = Context->SelectedAssets[0];

		InSection.AddMenuEntry(
			"EditMetadata",
			NSLOCTEXT("FMetadataEditorModule", "MetadataEditorLabel", "Edit Metadata"),
			NSLOCTEXT("FMetadataEditorModule", "MetadataEditorTooltip", "Edit metadatas of this asset."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Edit"),
			FUIAction(FExecuteAction::CreateStatic(&FMetadataEditorModule::OnEditMetadataClicked, SelectedAsset))
		);
	}));
}

void FMetadataEditorModule::OnEditMetadataClicked(FAssetData SelectedAsset)
{
	UClass* WidgetClass = LoadClass<UMetadataEditorWidget>(nullptr,TEXT("/MetadataEditor/Widgets/EUW_MetadataEditorWidget.EUW_MetadataEditorWidget_C"));

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
	
	WidgetInstance->InitializeWithAsset(SelectedAsset.GetAsset());

	const TSharedPtr<SWindow> Window = SNew(SWindow)
		.Title(FText::FromString(FString::Printf(TEXT("Edit %s Metadata"), *SelectedAsset.GetAsset()->GetName())))
		.ClientSize(FVector2D(300, 200))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		.SizingRule(ESizingRule::UserSized)
		[
			WidgetInstance->TakeWidget()
		];
	
	FSlateApplication::Get().AddModalWindow(Window.ToSharedRef(), FGlobalTabmanager::Get()->GetRootWindow());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMetadataEditorModule, MetadataEditor)
