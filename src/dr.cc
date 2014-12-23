#include <SDL.h>


#include <iostream>
#include <string>
#include <sstream>

#include "SDLScene.h"
#include "MatlabSession.h"
#include "MNeuralNetwork.h"

using namespace std;

void eventHandler();
bool keyboardEventHandler(SDL_Event e);
void mouseMotionEventHandler(SDL_Event e);
void mouseButtonPressEventHandler(SDL_Event event);
void preprocessImage();
void processData();
void processResult();
bool insideTable(SDL_Rect* zone, int x, int y);
int isAnyPoint(int x1, int y1, int x2, int y2);


bool 	paintMode = false;
SDLScene* scene;
SDL_Rect paintZone = {30, 35, 336, 420}; 
SDL_Color frg = {0,0,0};
int xminDrawed = -1;
int xmaxDrawed = -1;
int yminDrawed = -1;
int ymaxDrawed = -1;

int dataset[15];
MatlabSession* ms;
MNeuralNetwork* neff;

int main(int argc, char* argv[]) {

	ms = MatlabSession::createSession();

	//ms->execute("load /home/colladox/projects/c++/digitrecognized/resources/matlab_digitpatternt.txt");
	//ms->execute("load /home/colladox/projects/c++/digitrecognized/resources/matlab_digittargets.txt");
	ms->execute("load ./resources/matlab_digitpatternt.txt");
	ms->execute("load ./resources/matlab_digittargets.txt");
	ms->execute("P = matlab_digitpatternt'");
	ms->execute("T = matlab_digittargets'");

	neff = MNeuralNetwork::createNewFF(
				ms, "P","T","20","","","","","","","");
	
	//cout << "NumInputs: " << neff->getNumInputs() << endl;
	//cout << "NumLayers: " << neff->getNumLayers() << endl;
	//cout << "NumOutputs: " << neff->getNumOutputs() << endl;

	cout << "XX" << endl;

	stringstream command;
	command << neff->getName() <<"=train(" << neff->getName() << ",P,T)";
	cout << "Train command: " << command.str() << endl;
	ms->execute(command.str());
	command.str("");

	scene = new SDLScene("Digit Recognize v0.01", 500,800);

	scene->show();

	scene->setBackground("resources/numberrecognized_bck.png");

	SDL_Flip(scene->getScreen());

	eventHandler();

	SDL_Quit();

	ms->closeSession();
}

void eventHandler() {
	bool quit = false;
	SDL_Event event;

	do {
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					quit = keyboardEventHandler(event);
					break;
				case SDL_MOUSEMOTION:
					mouseMotionEventHandler(event);
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouseButtonPressEventHandler(event);
					break;
				case SDL_MOUSEBUTTONUP:
					mouseButtonPressEventHandler(event);
					break;
			}
		}
		SDL_Flip(scene->getScreen());
		SDL_Delay(50);
	} while(!quit);
}

bool keyboardEventHandler(SDL_Event e) {
	bool quit = false;

	switch(e.key.keysym.sym) {
		case SDLK_f:
			SDL_WM_ToggleFullScreen(scene->getScreen());
			break;
		case SDLK_q:
			quit = true;
			break;
		default:
		break;
	}

	return quit;
}

bool insideTable(SDL_Rect* zone, int x, int y) {
	if(	x > zone->x && x < zone->x+zone->w &&
		y > zone->y && y < zone->y+zone->h)
		return true;
	return false;
}

void mouseMotionEventHandler(SDL_Event e) {

	int xmouse = e.motion.x;
	int ymouse = e.motion.y;
	
	if(	paintMode && insideTable(&paintZone, xmouse, ymouse)) {
		scene->putPixel(xmouse,ymouse,0,0,0,6);
		if(xmouse < xminDrawed) xminDrawed = xmouse;
		if(xmouse > xmaxDrawed) xmaxDrawed = xmouse;
		if(ymouse < yminDrawed) yminDrawed = ymouse;
		if(ymouse > ymaxDrawed) ymaxDrawed = ymouse;
	}
}

void mouseButtonPressEventHandler(SDL_Event event) {
	int xmouse = event.button.x;
	int ymouse = event.button.y;

	switch (event.button.type) {
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT) {
				if(	insideTable(&paintZone, xmouse, ymouse)) {	
					paintMode = true;
					scene->putPixel(xmouse,ymouse, 0,0,0,6);
					xminDrawed = xmouse; xmaxDrawed = xmouse;
					yminDrawed = ymouse; ymaxDrawed = ymouse;
					cout << "P: " << xmouse << "," << ymouse << endl;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT) {
				paintMode = false;
				preprocessImage();
				processData();
				scene->clearRec(&paintZone, 255,255,255);
			}
			break;
		
	}
}

void preprocessImage() {
	cout << "preprocessImage()" << endl;
	cout << "DrawedZone: " << endl;
	cout << "X: " << xminDrawed << "," << xmaxDrawed << endl;
	cout << "Y: " << yminDrawed << "," << ymaxDrawed << endl;

	int xsegmentsize = (xmaxDrawed-xminDrawed)/3;
	int ysegmentsize = (ymaxDrawed-yminDrawed)/5;	

	cout << "Output Vector: " << endl;
	int dsp = 0;
	for(int j=0;j<5;j++) {
		for(int i=0;i<3;i++) {	
			int x1 = xsegmentsize * i + xminDrawed;
			int y1 = ysegmentsize * j + yminDrawed;
			dataset[dsp++] = isAnyPoint(x1, y1, x1+xsegmentsize, y1+ysegmentsize);
			cout << dataset[dsp-1] << ";";
		}
	}
	cout << endl;
}

void processData() {
	cout << "processData()" << endl;
	int n;

	stringstream command;
	command << "[Y, Pf, Af, E, perf] = sim("<< neff->getName() << ",[";
	for(int i=0;i<15;i++) {
		command << dataset[i];
		if(i<14) command << ";";
	}
	command << "]);";
	cout << "Sim command: " << command.str() << endl;
	ms->execute(command.str());
	double* arrayResult =
	ms->getDoubleArray("Y",&n);
	cout << "ArrayResult: ";
	double minDiff = 100000;
	int selectedOutput = -1;
	for(int i=0;i<n;i++) {
		cout << arrayResult[i] << ",";
		double diff = 1-arrayResult[i];
		if(diff < 0) diff = -diff;

		if(diff < minDiff) {
			minDiff = diff;
			selectedOutput = i;
		}
	}

	SDL_Rect rec = {480,50,200,200};
	scene->clearRec(&rec, 255,255,255);
	
	cout << endl << "Number Writed: " << selectedOutput << endl;
	command.str("");
	command << selectedOutput;
	scene->drawString(command.str(),"fonts/Arial/arialbd.ttf", 250, &frg, 520 , 10 );
	cout << endl;
}

void processResult() {
	cout << "processResult()" << endl;

}

int isAnyPoint(int x1, int y1, int x2, int y2) {
	SDL_Color c;
	Uint8 r,g,b;

	for(int i=x1;i<x2;i++) {
		for(int j=y1;j<y2;j++) {
			scene->getPixel(i,j,&r,&g,&b);	
			if(r != 255 || g!= 255 || b != 255)	
				return 1;
		}
	}
	return 0;
}






