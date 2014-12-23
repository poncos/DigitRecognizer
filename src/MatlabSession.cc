#include "MatlabSession.h"

#include "engine.h"
#include "matrix.h"
#include "mex.h"

#include <sstream>
#include <stdio.h>
#include <string.h>


#define RANDOM_VARNAME_LENGTH 25

using namespace std;

MatlabSession* MatlabSession::instance = 0;

MatlabSession::MatlabSession() {
	if( !(ep = engOpen("\0"))) {
		cerr << "Error creating session" << endl;
		exit(1);
	}
}

MatlabSession::~MatlabSession() {

}

/////\\//\\//\\/// SESSION MANAGEMENT
MatlabSession* MatlabSession::createSession() {

	if(instance == 0)
		instance = new MatlabSession();

	return instance; 
}

void MatlabSession::closeSession() {
	engClose(ep);
}

MatlabSession*  MatlabSession::loadSession(string aFileName) {

}

void MatlabSession::storeSession(string aFileName) {

}

/////\\//\\//\\///COMMAND EXECUTION
void MatlabSession::execute(string aCommand) {
	int result = engEvalString(ep, aCommand.c_str() );
}

/////\\//\\//\\///WINDOW MANAGEMENT
void MatlabSession::showWindow() {
	engSetVisible(ep, 1);
}

void MatlabSession::hideWindow() {
	engSetVisible(ep, 0);
}

/////\\//\\//\\///STRING VARIABLES
void MatlabSession::setVarString(string aVarName, string aValue) {
	mxArray *T = NULL;

	T = mxCreateString(aValue.c_str());
	engPutVariable(ep, aVarName.c_str(), T);

	mxDestroyArray(T);

}

string MatlabSession::getVarString(string aVarname) {
	mxArray *T 			= NULL;
	int 	strlen;
	string 	strResult;
	char 	*str;

	T = engGetVariable(ep, aVarname.c_str());

	if (T) {
		if(mxGetClassID(T) == mxCHAR_CLASS) {
			//cout << "Dimensions: " << mxGetNumberOfDimensions(T) << endl;
			//cout << "Sizes: " << mxGetN(T) << "x" << mxGetM(T) << endl;

			strlen = mxGetN(T)*sizeof(mxChar)+1;
			str = (char *)mxMalloc(strlen);
			if(!mxGetString(T, str, strlen)) {
				strResult.assign(str);
			}
		}

		mxDestroyArray(T);
	}
	return strResult;
}

void MatlabSession::setVarInteger(string aVarName, int aValue ) {
	mxArray *T = NULL;

	T = mxCreateDoubleScalar(aValue);
	engPutVariable(ep, aVarName.c_str(), T);

	mxDestroyArray(T);
}

int MatlabSession::getVarInteger(string aVarName) {
	mxArray *T = NULL;
	int result = -1;

cout << "getVarInteger " << aVarName.c_str() << endl;
	T = engGetVariable(ep, aVarName.c_str());

	cout << "reading variable: " <<  aVarName << endl;
	if(T) {
		if(mxGetClassID(T) == mxDOUBLE_CLASS) {
			cout << "variable type is correct" << endl;
			result = (int)*(double*)mxGetPr(T);
		}
		mxDestroyArray(T);	
	}

	return result;
}

double MatlabSession::getVarDouble(string aVarName) {
	mxArray *T = NULL;
	double result = -1;

	T = engGetVariable(ep, aVarName.c_str());

	if(T) {
		if(mxGetClassID(T) == mxDOUBLE_CLASS) {
			result = *(double*)mxGetPr(T);
		}
		mxDestroyArray(T);
	}

	return result;
}

void MatlabSession::setVarDouble(string aVarName, double aValue) {
	mxArray *T = NULL;

	T = mxCreateDoubleScalar(aValue);
	engPutVariable(ep, aVarName.c_str(), T);

	mxDestroyArray(T);
}

void MatlabSession::createIntegerArray(string aVarName, int* anArray, int length) {
	mxArray *T = NULL;	

	T = mxCreateNumericMatrix(1, length, mxINT32_CLASS, mxREAL);
	memcpy((void *)mxGetPr(T), (void *) anArray, sizeof(int)*length);

	if(engPutVariable(ep, aVarName.c_str(), T))
		cerr << "Error creating integer array" << endl;
	mxDestroyArray(T);
}

void MatlabSession::createDoubleArray(string aVarName, double* anArray, int length) {
	mxArray *T = NULL;

	T = mxCreateDoubleMatrix(1, length, mxREAL);
	memcpy((void *)mxGetPr(T), (void *)anArray, sizeof(double)*length);

	if(engPutVariable(ep, aVarName.c_str(), T)) {
		cerr << "Error creating double array: " << endl;
	}
	
	mxDestroyArray(T);
}

int* MatlabSession::getIntegerArray(string aVarName, int* arrayLength) {
	mxArray *T = NULL;
	int* result = NULL;
	int n=-1,m=-1;

	T = engGetVariable(ep, aVarName.c_str());

	if(T) {
		if(mxGetClassID(T) == mxINT32_CLASS) {
			m = mxGetM(T);
			
			if(m == 1) {
				n = mxGetN(T);
				result = new int[n];
				memcpy((void *)result, (void *)mxGetPr(T), sizeof(int)*n);
			}
		}
		mxDestroyArray(T);
	}

	*arrayLength = n;
	return result;
}

double* MatlabSession::getDoubleArray(string aVarName, int* array) {
	mxArray *T = NULL;
	double* result = NULL;
	int n=-1,m=-1;

	T = engGetVariable(ep, aVarName.c_str());

	if(T) {
		if(mxGetClassID(T) == mxDOUBLE_CLASS) {
			m = mxGetM(T);	
			n = mxGetN(T);
			cout << "m: " << m << endl;	
			if(m == 1 || n == 1) {
				if(n==1) n=m;
				result =  new double[n+1];
				memcpy((void *)result, (void *)mxGetPr(T), sizeof(double)*n);
			}
		}
		mxDestroyArray(T);
	}

	*array = n;
	return result;
}

string MatlabSession::generateRandomName() {
	string result;
	stringstream ss;

	for(int i=0;i<RANDOM_VARNAME_LENGTH;i++) {
		int ramdonValue = rand()%26 + 65;
		ss << (char)ramdonValue;
	}
	ss >> result;
	return result;
}

