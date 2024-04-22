#include "CombatComponent.h"

#include "Engine/SkeletalMeshSocket.h"

#include "DroneGame/Pawn/BasePawn.h"
#include "DroneGame/Actor/Weapon.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    bWantsInitializeComponent = true;

}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCombatComponent::InitializeComponent()
{
    Super::InitializeComponent();

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeComponent() failed: GetComponentOwner() returned nullptr [Component ID: %s]"), *GetName());
        return;
    }

    BasePawnOwner = Cast<ABasePawn>(Owner);
    if (!BasePawnOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeComponent() failed: Owner is not of type ABasePawn [Component ID: %s]"), *GetName());
        return;
    }

    CreateWeapon();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::CreateWeapon()
{
    UWorld* World = GetWorld();
    if (!World) {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: GetWorld() returned nullptr [Actor: %s]"), *GetName());
        return;
    }

    if (!BasePawnOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: BasePawnOwner is not valid [Component ID: %s]"), *GetName());
        return;
    }

    USkeletalMeshComponent* SkeletalMesh = BasePawnOwner->GetSkeletalMeshComponent();
    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: SkeletalMeshComponent is nullptr on BasePawnOwner [Component ID: %s]"), *GetName());
        return;
    }

    const USkeletalMeshSocket* AttachWeaponSocket = SkeletalMesh->GetSocketByName(AttachWeaponSocketName);
    if (!AttachWeaponSocket) {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: SocketName \"%s\" was not found  [Component ID: %s]"), *AttachWeaponSocketName.ToString(), *GetName());
        return;
    }
    FTransform SocketTransform = AttachWeaponSocket->GetSocketTransform(SkeletalMesh);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    AWeapon* NewWeapon = World->SpawnActor<AWeapon>(CurrentWeaponClass, BasePawnOwner->GetTransform(), SpawnParams);

    if (!NewWeapon) {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: GetComponentOwner() returned nullptr [Component ID: %s]"), *GetName());
        return;
    }

    CurrentWeapon = NewWeapon;
    CurrentWeapon->SetWeaponOwner(BasePawnOwner);

    bool bAttachActorResult = AttachWeaponSocket->AttachActor(CurrentWeapon, SkeletalMesh);
    if (!bAttachActorResult) {
        UE_LOG(LogTemp, Error, TEXT("CreateWeapon() failed: AttachActor failed [Component ID: %s]"), *GetName());
        return;
    }
}

void UCombatComponent::Shoot()
{
	if (!IsValid(CurrentWeapon)) {
        UE_LOG(LogTemp, Error, TEXT("Shoot() failed: CurrentWeapon is not valid [Component ID: %s]"), *GetName());
        return;
    }

    if (!CurrentWeapon->IsA(CurrentWeaponClass)) {
        UE_LOG(LogTemp, Error, TEXT("Shoot() failed: CurrentWeapon is not of type CurrentWeaponClass [Component ID: %s]"), *GetName());
        return;
    }
	CurrentWeapon->Shoot();
}

void UCombatComponent::Shoot(const FVector3d& Direction)
{
    if (!IsValid(CurrentWeapon)) {
        UE_LOG(LogTemp, Error, TEXT("Shoot() failed: CurrentWeapon is not valid [Component ID: %s]"), *GetName());
        return;
    }

    if (!CurrentWeapon->IsA(CurrentWeaponClass)) {
        UE_LOG(LogTemp, Error, TEXT("Shoot() failed: CurrentWeapon is not of type CurrentWeaponClass [Component ID: %s]"), *GetName());
        return;
    }
    CurrentWeapon->Shoot(Direction);
}

AWeapon* UCombatComponent::GetCurrentWeapon() const
{
    return CurrentWeapon;
}

