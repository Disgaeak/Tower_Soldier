// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetControl.h"

FString UWidgetControl::GetDialogue()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message)
	return Message;
}