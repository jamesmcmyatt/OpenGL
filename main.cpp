#include "Game.h"

int main()
{
	//game title, window width, window height, OpenGL version Maajor, OpenGL version minor, resizable(false)
	//if openGL 4,6 doesnt work use 3,3
	
	Game game("FOGGS", 1920, 1080, 4, 4, false);
	while (!game.getWindowShouldClose())
	{
		//update input and render
		game.update();
		game.render();
	}
	return 0;
}

