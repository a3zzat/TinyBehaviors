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
	TinyBehavior Behavior("Example", ExampleTask);
	Behavior.AddChild("Example2", &Behavior, Example2Task);

	if (Behavior.Execute(&Behavior, 0))
	{
		//do something
	}

	Behavior.RemoveChildByIndex(0);

	return 0;

}