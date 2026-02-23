// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BFL.h"

void UC_BFL::PrintActorNetMessage(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has authority"),*Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] does not have authority"), *Actor->GetName());
	}
	ENetRole ActorLocalRole = Actor->GetLocalRole();
	switch(ActorLocalRole)
	{
		case ROLE_None:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is ROLE_None"), *Actor->GetName());
			break;
		case ROLE_SimulatedProxy:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is ROLE_SimulatedProxy"), *Actor->GetName());
			break;
		case ROLE_AutonomousProxy:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is ROLE_AutonomousProxy"), *Actor->GetName());
			break;
		case ROLE_Authority:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is ROLE_Authority"), *Actor->GetName());
			break;
		case ROLE_MAX:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is ROLE_MAX"), *Actor->GetName());
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] LocalRole is Default"), *Actor->GetName());
			break;

	}
	ENetRole ActorRemoteRole = Actor->GetRemoteRole();
	switch (ActorRemoteRole)
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is ROLE_None"), *Actor->GetName());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is ROLE_SimulatedProxy"), *Actor->GetName());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is ROLE_AutonomousProxy"), *Actor->GetName());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is ROLE_Authority"), *Actor->GetName());
		break;
	case ROLE_MAX:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is ROLE_MAX"), *Actor->GetName());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] RemoteRole is Default"), *Actor->GetName());
		break;

	}
}
