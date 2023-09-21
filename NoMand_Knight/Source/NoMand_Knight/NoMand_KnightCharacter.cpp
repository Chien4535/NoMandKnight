// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoMand_KnightCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ANoMand_KnightCharacter

ANoMand_KnightCharacter::ANoMand_KnightCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	Health = 100.f;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	// 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	// 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	// 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	// 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ANoMand_KnightCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook *DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void ANoMand_KnightCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANoMand_KnightCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANoMand_KnightCharacter::MoveRight);

	// Fighting Game Inputs
	PlayerInputComponent->BindAction("StandardAttack", IE_Pressed, this, &ANoMand_KnightCharacter::StandardAttack);
	// PlayerInputComponent->BindAction("CancelStandard", IE_Pressed, this, &ANoMand_KnightCharacter::CancelStandard;
	PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &ANoMand_KnightCharacter::HeavyAttack);
	// PlayerInputComponent->BindAction("CancelHeavy", IE_Pressed, this, &ANoMand_KnightCharacter::CancelHeavy;
	PlayerInputComponent->BindAction("KickAttack", IE_Pressed, this, &ANoMand_KnightCharacter::KickAttack);
	// PlayerInputComponent->BindAction("CancelKick", IE_Pressed, this, &ANoMand_KnightCharacter::CancelKick;
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &ANoMand_KnightCharacter::SpecialAttack);
	// PlayerInputComponent->BindAction("CancelSpecial", IE_Pressed, this, &ANoMand_KnightCharacter::CancelSpecial;

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANoMand_KnightCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANoMand_KnightCharacter::TouchStopped);
}

void ANoMand_KnightCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ANoMand_KnightCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	Jump();
}

void ANoMand_KnightCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();
}

void ANoMand_KnightCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

void ANoMand_KnightCharacter::StandardAttack()
{
	float DamageAmount = 10.0f;
	TakeDamage(DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Standard Attack"));
}

void ANoMand_KnightCharacter::HeavyAttack()
{
	float DamageAmount = 20.0f;
	TakeDamage(DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Heavy Attack"));
}

void ANoMand_KnightCharacter::KickAttack()
{
	float DamageAmount = 5.0f;
	TakeDamage(DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Kick Attack"));
}

void ANoMand_KnightCharacter::SpecialAttack()
{
	float DamageAmount = 35.0f;
	TakeDamage(DamageAmount);

	// Handle animations here later.
	UE_LOG(LogTemp, Warning, TEXT("Special Attack"));
}

void ANoMand_KnightCharacter::TakeDamage(float DamageAmount) {
	if (HasAuthority()) {
		Health -= DamageAmount;
		if (Health <= 0.0f) {
			Health = 0;
			// Do some game over shit here or something uhhhh...
		}
		//Healthbar update function will be needed from UI team.
	}
}