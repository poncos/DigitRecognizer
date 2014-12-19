#include "MNeuralNetwork.h"

#include <sstream>

MNeuralNetwork::MNeuralNetwork(
			MatlabSession* session,
			string aVarName) {
	itsSession = session;
	itsVarName = aVarName;
}

MNeuralNetwork* MNeuralNetwork::createCustomNetwork(
			MatlabSession* session,
			int numInputs,
			int numLayers,
			string biasConnect,
			string inputConnect,
			string layerConnect,
			string outputConnect,
			string targetConnect) {
		
	string aVarName = session->generateRandomName();
	stringstream matlabCommand;
	matlabCommand << aVarName << " = network(" << numInputs <<"," << numLayers;
	string strParams[5] = {
		biasConnect, inputConnect, layerConnect, outputConnect, targetConnect};
	string params = validateStringParams(strParams, 5);
	if(params != "") matlabCommand << ",";
	matlabCommand << params << ")";

	cout << "Command: " << matlabCommand.str() << endl;
	session->execute(matlabCommand.str());

	return new MNeuralNetwork(session, aVarName);
}

MNeuralNetwork* MNeuralNetwork::createNewP(
			MatlabSession* session,
			string PR, int S, string TF, string LF) {

}

MNeuralNetwork* MNeuralNetwork::createNewFF(
		MatlabSession* session,
					string P, string T,
					string S, string TF,
					string BTF, string BLF, string PF,
					string IPF, string OPF, string DDF) {

		string aVarName = session->generateRandomName();
		stringstream matlabCommand;
		matlabCommand << aVarName << " = newff(";
		string strParams[10] = {
			P,T,S,TF,BTF,BLF,PF,IPF,OPF,DDF
		};
		string params = validateStringParams(strParams,10);
		matlabCommand << params << ")";

		cout << "Command: " << matlabCommand.str() << endl;
		session->execute(matlabCommand.str());

		return new MNeuralNetwork(session, aVarName);
}

MNeuralNetwork* MNeuralNetwork::createNewFFvR7(
			MatlabSession* session,
			string aVarName,
			string PR, string S, string TF, string BTF,
			string BLF, string PF) {

}

string MNeuralNetwork::getName() {
	return itsVarName;
}

int MNeuralNetwork::getNumLayers() {
	int result = -1;
	string rname = itsSession->generateRandomName();
	stringstream tmpCommand;
	tmpCommand << rname << "= " << itsVarName << ".numLayers";

	itsSession->execute(tmpCommand.str());	
	result =  itsSession->getVarInteger(rname);
	//TODO free matlab variable
	return result;
}

int MNeuralNetwork::getNumInputs() {
	int result = -1;
	string rname = itsSession->generateRandomName();
	stringstream tmpCommand;
	tmpCommand << rname << "= " << itsVarName << ".numInputs";

	itsSession->execute(tmpCommand.str());
	result = itsSession->getVarInteger(rname);
	//TODO free matlab variable
	return result;
}

int MNeuralNetwork::getNumOutputs() {
	int result = -1;
	string rname = itsSession->generateRandomName();
	stringstream tmpCommand;
	tmpCommand << rname << "= " << itsVarName << ".numOutputs";

	itsSession->execute(tmpCommand.str());
	result = itsSession->getVarInteger(rname);
	//TODO free matlab variable
	return result;
}

/////\\//\\//\\//\\//\\//\\//\\//\\\\\\\\\\\\\\\\\\
/////\\//\\// OPERATON METHODS
/////\\//\\//\\//\\//\\//\\//\\//\\\\\\\\\\\\\\\\\\

void MNeuralNetwork::execTrain() {

	stringstream command;
	command << "[" << itsVarName << "tr,Y,E,Pf,Af]"
			<< "=train(" << itsVarName << ",P,T,Pi,Ai,VV,TV)";

// Entrenamiento ([net, tr, Y, E, Pf, Af] = train(net, P, T, Pi, Ai, VV, TV);):
}

void MNeuralNetwork::execSim() {

//Simulación ([Y, Pf, Af, E, perf] = sim(net, P, Pi, Ai, T)):
}

void MNeuralNetwork::execInit() {
	stringstream aCommand;
	aCommand << itsVarName << "=init("<< itsVarName << ")";

	itsSession->execute(aCommand.str());
}

string MNeuralNetwork::validateStringParams(string* params, int length) {
	bool nullParam = false;
	stringstream command;
	string item = "";
	string result;

	for(int i=0;i<length;i++) {
		item = params[i];

		if( item != "")
			command << item << ","; 
		else
			break;
	}
	string str = command.str();
	result = str.substr(0, str.length()-1);

	return result;
}
