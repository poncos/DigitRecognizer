#include "SDLScene.h"

#include <SDL_image.h>
#include<SDL_ttf.h>

SDLScene::SDLScene(string title, int height, int width) {
	this->width = width;
	this->height = height;
	this->title = title;	
}

void SDLScene::setBackground(string image) {
	bckImage = IMG_Load(image.c_str());

	if(!bckImage) {
		cerr << "Error loading image: " << image << endl; 
	}		
	bckLocation.x = 0;
	bckLocation.y = 0;
	SDL_BlitSurface(bckImage, NULL, screen, &bckLocation);
	SDL_FreeSurface(bckImage);
}

void SDLScene::show() {
	initGraphMode();
	
	if(TTF_Init()<0) {
		cerr << "Errir initializing TTF" << endl;	
	}
}

SDL_Surface* SDLScene::getScreen() {
	return screen;
}

void SDLScene::drawString(
	string text, string font, int size,SDL_Color* color, int x, int y) {
	TTF_Font* ttffont = TTF_OpenFont(font.c_str(), size);
	SDL_Surface* textSurface;
	SDL_Rect textLocation;

	if(!ttffont)
		cerr << "Error opening font: " << TTF_GetError() << endl;
	textSurface = TTF_RenderText_Blended( ttffont, text.c_str(), *color);
	if(!textSurface)
		cerr << "Error rendering text: " << TTF_GetError() << endl;
	textLocation.x = x;
	textLocation.y = y;
	textLocation.w = textSurface->w;
	textLocation.h = textSurface->h;

	//cout << "Surface size: " << textLocation.w << "x" << textLocation.h << endl;
	SDL_BlitSurface(textSurface,NULL,screen,&textLocation);
	SDL_FreeSurface(textSurface);
	free(ttffont);
}

void SDLScene::initGraphMode() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)                                                		
	{
		cout << "Error inittializaing SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	
	screen = SDL_SetVideoMode(width,height,DEPTH,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen == NULL)
	{
		cout << "Error stablishing video mode: " << SDL_GetError() << endl;
	}

	SDL_WM_SetCaption(title.c_str(),NULL);
}

void SDLScene::putPixel(int x,int y,int r,int g,int b) {
	
	lock();
	//bloqueamos la superficie
	Uint32 color;
	Uint8* buffer;
	
	if (screen != NULL)
	{
		color= SDL_MapRGB(screen->format,r,g,b);
		buffer = (Uint8*)screen->pixels + y * screen->pitch + screen->format->BytesPerPixel * x;	
		memcpy(buffer,&color,screen->format->BytesPerPixel);
	}
	//desbloqueamos la superficie
	unlock();
}

void SDLScene::getPixel(int x, int y, Uint8* r, Uint8* g, Uint8* b) {
	int bpp = screen->format->BytesPerPixel;

	Uint32 pcolor;
	lock();	
	Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
	memcpy(&pcolor, p,bpp);	

	SDL_GetRGB(pcolor, screen->format, r,g,b);

	unlock();
}

void SDLScene::putPixel(int x, int y, int r, int g, int b, int size) {
	lock();
	//bloqueamos la superficie
	Uint32 color;
	Uint8* buffer;
	int l = size/2;
	int _x=x-l,_y=y-l;
	
	if (screen != NULL)
	{
		color= SDL_MapRGB(screen->format,r,g,b);
		for(int i=0;i<size;i++,_x++) {
			_y=y-l;
			for(int j=0;j<size;j++,_y++) {
				buffer = (Uint8*)screen->pixels + _y * screen->pitch + screen->format->BytesPerPixel * _x;	
				memcpy(buffer,&color,screen->format->BytesPerPixel);
			}
		}
	}
	//desbloqueamos la superficie
	unlock();
}

void SDLScene::clearRec(SDL_Rect* rec, SDL_Color* color) {
	SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, color->r, color->g, color->b));
}

void SDLScene::clearRec(SDL_Rect* rec, Uint8 r, Uint8 g, Uint8 b) {
	SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, r, g, b));
}

void SDLScene::lock() {
	
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
}

void SDLScene::unlock() {
	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);
}
