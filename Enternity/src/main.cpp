#include <iostream>
#include "Engine/Engine.h"

int main()
{	
	if (Enternity::Engine::GetInstance().Initialize())
	{
		Enternity::Engine::GetInstance().Run();
	}

	return 0;
}