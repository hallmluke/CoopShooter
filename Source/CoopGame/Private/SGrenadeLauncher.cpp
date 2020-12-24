// Fill out your copyright notice in the Description page of Project Settings.


#include "SGrenadeLauncher.h"
#include "SGrenade.h"

void ASGrenadeLauncher::Fire() {
	AActor* MyOwner = GetOwner();
	if (MyOwner && GrenadeClass) {
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		//FRotator MuzzleRotation = MeshComp->GetSocketRotation(MuzzleSocketName);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = Cast<APawn>(GetOwner());

		GetWorld()->SpawnActor<ASGrenade>(GrenadeClass, MuzzleLocation, EyeRotation, ActorSpawnParams);
	}
}