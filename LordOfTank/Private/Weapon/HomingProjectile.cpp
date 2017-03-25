// Fill out your copyright notice in the Description page of Project Settings.

#include "LordOfTank.h"
#include "Weapon/HomingProjectile.h"




AHomingProjectile::AHomingProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");				//충돌체의 프로필 이름을 설정한다.
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
	CollisionComp->OnComponentHit.AddDynamic(this, &AHomingProjectile::OnHit);		

																							
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoStaticMesh(TEXT("StaticMesh'/Game/LOTAssets/TankAssets/Meshes/ArmorPiercingAmmo.ArmorPiercingAmmo'"));
	AmmoMesh->SetStaticMesh(AmmoStaticMesh.Object);
	AmmoMesh->SetupAttachment(RootComponent);
	AmmoMesh->SetRelativeRotation(FRotator(-90.f, 0.0f, 0.0f));
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 4000.f;
	ProjectileMovement->MaxSpeed = 800000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;	
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 11000.f;
	

}


void AHomingProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Damage Player!");
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();

	}
}

void AHomingProjectile::SetHomingTarget(AActor* HomingTarget)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "SetHomingTarget Call!!");
	if (HomingTarget) {
		ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, HomingTarget->GetName() +"SetHomingTarget Success!!");
		
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "SetHomingTarget Fail!!");
}