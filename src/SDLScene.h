#ifndef SDLSCENE_H
#define SDLSCENE_H


#include<SDL.h>
#include<SDL_ttf.h>

#include<iostream>
#include<string>

using namespace std;

#define DEPTH 16
#define TITLE "Tiff viewer 0.01"

class SDLScene {
	
	private:
		SDL_Surface* screen;
		SDL_Surface* bckImage;
		SDL_Rect	 bckLocation;
		SDL_Color 	 frgColor;
		SDL_Color	 fillColor;
		
	
		int height;
		int width;
		string title;
	
		void initGraphMode();
		void lock();
		void unlock();
	
	public:
		SDLScene(string title, int width, int height);
		void setBackground(string image);
		void show();
		void putPixel(int x,int y,int r,int g,int b);
		void putPixel(int x, int y, int r, int g, int b, int size);
		void getPixel(int x, int y, Uint8* r, Uint8* g, Uint8* b);
		SDL_Surface* getScreen();
		void drawString(
			string text, string font, int size,
			SDL_Color* color, int x, int y);
		void clearRec(SDL_Rect* rec, SDL_Color* color);
		void clearRec(SDL_Rect* rec, Uint8 r, Uint8 g, Uint8 b);
	
};

#endif
