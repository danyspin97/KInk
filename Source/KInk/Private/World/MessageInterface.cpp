// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "World/MessageHandler.h"
#include "MessageInterface.h"

UMessageInterface::UMessageInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IMessageInterface::OnMessage(struct FMessage Message)
{
	
}
