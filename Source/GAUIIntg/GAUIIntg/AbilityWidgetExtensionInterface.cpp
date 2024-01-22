// Copyright (C) 2024 owoDra

#include "AbilityWidgetExtensionInterface.h"

#include "Blueprint/UserWidget.h"
#include "Abilities/GameplayAbilityTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityWidgetExtensionInterface)


void IAbilityWidgetExtensionInterface::AddExtensions(const FGameplayAbilityActorInfo* ActorInfo)
{
	auto* Object{ Cast<UObject>(this) };
	auto* World{ Object ? Object->GetWorld() : nullptr };

	if (World && ActorInfo && ActorInfo->IsLocallyControlled())
	{
		auto* Subsystem{ World->GetSubsystem<UUIExtensionPointSubsystem>() };

		auto PlayerController{ ActorInfo->PlayerController };
		auto* LocalPlayer{ PlayerController.IsValid() ? PlayerController->GetLocalPlayer() : nullptr };

		for (const auto& KVP : GetExtensionContainer().WidgetToAdd)
		{
			const auto& Tag{ KVP.Key };
			const auto& Class{ KVP.Value };

			if (Tag.IsValid() && Class)
			{
				auto Handle{ Subsystem->RegisterExtensionAsWidgetForContext(Tag, LocalPlayer, Class, -1) };

				GetExtensionContainer().AddedExtensionHandles.Add(Handle);
			}
		}
	}
}

void IAbilityWidgetExtensionInterface::RemoveExtensions(const FGameplayAbilityActorInfo* ActorInfo)
{
	auto* Object{ Cast<UObject>(this) };
	auto* World{ Object ? Object->GetWorld() : nullptr };

	if (World && ActorInfo && ActorInfo->IsLocallyControlled())
	{
		for (auto& Handle : GetExtensionContainer().AddedExtensionHandles)
		{
			Handle.Unregister();
		}

		GetExtensionContainer().AddedExtensionHandles.Empty();
	}
}
