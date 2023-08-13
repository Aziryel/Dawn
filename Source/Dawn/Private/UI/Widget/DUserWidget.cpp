// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DUserWidget.h"

void UDUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
