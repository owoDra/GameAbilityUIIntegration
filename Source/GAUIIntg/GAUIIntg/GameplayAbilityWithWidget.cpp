// Copyright (C) 2024 owoDra

#include "GameplayAbilityWithWidget.h"

#include "GAUIIntgLogs.h"

#include "Extension/UIExtensionPointTypes.h"
#include "Extension/UIExtensionPointSubsystem.h"

#include "Blueprint/UserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameplayAbilityWithWidget)


UGameplayAbilityWithWidget::UGameplayAbilityWithWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}


void UGameplayAbilityWithWidget::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (ActorInfo->IsLocallyControlled())
	{
		auto* Subsystem{ GetWorld()->GetSubsystem<UUIExtensionPointSubsystem>() };

		auto PlayerController{ ActorInfo->PlayerController };
		auto* LocalPlayer{ PlayerController.IsValid() ? PlayerController->GetLocalPlayer() : nullptr };
		
		for (const auto& KVP : WidgetToAdd)
		{
			const auto& Tag{ KVP.Key };
			const auto& Class{ KVP.Value };

			if (Tag.IsValid() && Class)
			{
				auto Handle{ Subsystem->RegisterExtensionAsWidgetForContext(Tag, LocalPlayer, Class, -1) };

				AddedExtensionHandles.Add(Handle);
			}
		}
	}
}

void UGameplayAbilityWithWidget::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	if (ActorInfo->IsLocallyControlled())
	{
		for (auto& Handle : AddedExtensionHandles)
		{
			Handle.Unregister();
		}

		AddedExtensionHandles.Empty();
	}
}
