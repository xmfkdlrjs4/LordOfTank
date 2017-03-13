// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class LORDOFTANK_API AProjectile : public AActor
{
	GENERATED_BODY()
protected:

		/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionComp;

	//�߻�ü �̵��� ���ؼ��� ������ƮŸ�Ϲ����Ʈ������Ʈ�� ����ؾ��Ѵ�.
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


	/*�߻�ü �޽�*/
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* AmmoMesh;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	/** called when projectile hits something */
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//ź�� ��
	float AmmoCount;
	//ź�� ������
	float Damage;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
