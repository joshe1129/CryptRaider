#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Moving_C.h"
#include "Trigger_C.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTrigger_C : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrigger_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMoving_C* newMover);

private:
	UPROPERTY(EditAnywhere)
	FName actorTag;

	UMoving_C* mover_C;

	FVector testVector = FVector(0.0, -2430.0, 19.540688);
	FRotator testRotation = FRotator(0.0, 0.0, 0.0);

	AActor* GetAcceptableActor() const;
};
