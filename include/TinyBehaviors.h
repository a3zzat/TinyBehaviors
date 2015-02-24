#ifndef TINY_BEHAVIORS_H
#define TINY_BEHAVIORS_H
#include <string.h>
#include <stdlib.h>
#define MAX_CHILDREN 10

struct TinyBehavior;
struct TinyBlackboard;

//Task type definition
typedef bool (*Task)(TinyBehavior*);

struct TinyBehavior
{
	TinyBehavior(Task NewTask)
	{
		CurrentTask = NewTask;
		Children = {0};
	}

	Task CurrentTask; 

	TinyBehavior* Parent;
	TinyBehavior* Children[MAX_CHILDREN];
	unsigned int ChildCount;

	bool Execute(TinyBehavior* Behavior)
	{
		if(CurrentTask(Behavior))
		{
			for(unsigned int Iter = 0; Iter < ChildCount; Iter++)
			{
				return Children[Iter]->Execute(Children[Iter]);
			}
		}

		return false;
	}

	TinyBehavior* AddChild(TinyBehavior* Parent, Task NewTask)
	{
		*Children[ChildCount] = TinyBehavior::TinyBehavior(NewTask);
		Children[ChildCount]->Parent = Parent;
		ChildCount++;
		return Parent;
	}
};

#endif
