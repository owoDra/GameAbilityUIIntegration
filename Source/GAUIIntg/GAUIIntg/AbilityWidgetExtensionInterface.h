// Copyright (C) 2024 owoDra

#pragma once

#include "UObject/Interface.h"

#include "Extension/UIExtensionPointTypes.h"
#include "Extension/UIExtensionPointSubsystem.h"

#include "GameplayTagContainer.h"

#include "AbilityWidgetExtensionInterface.generated.h"

class UUserWidget;
struct FGameplayAbilityActorInfo;


/**
 * List of widgets to be added to ExtensionPoint when granting abilities
 * 
 * Note:
 *	This structure exists for use with the IAbilityWidgetExtensionInterface
 */
USTRUCT(BlueprintType)
struct GAUIINTG_API FAbilityWidgetExtensionsContainer
{
	GENERATED_BODY()
public:
	FAbilityWidgetExtensionsContainer() {}

public:
	//
	// Mapping list of widget classes to be added to the UIExtensionPoint specified when granting abilities
	// 
	// Key:
	//	UIExtensionPointTag
	// 
	// Key:
	//	Widget class
	//
	UPROPERTY(EditDefaultsOnly, meta = (ForceInlineRow, Categories = "UI.Extension"))
	TMap<FGameplayTag, TSubclassOf<UUserWidget>> WidgetToAdd;

	//
	// Handle list of added UIExtension
	//
	UPROPERTY(Transient)
	TArray<FUIExtensionHandle> AddedExtensionHandles;
};


/**
 * Interface for adding widgets to widget extensions when granting abilities
 */
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
 class GAUIINTG_API UAbilityWidgetExtensionInterface : public UInterface
 {
	 GENERATED_BODY()
 };
 
 class GAUIINTG_API IAbilityWidgetExtensionInterface : public IInterface
 {
	 GENERATED_BODY()
 protected:
	 virtual FAbilityWidgetExtensionsContainer& GetExtensionContainer() = 0;

 public:
	 virtual void AddExtensions(const FGameplayAbilityActorInfo* ActorInfo);
	 virtual void RemoveExtensions(const FGameplayAbilityActorInfo* ActorInfo);

 };

