// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMetadataEditor, Log, All);

class FMetadataEditorModule : public IModuleInterface
{
public:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
