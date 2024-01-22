// Copyright (C) 2024 owoDra

#pragma once

#include "GAEGameplayAbility.h"
#include "AbilityWidgetExtensionInterface.h"

#include "GameplayAbilityWithWidget.generated.h"

class UUserWidget;
struct FUIExtensionHandle;


/**
 * GameplayAbility class with features for adding widgets
 */
UCLASS(Abstract)
class GAUIINTG_API UGameplayAbilityWithWidget : public UGAEGameplayAbility, public IAbilityWidgetExtensionInterface
{
	GENERATED_BODY()
public:
	UGameplayAbilityWithWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (ShowOnlyInnerProperties))
	FAbilityWidgetExtensionsContainer WidgetToAdd;

protected:
	virtual FAbilityWidgetExtensionsContainer& GetExtensionContainer() { return WidgetToAdd; }

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
