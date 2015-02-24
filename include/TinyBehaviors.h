#ifndef TINY_BEHAVIORS_H
#define TINY_BEHAVIORS_H
#define MAX_CHILDREN 10
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TinyBehavior;

//Task type definition
typedef bool (*Task)(TinyBehavior*, double);

struct TinyBehavior
{
	TinyBehavior()
	{
		ChildCount = 0;
		CurrentTask = NULL;
		for (unsigned int Iter = 0; Iter < MAX_CHILDREN; Iter++)
		{
			Children[Iter] = NULL;
		}
		ChildCount = NULL;
		ParentNode = NULL;
	}
	TinyBehavior(const char* BehaviorName, Task NewTask)
	{
		CurrentTask = NewTask;
		for (unsigned int Iter = 0; Iter < MAX_CHILDREN; Iter++)
		{
			Children[Iter] = 0;
		}
		ChildCount = 0;
		ParentNode = 0;
		Name = BehaviorName;
	}

	bool Execute(TinyBehavior* Behavior, double DeltaTime)
	{
		if (CurrentTask(Behavior, DeltaTime))
		{
			for (unsigned int Iter = 0; Iter < ChildCount; Iter++)
			{
				return Children[Iter]->Execute(Children[Iter], DeltaTime);
			}
		}
		return false;
	}

	TinyBehavior* AddChild(const char* BehaviorName, TinyBehavior* Parent, Task NewTask)
	{
		//pretty much the same as new
		TinyBehavior* NewBehavior = (TinyBehavior*)malloc(sizeof(NewBehavior));
		*NewBehavior = TinyBehavior(BehaviorName, NewTask);
		Children[ChildCount] = NewBehavior;
		Children[ChildCount]->ParentNode = Parent;
		ChildCount++;
		return Parent;
	}

	void RemoveChildByIndex(unsigned int BehaviorIndex)
	{
		if (BehaviorIndex >= 0 && BehaviorIndex < MAX_CHILDREN)
		{
			Children[BehaviorIndex] = NULL;
			ChildCount--;
		}
	}
	
	void RemoveChildByName(const char* BehaviorName)
	{
		if (BehaviorName != NULL)
		{
			for (unsigned int Iter = 0; Iter < MAX_CHILDREN; Iter++)
			{
				if (!strcmp(BehaviorName, Children[Iter]->Name))
				{
					Children[Iter] = NULL;
					ChildCount--;
					break;
				}
			}
		}
	}

	Task CurrentTask;
	TinyBehavior* ParentNode;
	TinyBehavior* Children[MAX_CHILDREN];
	unsigned int ChildCount;
	const char* Name;
};
#endif