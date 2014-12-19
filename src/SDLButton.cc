#include "SDLButton.h"

#include<SDL_image.h>
#include<iostream>

using namespace std;

SDLButton::SDLButton(
		SDLScene* scene,
		string imageOn,
		string imageOff,
		string imageDown,
		int xpos, int ypos) {
	this->state = DEACTIVE_STATE;
	this->imageOn = imageOn;
	this->imageOff = imageOff;
	this->imageDown = imageDown;
	this->scene = scene;
	buttonSurface = IMG_Load(imageOff.c_str());
	buttonLocation.x = xpos;
	buttonLocation.y = ypos;
			
	SDL_BlitSurface(buttonSurface,NULL,scene->getScreen(), &buttonLocation);
	SDL_FreeSurface(buttonSurface);
}

SDLButton::SDLButton(
		SDLScene* scene,
		string imageOn,
		string imageOff,
		string imageDown,
		string text,
		string font,
		int xpos, int ypos,
		int size) {
	this->state = DEACTIVE_STATE;
	this->imageOn = imageOn;
	this->imageOff = imageOff;
	this->imageDown = imageDown;
	this->text = text;
	this->scene = scene;
	buttonSurface = IMG_Load(imageOff.c_str());
	buttonLocation.x = xpos;
	buttonLocation.y = ypos;
	buttonLocation.w = buttonSurface->w;
	buttonLocation.h = buttonSurface->h;
			
	//TEXT
	txtfont = TTF_OpenFont(font.c_str(),size);
	if(!txtfont)
		cerr << "Error opening font: " << TTF_GetError() << endl;
	txtColor.r = 255; txtColor.g = 255; txtColor.b = 255;
	textSurface = TTF_RenderText_Blended( txtfont, text.c_str(), txtColor );
	if(!textSurface)
		cerr << "Error rendering text: " << TTF_GetError() << endl;
	
	textLocation.w = textSurface->w;
	textLocation.h = textSurface->h;
	//int dsp = buttonLocation.x + buttonLocation.w - xpos - textSurface->w;
	textLocation.x = xpos + buttonLocation.w - textLocation.w - 5;
	textLocation.y = ypos+5;
	
	SDL_BlitSurface(buttonSurface,NULL,scene->getScreen(), &buttonLocation);
	SDL_BlitSurface(textSurface,NULL,scene->getScreen(),&textLocation);
	SDL_FreeSurface(buttonSurface);
}

void SDLButton::addActionListener(Command* c) {
	this->command = c;
}

int SDLButton::getX() {
	return buttonLocation.x;	
}

int SDLButton::getY(){
	return buttonLocation.y;
}

int SDLButton::getW() {
	return buttonLocation.w;
}

int SDLButton::getH() {
	return buttonLocation.h;
}

void SDLButton::activate() {
	if(state != ACTIVE_STATE && state != DOWN_STATE) {
		state = ACTIVE_STATE;
		swapImage();
	}
}

void SDLButton::deactivate() {
	if(state == DEACTIVE_STATE)
		return;
	state = DEACTIVE_STATE;
	swapImage();
}

void SDLButton::click() {	
	if(command) {
		command->execute();
	}
}

void SDLButton::down() {
	if(state != DOWN_STATE) {
		state = DOWN_STATE;
		swapImage();
	}
}

void SDLButton::up() {
	if(state != ACTIVE_STATE) {
		state = ACTIVE_STATE;
		swapImage();
		click();
	}
}

void SDLButton::swapImage() {
	if(state == ACTIVE_STATE) {
		buttonSurface = IMG_Load(imageOn.c_str());
	}
	else {
		if(state == DEACTIVE_STATE) {
			buttonSurface = IMG_Load(imageOff.c_str());
		} else {
			if(state == DOWN_STATE) {
				buttonSurface = IMG_Load(imageDown.c_str());
			}
		}
	}
	SDL_BlitSurface(buttonSurface,NULL,scene->getScreen(), &buttonLocation);
	if(textSurface)
		SDL_BlitSurface(textSurface,NULL,scene->getScreen(), &textLocation);
	SDL_FreeSurface(buttonSurface);
}
