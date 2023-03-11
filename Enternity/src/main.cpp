#include "Application/Application.h"


#include "Core/Math/Vector.h"
void Test()
{
	using namespace Enternity;
	Vector2f vec(1, 2);
	Vector2f vec2(3, 4);



	int i = 0;
	i++;
}

int main(int argc, const char** argv) {

	Test();

	Enternity::Application app;

	app.Initialize(1200, 800, "hahaha");
	app.Run();
	app.Finalize();
	
	return 0;
}


