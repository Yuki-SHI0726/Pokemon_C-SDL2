// AIComponent.h
// Zixuan Shi
// Component of AI

#pragma once

class Pokemon;

//////////////////////////////////
// Interface for AI states
//////////////////////////////////
class AIState
{
protected:
	Pokemon& m_owner;

public:
	AIState(Pokemon& pokemon);
	virtual ~AIState() {};

	virtual void OnEnter() = 0;
	virtual void Update() = 0;
	virtual void OnExit() = 0;
};


// Notes on 11/12/2019


//Agent = Any Character or Object with Ai

//Scripted Behaviour = {switch(), if/else(), enum}

//State Machines = {i.e. Patrol, Attack, Flee}

//Decision tree(Binary, true or false)

/*
				<canSeePlayer>?
				/            \
		<isInRange>?		[Patrol]
		/		  \
	[Attack]   [Move Closer]

*/

//Behavior Tree(Extension on Decision Tree): https://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php

//Utility Theory

//fuzzy logic

//Move = {linear, wandering, }


//Homework

// Try to emplement state machine to enemy