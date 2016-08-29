// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "MessageInterface.generated.h"

/**
 * 
 */
 /** Class needed to support InterfaceCast<IToStringInterface>(Object) */
UINTERFACE(MinimalAPI)
class UMessageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IMessageInterface
{
	GENERATED_IINTERFACE_BODY()

	// Base function overrided by each class that extend this interface
	virtual void OnMessage(struct FMessage Message);
};