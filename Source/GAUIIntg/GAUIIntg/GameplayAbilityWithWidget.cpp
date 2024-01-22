// Copyright (C) 2024 owoDra

#include "GameplayAbilityWithWidget.h"

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

	this->AddExtensions(ActorInfo);
}

void UGameplayAbilityWithWidget::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	this->RemoveExtensions(ActorInfo);
}
