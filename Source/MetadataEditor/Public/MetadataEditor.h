// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FMetadataEditorModule : public IModuleInterface
{
public:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
