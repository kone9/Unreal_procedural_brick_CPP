// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generacion_ladrillos.generated.h"

UCLASS()
class PROCEDURAL_BRICKS_API AGeneracion_ladrillos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneracion_ladrillos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//timer
	FTimerHandle timer_spawn_handler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeToSpawn;
	
	UFUNCTION()
	void SpawnTimer_out();


	//birck
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount_z;


	//new position brick
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int distace_spawn_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int distace_spawn_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> brick_reference;
	
	UPROPERTY(BlueprintReadWrite)
	FVector brick_position;

private:
	void spawn_brick(TSubclassOf<AActor> brick, FVector positionBrick);

	bool check_brick_amoutn_end();

	//counter reference actual position
	int count_x;
	int count_z;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};