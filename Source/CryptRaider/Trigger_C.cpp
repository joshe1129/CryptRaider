#include "Trigger_C.h"

UTrigger_C::UTrigger_C()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrigger_C::BeginPlay()
{
	Super::BeginPlay();
}

void UTrigger_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mover_C == nullptr)
	{
		return;
	}

	AActor* actor = GetAcceptableActor();
	if (actor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TickComponent: Found acceptable actor: %s"), *actor->GetName());

		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != nullptr)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		mover_C->SetShouldMove(true);
	}
	else
	{
		mover_C->SetShouldMove(false);
	}
}

void UTrigger_C::SetMover(UMoving_C* newMover)
{
	mover_C = newMover;
}

AActor* UTrigger_C::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);


	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(actorTag) && !Actor->ActorHasTag("Grabbed"))
		{
			// Log cuando se encuentra un actor aceptable
			//UE_LOG(LogTemp, Warning, TEXT("GetAcceptableActor: Acceptable actor found: %s"), *Actor->GetName());
			return Actor;
		}
	}
	return nullptr;
}