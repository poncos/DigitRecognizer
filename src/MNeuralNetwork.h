#ifndef MNEURALNETWORK_H_
#define MNEURALNETWORK_H_

#include<string>

#include "MatlabSession.h"

using namespace std;

class MNeuralNetwork {

	private:
		MatlabSession* 	itsSession;
		string			itsVarName;

		static string validateStringParams(
			string* params, int length);
		
	protected:
		MNeuralNetwork(
					MatlabSession* session,
					string varName);
	public:
		~MNeuralNetwork();
		static MNeuralNetwork* createCustomNetwork(
					MatlabSession* session,
					int numInputs,
					int numLayers,
					string biasConnect,
					string inputConnect,
					string layerConnect,
					string outputConnect,
					string targetConnect
					);
		static MNeuralNetwork* createNewP(
					MatlabSession* session,	
					string PR, int S, string TF, string LF);
		static MNeuralNetwork* createNewFF(
					MatlabSession* session,
					string P, string T,
					string S, string TF,
					string BTF, string BLF, string PF,
					string IPF, string OPF, string DDF);

		static MNeuralNetwork* createNewFFvR7(
					MatlabSession* session,
					string aVarName,
					string PR, string S, string TF, string BTF,
					string BLF, string PF);
		string getName();
		int getNumLayers();
		int getNumInputs();
		int getNumOutputs();
		void execInit();
		void execTrain();
		void execSim();
};

#endif
