// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerCharater.generated.h"

class UPaperFlipbook;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PJUNREAL_API APlayerCharater : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharater();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveRight(float Value);
    void StartJump();
    void StopJump();

    void UpdateAnimation();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UPaperFlipbook* IdleAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UPaperFlipbook* RunAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UPaperFlipbook* JumpAnimation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* SideViewCameraComponent;

private:
    float MoveValue;

};
