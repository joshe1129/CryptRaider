#include "Moving_C.h"
#include "Math/UnrealMathUtility.h"

UMoving_C::UMoving_C()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoving_C::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetOwner()->GetActorLocation();	
}


void UMoving_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector targetLocation = originalLocation;

	if (shouldMove)
	{
		targetLocation = originalLocation + moveOffset;
	}


	FVector currentLocation = GetOwner()->GetActorLocation();
	float speed = moveOffset.Length() / moveTime;

	FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
	GetOwner()->SetActorLocation(newLocation);
}

void UMoving_C::SetShouldMove(bool newShouldMove)
{
	shouldMove = newShouldMove;
	//UE_LOG(LogTemp, Warning, TEXT("SetShouldMove: Should move set to: %s"), shouldMove ? TEXT("true") : TEXT("false"));
}