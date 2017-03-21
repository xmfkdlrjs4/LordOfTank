// Fill out your copyright notice in the Description page of Project Settings.

#include "LordOfTank.h"
#include "Weapon/HomingProjectile.h"




AHomingProjectile::AHomingProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");				//�浹ü�� ������ �̸��� �����Ѵ�.
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
	CollisionComp->OnComponentHit.AddDynamic(this, &AHomingProjectile::OnHit);		// set up a notification for when this component hits something blocking

																							// Set as root component
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoStaticMesh(TEXT("StaticMesh'/Game/LOTAssets/TankAssets/Meshes/ArmorPiercingAmmo.ArmorPiercingAmmo'"));
	AmmoMesh->SetStaticMesh(AmmoStaticMesh.Object);
	AmmoMesh->SetupAttachment(RootComponent);
	AmmoMesh->SetRelativeRotation(FRotator(90.f, 0.0f, 0.0f));
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);






	//������ƮŸ�Ϲ����Ʈ������Ʈ�� �������� ������Ʈ ��ġ�� ��Ÿ���� �� ������Ʈ�� �ƴϱ� ������ ���̰ų� ���� �ʴ´�.
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 8000.f;
	ProjectileMovement->MaxSpeed = 8000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;	//�ӵ��� ���� źȯ�� ȸ����Ű�� ���� �� ����Ѵ�.
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 1.f;

	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;

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