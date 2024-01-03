// Copyright (C) 2023 owoDra

#include "GameplayAbilityWithWidget.h"

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
		auto* OwningActor{ ActorInfo->OwnerActor.Get() };

		for (const auto& KVP : WidgetToAdd)
		{
			const auto& Tag{ KVP.Key };
			const auto& Class{ KVP.Value };

			if (Tag.IsValid() && Class)
			{
				auto Handle{ Subsystem->RegisterExtensionAsWidgetForContext(Tag, OwningActor, Class, -1) };

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
