// AIHalfHpState.h
// Zixuan Shi
// AI when object is half hp

#pragma once
#include "AIComponent.h"

// #DG: Looks like this isn't used anywhere and can/should be removed. 
class AIHalfHpState : public AIState
{
public:
	AIHalfHpState(Pokemon& pokemon);

	virtual void OnEnter() override final;
	virtual void Update() override final;
	virtual void OnExit() override final;
};

