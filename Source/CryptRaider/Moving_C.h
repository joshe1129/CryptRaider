#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Moving_C.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMoving_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoving_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool newShouldMove);

private:
	UPROPERTY(EditAnywhere)
	FVector moveOffset;

	UPROPERTY(EditAnywhere)
	float moveTime = 4;

	bool shouldMove = false;

	FVector originalLocation;
};
