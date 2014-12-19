#ifndef SDLBUTTON_H
#define SDLBUTTON_H

#include <SDL.h>
#include<string>

#include"SDLScene.h"
#include "Command.h"

using namespace std;

const int	 	ACTIVE_STATE 	= 0;
const int		DEACTIVE_STATE 	= 2;
const int		DOWN_STATE 		= 4;	

class SDLButton {
	
	private:
	
		string 			imageOn;
		string			imageOff;
		string 			imageDown;
		SDLScene*		scene;
		SDL_Surface* 	buttonSurface;
		SDL_Rect 		buttonLocation;
		int				state;
		//Text
		TTF_Font*		txtfont;
		SDL_Surface*	textSurface;
		SDL_Rect		textLocation;
		SDL_Color		txtColor;
	
		string 			text;
		Command*		command;
	
		void swapImage();
		
	public:
		SDLButton(SDLScene* scene,
					string imageOn, string imageOff, string imageDown,
					int xpos, int ypos);
		SDLButton(SDLScene* scene,
					string imageOn, string imageOff, string imageDown,
					string text,string font,
					int xpos, int ypos, int size);
		void addActionListener(Command* c);
		int getX();
		int getY();
		int getW();
		int getH();
		void activate();
		void deactivate();
		void click();
		void down();
		void up();
};

#endif
