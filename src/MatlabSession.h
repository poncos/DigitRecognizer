#ifndef MATLABSESSION_H_
#define MATLABSESSION_H_

#include "engine.h"
#include <iostream>
#include <string>

using namespace std;

class MatlabSession {
	
	private:
		static MatlabSession* instance;

		Engine *ep;

	protected:
		MatlabSession();
//		MatlabSession(const MatlabSession&);
//		MatlabSession& operator=(MatlabSession&);

	public:
		static MatlabSession* createSession();
		~MatlabSession();

		// session management
		void closeSession();
		static MatlabSession* loadSession(string aFileName);
		void storeSession(string aFileName);

		// comand execution operations
		void execute(string aCommand);

		// window manage
		void showWindow();
		void hideWindow();
		
		// strings manipulations
		void setVarString(string aVarName, string aValue);
		string getVarString(string aVarName);

		// integer manipulations
		void setVarInteger(string aVarName, int aValue);
		int getVarInteger(string aVarName);

		void setVarDouble(string aVarName, double aValue);
		double getVarDouble(string aVarName);

		// matrix functions
		void createIntegerArray(string aVarName, int* anArray, int length );
		void createDoubleArray(string aVarName, double* anArray, int length);
		int* getIntegerArray(string aVarName, int* arrayLength);
		double* getDoubleArray(string aVarName, int* arrayLength);

		// utilities
		string generateRandomName();
};


#endif
