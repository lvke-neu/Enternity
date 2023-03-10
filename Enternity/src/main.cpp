#include "Application/Application.h"

int main(int argc, const char** argv) {

	Enternity::Application app;

	app.Initialize(1200, 800, "hahaha");
	app.Run();
	app.Finalize();
	
	return 0;
}


