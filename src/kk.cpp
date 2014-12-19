#include <SDL.h>
#include<SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {

	string font = "font";
	TTF_Font* ttffont = TTF_OpenFont(font.c_str(), 18);
	
	IMG_Load(font.c_str());

	SDL_Quit();
}

