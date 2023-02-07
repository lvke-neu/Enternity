#include "Engine/Core/Debug/ExecutionTimer.h"

using namespace Enternity;
int main()
{
	Log::Init();

	{
		ExecutionTimer execTimer;

		
		for (int i = 0; i < 1000000; i++)
		{
			int count = 0;
			for (int j = 0; j < 1001; j++)
				count += j;
		}
	}
	

	while (true);
	return 0;
}