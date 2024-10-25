#include "SmartAI/Characters/Enemy/RangedEnemy.h"

#include "Kismet/GameplayStatics.h"

ARangedEnemy::ARangedEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(), UnEquipSocketName);
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshFinder(TEXT("/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Gideon_Ring_Portal"));

	if(WeaponMeshFinder.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(WeaponMeshFinder.Object);
	}

	AttackRange = DefenseRange = 600;
}

void ARangedEnemy::ToggleArmed()
{
	const FName NewSocketName = IsArmed ? UnEquipSocketName : EquipSocketName;
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NewSocketName);
}

void ARangedEnemy::Fire()
{
	if (LineTraceTarget(DrawFireLine))
	{
		UGameplayStatics::ApplyDamage(GetEnemyController()->GetAttackingTarget(), Damage, GetEnemyController(), this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, FString::Printf(TEXT("Hit[%s]! Make Damage: %f"), *GetEnemyController()->GetAttackingTarget()->GetActorNameOrLabel(), Damage));

	}

}

bool ARangedEnemy::LineTraceTarget(bool DrawDebug) const
{
	if (!GetEnemyController() || !GetEnemyController()->GetAttackingTarget()) return false;


	if (!GetEnemyController()->GetAttackingTarget()) return false;

	FVector LineStart = GetMesh()->GetSocketLocation(FName(TEXT("Muzzle_01")));
	FVector LineEnd = GetEnemyController()->GetAttackingTarget()->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Pawn, Params);
	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false, 1, 0, 2);
	}

	return HitResult.GetActor() && HitResult.GetActor() == GetEnemyController()->GetAttackingTarget();
}
