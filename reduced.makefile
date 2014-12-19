#BUILD of tiffviewer

#before run first time do
# export LD_LIBRARY_PATH=/usr/local/matlabR2008a/bin/glnxa64/:/usr/local/matlabR2008a/sys/os/glnxa64/:/usr/local/matlabR2008a/bin/glnxa64/:/usr/local/matlabR2008a/sys/os/glnxa64/:
#export LD_LIBRARY_PATH=/usr/local/MATLAB/R2014a/bin/glnxa64/:/usr/local/MATLAB/R2014a/sys/os/glnxa64/:/usr/local/MATLAB/R2014a/bin/glnxa64/

#sudo apt-get install libsdl1.2-dev
#sudo apt-get install libsdl-ttf2.0-dev
#sudo apt-get install libsdl-image1.2-dev

#directories
SRC_DIR = ./src
BIN_DIR = ./bin
#matlab directories
MATLAB_DIR = /usr/local/MATLAB/R2014a


#variables
CFLAGS = -I$(SRC_DIR)
SDL_FLAGS = `sdl-config --libs --cflags` -lX11 -lSDL_image -lSDL_ttf
MATLAB_FLAGS = -I$(MATLAB_DIR)/extern/include/ -L$(MATLAB_DIR)/bin/glnxa64/ -leng -lmx
SRC = $(SRC_DIR)/MatlabSession.cc $(SRC_DIR)/MNeuralNetwork.cc $(SRC_DIR)/dr.cc $(SRC_DIR)/SDLScene.cc $(SRC_DIR)/SDLButton.cc 
OBJ = $(BIN_DIR)/MatlabSession.o $(BIN_DIR)/MNeuralNetwork.o $(BIN_DIR)/dr.o $(BIN_DIR)/SDLScene.o $(BIN_DIR)/SDLButton.o 
BIN = $(BIN_DIR)/dr

#rules
compile: $(OBJ)
	g++ $(SDL_FLAGS) $(CFLAGS) $(MATLAB_FLAGS) -o $(BIN) $(OBJ)

$(BIN_DIR)/dr.o: $(SRC_DIR)/dr.cc
	g++ -c $(SDL_FLAGS) $(CFLAGS) $(MATLAB_FLAGS) $(SRC_DIR)/dr.cc -o $(BIN_DIR)/dr.o

$(BIN_DIR)/SDLScene.o: $(SRC_DIR)/SDLScene.cc
	g++ -c $(CFLAGS) $(SRC_DIR)/SDLScene.cc $(SDL_FLAGS) -o $(BIN_DIR)/SDLScene.o

$(BIN_DIR)/SDLButton.o: $(SRC_DIR)/SDLButton.cc
	g++ -c $(CFLAGS) $(SRC_DIR)/SDLButton.cc $(SDL_FLAGS) -o $(BIN_DIR)/SDLButton.o

$(BIN_DIR)/MatlabSession.o: $(SRC_DIR)/MatlabSession.cc
	g++ -c $(CFLAGS) $(SRC_DIR)/MatlabSession.cc $(MATLAB_FLAGS) -o $(BIN_DIR)/MatlabSession.o

$(BIN_DIR)/MNeuralNetwork.o: $(SRC_DIR)/MNeuralNetwork.cc
	g++ -c $(CFLAGS) $(SRC_DIR)/MNeuralNetwork.cc $(MATLAB_FLAGS) -o $(BIN_DIR)/MNeuralNetwork.o
