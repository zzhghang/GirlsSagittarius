// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"


#include "MultiplayerSessionSubsystem.generated.h"



//�Զ���ί��
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiPlayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiPlayerOnFindSessionComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiPlayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiPlayerOnDestorySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiPlayerOnStartSessionComplete, bool, bWasSuccessful);

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionSubsystem();

	//
	//�Ự��غ���
	//
	void CreateSession(int32 NumPublicConnect, FString MatchType);
	void FindSession(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestorySession();
	void StartSession();

	FMultiPlayerOnCreateSessionComplete MultiPlayerOnCreateSessionComplete;
	FMultiPlayerOnFindSessionComplete MultiPlayerOnFindSessionComplete;
	FMultiPlayerOnJoinSessionComplete MultiPlayerOnJoinSessionComplete;
	FMultiPlayerOnDestorySessionComplete MultiPlayerOnDestorySessionComplete;
	FMultiPlayerOnStartSessionComplete MultiPlayerOnStartSessionComplete;

protected:

	//�ص�����
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestorySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);


private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;	
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	//
	//ί��
	//
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FDelegateHandle FindSessionCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestorySessionCompleteDelegate;
	FDelegateHandle DestorySessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	bool bCreateSessionOnDestory{ false };
	int32 LastNumPublicConnections;
	FString LastMatchType;
};
