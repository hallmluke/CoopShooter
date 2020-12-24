// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "SHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));

	HealthComp->OnHealthChanged.AddDynamic(this, &ASExplosiveBarrel::OnHealthChanged);

	bExploded = false;

	ExplosionForceValue = 1000;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::Explode()
{
	if (ExplosionEffect) {
		UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, MeshComp, NAME_None, FVector(ForceInit), FRotator::ZeroRotator, (FVector) (4.0f));

		MeshComp->SetMaterial(0, ExplodedMaterial);
		MeshComp->AddForce(GetActorUpVector() * ExplosionForceValue);

		RadialForceComp->FireImpulse();
	}
}

void ASExplosiveBarrel::OnHealthChanged(USHealthComponent* HealthComponent, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f && !bExploded) {
		// Die!
		bExploded = true;

		Explode();
	}
}


