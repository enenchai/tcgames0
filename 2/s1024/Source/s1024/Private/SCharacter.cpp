// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; //���������ƶ������ƾ�ͷ����

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true; //���Զ���




	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	//CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	//�������ݣ����� ���� ��ӳ�� �½�moveforward scale��ֵ����value��ֵ
	//1 ǰ������ 2 ��ǰ1.0f ���-1.0f �ٶ�0.5f 3 Ĭ��false ���Բ�д
	AddMovementInput(GetActorForwardVector(), Value, false);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value, false);
}

void ASCharacter::BeginCrouch()
{
	Crouch();
}

void ASCharacter::EndCrouch()
{
	UnCrouch();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASCharacter::AddScore()
{
	score++;
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//��һ�¶�һ��
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	//pitch y�� roll x�� yaw z��
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); //�����ƶ���ͷ ��z��ǰ����ת
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput); //���¿�

	//��һ�±���״̬
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch); //����
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch); //վ��

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

}

FVector ASCharacter::GetPawnViewLocation() const //�����۾�λ��
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

