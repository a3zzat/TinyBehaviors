#ifndef TINY_BEHAVIORS_H
#define TINY_BEHAVIORS_H
#define MAX_CHILDREN 10
#include <stdlib.h>

struct TinyBehavior;

//Task type definition
typedef bool (*Task)(TinyBehavior*, double);

struct TinyBehavior
{
	TinyBehavior()
	{
		ChildCount = 0;
		CurrentTask = 0;
		for (unsigned int Iter = 0; Iter < MAX_CHILDREN; Iter++)
		{
			Children[Iter] = 0;
		}
		ChildCount = 0;
		ParentNode = 0;
	}
	TinyBehavior(Task NewTask)
	{
		CurrentTask = NewTask;
		for (unsigned int Iter = 0; Iter < MAX_CHILDREN; Iter++)
		{
			Children[Iter] = 0;
		}
		ChildCount = 0;
		ParentNode = 0;
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

	TinyBehavior* AddChild(TinyBehavior* Parent, Task NewTask)
	{
		//pretty much the same as new
		TinyBehavior* NewBehavior = (TinyBehavior*)malloc(sizeof(NewBehavior));
		*NewBehavior = TinyBehavior(NewTask);
		Children[ChildCount] = NewBehavior;
		Children[ChildCount]->ParentNode = Parent;
		ChildCount++;
		return Parent;
	}

	Task CurrentTask;
	TinyBehavior* ParentNode;
	TinyBehavior* Children[MAX_CHILDREN];
	unsigned int ChildCount;
};


#endif
