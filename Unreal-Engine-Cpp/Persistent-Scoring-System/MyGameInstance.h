#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAMEPLAYPRACTICE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddScore(int32 amount);

	int32 GetScore() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
	int32 TotalScore = 0;
	
};
