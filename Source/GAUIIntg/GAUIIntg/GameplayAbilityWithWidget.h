// Copyright (C) 2023 owoDra

#pragma once

#include "GAEGameplayAbility.h"

#include "Extension/UIExtensionPointTypes.h"

#include "GameplayAbilityWithWidget.generated.h"

class UUserWidget;


/**
 * GameplayAbility class with features for adding widgets
 */
UCLASS(Abstract)
class GAUIINTG_API UGameplayAbilityWithWidget : public UGAEGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbilityWithWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//
	// Mapping list of widget classes to be added to the UIExtensionPoint specified when granting abilities
	// 
	// Key:
	//	UIExtensionPointTag
	// 
	// Key:
	//	Widget class
	//
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (ForceInlineRow, Categories = "UI.Extension"))
	TMap<FGameplayTag, TSubclassOf<UUserWidget>> WidgetToAdd;

	//
	// Handle list of added UIExtension
	//
	UPROPERTY(Transient)
	TArray<FUIExtensionHandle> AddedExtensionHandles;

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
