// Fill out your copyright notice in the Description page of Project Settings.


#include "Generacion_ladrillos.h"
#include <Engine/World.h>

// Sets default values
AGeneracion_ladrillos::AGeneracion_ladrillos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	timeToSpawn = 1.0f;//milisecons

	amount_x = 10;
	amount_z = 10;
	count_x = 0;
	count_z = 0;

	distace_spawn_x = 300;
	distace_spawn_z = 200;

	horizontal_can_instantiate_bricks = true;
	vertical_can_instantiate_bricks = false;
	diagonal_can_instantiate_bricks = false;
	
	offset_x = 0;
	offset_z = 0;
	can_spawn = false;
	check_offset_X = 0;
	check_offset_Z = 0;
	final_offset_x = 0;
	final_offset_z= 0;
	check_final_offset_X = 4;
	check_final_offset_Z = 0;
}

// Called when the game starts or when spawned
void AGeneracion_ladrillos::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() == nullptr) return;

	if (horizontal_can_instantiate_bricks || vertical_can_instantiate_bricks || diagonal_can_instantiate_bricks)
	{
		//FVector initi_brick_position = FVector::ZeroVector;
		//spawn_brick(brick_reference, initi_brick_position);//spawn new brick first
		GetWorld()->GetTimerManager().SetTimer(timer_spawn_handler, this, &AGeneracion_ladrillos::SpawnTimer_out, timeToSpawn, true);
	}
}

void AGeneracion_ladrillos::SpawnTimer_out()
{
	
	if (horizontal_can_instantiate_bricks)//if instance lineal
	{
		FVector reference_lineal_brick_position = FVector::ZeroVector;//reference variable
		bool can_instance_brick = horizontal_new_position_to_end(reference_lineal_brick_position);
		if (can_instance_brick)
		{
			spawn_brick(brick_reference, reference_lineal_brick_position);//spawn new brick
		}
	}
	if (vertical_can_instantiate_bricks)//if instance vertical
	{
		FVector reference_vertical_brick_position = FVector::ZeroVector;//reference variable
		bool can_instance_brick = vertical_new_position_to_end(reference_vertical_brick_position);
		if (can_instance_brick)
		{
			spawn_brick(brick_reference, reference_vertical_brick_position);//spawn new brick
		}
	}
	if (diagonal_can_instantiate_bricks)//if instance vertical
	{
		FVector reference_diagonal_brick_position = FVector::ZeroVector;//reference variable
		bool can_instance_brick = diagonal_new_position_to_end(reference_diagonal_brick_position);
		if (can_instance_brick)
		{
			spawn_brick(brick_reference, reference_diagonal_brick_position);//spawn new brick
		}
	}
	
}

void AGeneracion_ladrillos::spawn_brick(TSubclassOf<AActor> brick, FVector positionBrick)
{
	if (GetWorld() == nullptr) return;
	FActorSpawnParameters SpawnParams;
	
	AActor* newbrick = GetWorld()->SpawnActor<AActor>(
		brick,
		positionBrick,
		FRotator::ZeroRotator,
		SpawnParams
		);
	
	FAttachmentTransformRules rules(
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			false
		);

	newbrick->AttachToActor(this, rules);

	
}

bool AGeneracion_ladrillos::horizontal_new_position_to_end(FVector &brick_position)
{
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("instance brick"));
	brick_position = FVector::ZeroVector;
	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	brick_position.Y = 0;
	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	
	check_X_counter = count_x;
	check_Z_counter = count_z;

	if (count_x >= amount_x - 1)//if there are more in X than quantity X
	{
		count_x = 0;
		count_z += 1;

		if (count_z > amount_z - 1)//if there are more in Y than quantity Y
		{
			GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
			return false;
		}
	}
	else
	{
		count_x += 1;
	}


	return true;
}

bool AGeneracion_ladrillos::vertical_new_position_to_end(FVector& brick_position)
{
	//if (GEngine)
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("instance brick"));
	brick_position = FVector::ZeroVector;
	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	brick_position.Y = 0;
	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);

	check_X_counter = count_x;
	check_Z_counter = count_z;

	if (count_z >= amount_z - 1)//if there are more in X than quantity X
	{
		count_z = 0;
		count_x += 1;

		if (count_x > amount_x - 1)//if there are more in Y than quantity Y
		{
			GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
			return false;
		}
	}
	else
	{
		count_z += 1;
	}


	return true;
}


bool AGeneracion_ladrillos::diagonal_new_position_to_end(FVector& brick_position)
{
	//if (GEngine)
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("instance brick"));

	//if (offset_x == amount_x -1 && offset_z == amount_z -1)
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
	//	return false;
	//}

	//tener en cuenta que esto representa el resultado anterior
	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	brick_position.Y = 0;
	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	////////////////////////////////////////////////////


	check_X_counter = count_x;
	check_Z_counter = count_z;
	check_offset_X = offset_x;
	check_offset_Z = offset_z;
	check_final_offset_X = final_offset_x;
	check_final_offset_Z = final_offset_z;

	//if (offset_x == amount_x - 1 && offset_z == amount_z - 1)//cuando termina la diagonal
	//{
	//	
	//}
	if (count_x == amount_x - 1  && count_z == amount_z )//termino de instanciar 
	{
		GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
		return false;
	}

	else//sino comienzo a instanciar
	{
		if (offset_z == offset_x)//solo si son iguales paso al proximo offset X
		{
			if (offset_x < amount_x -1)//sino llego al final de X sumo una posici�n en X
			{
				offset_x += 1;
				count_x = offset_x;
				count_z = 0;
			}
			else
			{
				count_x = amount_x - 1;
				count_z += 1;

				offset_x = count_x;
				offset_z = count_z;
			}
		}
		else//mantiene en offset x hasta que termine la diagonal
		{
			if (count_z != offset_x)//voy intercalando posiciones
			{
				count_z += 1;//sumo en z
				count_x -= 1;//resto en X
				
				const int int_to_print = count_z;
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("int: %i"), int_to_print));
			}
			else //si la diagonal termino
			{
				count_z = count_x;//z tendria que volver a la posici�n en y
				count_x = offset_x;//vuelvo al offset
				offset_z = offset_x;//offset vuelve a posicion x
			}
		}
	}
	


	//if (count_z == 0)
	//{
	//	count_x = offset_x;
	//}
	//if (count_x > count_z)//I stay at the index of "x" until I reach the same amount in "z"
	//{
	//	count_z = count_x;
	//	count_x -= 1;
	//}
	//else
	//{
	//	offset_x += 1;//sum in x
	//}

	


	//if (offset_x < count_z)//if there are more in X than quantity X
	//{
	//	//count_x += 1;
	//	offset_x += 1;
	//	//count_x = offset_x;

	//	brick_position = FVector::ZeroVector;
	//	brick_position.X = GetActorLocation().X + (distace_spawn_x * offset_x);
	//	brick_position.Y = 0;
	//	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	//}
	//else
	//{
	//	count_z += 1;
	//	offset_x = 0;

	//	brick_position = FVector::ZeroVector;
	//	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	//	brick_position.Y = 0;
	//	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	//}

	return true;
}


//bool AGeneracion_ladrillos::diagonal_new_position_to_end(FVector& brick_position)
//{
//	//if (GEngine)
////	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("instance brick"));
//
//	if (count_z > amount_z)
//	{
//		GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
//		return false;
//	}
//
//	check_X_counter = count_x;
//	check_Z_counter = count_z;
//	
//
//	if (offset_x < count_z)//if there are more in X than quantity X
//	{
//		//count_x += 1;
//		offset_x += 1;
//		//count_x = offset_x;
//
//		brick_position = FVector::ZeroVector;
//		brick_position.X = GetActorLocation().X + (distace_spawn_x * offset_x);
//		brick_position.Y = 0;
//		brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
//	}
//	else
//	{
//		count_z += 1;
//		offset_x = 0;
//
//		brick_position = FVector::ZeroVector;
//		brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
//		brick_position.Y = 0;
//		brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
//	}
//	
//	return true;
//}


// Called every frame
void AGeneracion_ladrillos::Tick(float DeltaTime)
{

}

