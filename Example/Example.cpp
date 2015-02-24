#include <stdio.h>
#include <TinyBehaviors.h>

bool ExampleTask(TinyBehavior* Behavior, double DeltaTime)
{
	printf("%i\n", Behavior->ChildCount);
	return true;
}

bool Example2Task(TinyBehavior* Behavior, double DeltaTime)
{
	printf("blarg\n");
	return true;
}

int main()
{
	TinyBehavior Behavior(ExampleTask);
	Behavior.AddChild(&Behavior, Example2Task);

	if (Behavior.Execute(&Behavior, 0))
	{
		//do something
	}

	return 0;

}