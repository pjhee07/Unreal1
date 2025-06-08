// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharater.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

APlayerCharater::APlayerCharater()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->GravityScale = 2.5f;
    GetCharacterMovement()->AirControl = 0.8f;
    GetCharacterMovement()->JumpZVelocity = 1000.f;
    GetCharacterMovement()->MaxWalkSpeed = 600.f;

    bUseControllerRotationYaw = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.f;
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    SideViewCameraComponent->bUsePawnControlRotation = false;

    MoveValue = 0.f;

}

void APlayerCharater::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerCharater::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateAnimation();
}

void APlayerCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharater::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharater::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharater::StopJump);
}

void APlayerCharater::MoveRight(float Value)
{
    MoveValue = Value;

    AddMovementInput(FVector(1.f, 0.f, 0.f), Value);

    if (Value < 0.f)
        GetSprite()->SetRelativeRotation(FRotator(0.f, 180.f, 0.f)); 
    else if (Value > 0.f)
        GetSprite()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f)); 
}

void APlayerCharater::StartJump()
{
    Jump();
}

void APlayerCharater::StopJump()
{
    StopJumping();
}

void APlayerCharater::UpdateAnimation()
{
    //const FVector Velocity = GetVelocity();
    const bool bIsFalling = GetCharacterMovement()->IsFalling();

    if (bIsFalling && JumpAnimation)
    {
        GetSprite()->SetFlipbook(JumpAnimation);
    }
    else if (FMath::Abs(MoveValue) > 0.1f && RunAnimation)
    {
        GetSprite()->SetFlipbook(RunAnimation);
    }
    else if (IdleAnimation)
    {
        GetSprite()->SetFlipbook(IdleAnimation);
    }
}
