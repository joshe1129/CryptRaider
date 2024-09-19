#include "Grabber_C.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UGrabber_C::UGrabber_C()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber_C::BeginPlay()
{
	Super::BeginPlay();	
}

void UGrabber_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicHandle = GetPhysicsHandle();

	if (physicHandle && physicHandle->GetGrabbedComponent() != nullptr)
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}

void UGrabber_C::Grab()
{
	UPhysicsHandleComponent* physicHandle = GetPhysicsHandle();
	if (physicHandle == nullptr)
	{
		return;
	}

	FHitResult hitResult;
	bool hasHit = GetGrabbableObject(hitResult);
	
	if (hasHit)
	{
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		AActor* hitActor = hitResult.GetActor();
		hitActor->Tags.Add("Grabbed");
		hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		physicHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()		
		);
		//DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Magenta, false, 7);
	}
}

void UGrabber_C::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if (physicsHandle && physicsHandle->GetGrabbedComponent() != nullptr)
	{
		AActor* grabbedActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		grabbedActor->Tags.Remove("Grabbed");
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		physicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber_C::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}

	return result;
}

bool UGrabber_C::GetGrabbableObject(FHitResult& outHitResult) const
{
	FVector startSweep = GetComponentLocation();
	FVector endSweep = startSweep + GetForwardVector() * maxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);

	return GetWorld()->SweepSingleByChannel(
		outHitResult,
		startSweep, endSweep,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere
	);
}