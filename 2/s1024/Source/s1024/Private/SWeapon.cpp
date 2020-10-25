// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

//��ʱ16
void ASWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); //����EyeLocation��EyeRotation ��MyOwner��õ�
		FVector ShotDirection = EyeRotation.Vector();
		FVector EndLocation = EyeLocation + ShotDirection * 10000;
		FCollisionQueryParams Params; //�����ײ��ϸ��
		Params.AddIgnoredActor(MyOwner); //������ײ����
		Params.AddIgnoredActor(this); //������ײ��ǹ
		Params.bTraceComplex = true; //��ײ��������嵽��
		FHitResult OutHit;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, EyeLocation, EndLocation, ECC_Visibility, Params))
		{
			//1 2 ������ʼλ�� 3 ������ֹλ�� 4 ��Ҫ����Щ������ 5 ��ײϸ��

			AActor* HitActor = OutHit.GetActor(); //��˭����
			

			//����˺�
			UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, OutHit, MyOwner->GetInstigatorController(), this, DamageType);
			//1 HitActor ��˭ 2 �����˺� 3 ���䷽�� 4 OutHit 5 �˺���Դ 6 �˺���ɵ����� 7 �˺�����

			WScore++;
			UE_LOG(LogTemp, Warning, TEXT("666"));
		}
		
		DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::White, false, 1.0, 0, 1);
		//1 world 2 ��ʼλ�� 3 �յ� 4 ���ߵ���ɫ 5 �Ƿ���Ҫ�������� 6 ���ڵ�ʱ�� 7 ���ȼ� 8 �߿��
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

