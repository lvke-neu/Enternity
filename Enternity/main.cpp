#include "Application/Application.h"
#include <stdio.h>

using namespace Enternity;

int main(int argc, const char** argv) {

	Application app;

	if (!app.Initialize())
	{
		printf("Application Initialize Failed");
		return 0;
	}
	app.Run();
	app.Finalize();
	
	return 0;
}

