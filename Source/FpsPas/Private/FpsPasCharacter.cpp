// Copyright Epic Games, Inc. All Rights Reserved.

#include "FpsPasCharacter.h"
#include "FpsPasProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/InputSettings.h"
#include "NiagaraComponent.h"


//////////////////////////////////////////////////////////////////////////
// AFpsPasCharacter

AFpsPasCharacter::AFpsPasCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.0f;

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.0f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->PostProcessBlendWeight = 1.0f;

	DefaultPostProcess = FPostProcessSettings();
	DefaultPostProcess.BloomIntensity = 1.25f;
	DefaultPostProcess.AutoExposureMethod = AEM_Manual;
	DefaultPostProcess.AutoExposureBias = 10.32f;
	DefaultPostProcess.LensFlareIntensity = 0.25f;
	DefaultPostProcess.WhiteTemp = 7378.0f;
	DefaultPostProcess.ColorSaturation = FVector4(1.075f, 1.075f, 1.075f, 1.0f);
	DefaultPostProcess.AmbientOcclusionIntensity = 1.0f;
	
	DefaultPostProcess.bOverride_BloomIntensity = true;
	DefaultPostProcess.bOverride_AutoExposureMethod = true;
	DefaultPostProcess.bOverride_AutoExposureBias = true;
	DefaultPostProcess.bOverride_LensFlareIntensity = true;
	DefaultPostProcess.bOverride_WhiteTemp = true;
	DefaultPostProcess.bOverride_ColorSaturation = true;
	DefaultPostProcess.bOverride_AmbientOcclusionIntensity = true;

	DistortionPostProcess = DefaultPostProcess;
	DistortionPostProcess.SceneFringeIntensity = 10.0f;
	DistortionPostProcess.VignetteIntensity = 0.8f;
	
	DistortionPostProcess.bOverride_SceneFringeIntensity = true;
	DistortionPostProcess.bOverride_VignetteIntensity = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));

	Distortion = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Distortion"));
	Distortion->SetupAttachment(FirstPersonCamera);
	Distortion->SetOnlyOwnerSee(true);
	Distortion->bCastDynamicShadow = false;
	Distortion->CastShadow = false;
	Distortion->SetRelativeLocation(FVector(80.0f, 0.0f, 0.0f));
	Distortion->SetRelativeScale3D(FVector(4.0f));
	Distortion->SetAutoActivate(false);

	// Initialize the noise emitter component
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
}

void AFpsPasCharacter::CollectAmmo(const int32 Ammo) const
{
	OnCollectAmmo.Broadcast(Ammo);
}

void AFpsPasCharacter::EnableDistortion() const
{
	FirstPersonCamera->PostProcessSettings = DistortionPostProcess;
	Distortion->Activate();
}

void AFpsPasCharacter::DisableDistortion() const
{
	FirstPersonCamera->PostProcessSettings = DefaultPostProcess;
	Distortion->Deactivate();
}

void AFpsPasCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

//////////////////////////////////////////////////////////////////////////// Input

void AFpsPasCharacter::MoveForward(const float Value)
{
	// add movement in that direction
	AddMovementInput(GetActorForwardVector(), Value);
}

void AFpsPasCharacter::MoveRight(const float Value)
{
	// add movement in that direction
	AddMovementInput(GetActorRightVector(), Value);
}

void AFpsPasCharacter::TurnAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFpsPasCharacter::LookUpAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFpsPasCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed)
		return;
	
	if (FingerIndex == TouchItem.FingerIndex && !TouchItem.bMoved)
	{
		OnPrimaryAction();
	}
	
	TouchItem.bIsPressed = true;
	TouchItem.Location = Location;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.bMoved = false;
}

void AFpsPasCharacter::EndTouch(const ETouchIndex::Type, const FVector)
{
	if (TouchItem.bIsPressed == false)
		return;
	
	TouchItem.bIsPressed = false;
}

void AFpsPasCharacter::BeginPlay()
{
	Super::BeginPlay();

	DisableDistortion();
}

void AFpsPasCharacter::SetupPlayerInputComponent(UInputComponent* const PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AFpsPasCharacter::OnPrimaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AFpsPasCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AFpsPasCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AFpsPasCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AFpsPasCharacter::LookUpAtRate);
}

void AFpsPasCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PawnMakeNoise(1.0f, GetActorLocation(), true, this);
}

bool AFpsPasCharacter::EnableTouchscreenMovement(UInputComponent* const& PlayerInputComponent)
{
	if (!FPlatformMisc::SupportsTouchInput() && !GetDefault<UInputSettings>()->bUseMouseForTouch)
		return false;
	
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFpsPasCharacter::BeginTouch);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFpsPasCharacter::EndTouch);

	return true;
}
