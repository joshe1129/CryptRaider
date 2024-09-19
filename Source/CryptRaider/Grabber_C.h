#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber_C.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber_C : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:
	UPROPERTY(EditAnywhere)
	float maxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float grabRadius= 100;

	UPROPERTY(EditAnywhere)
	float holdDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableObject(FHitResult& outHitResult) const;

};
