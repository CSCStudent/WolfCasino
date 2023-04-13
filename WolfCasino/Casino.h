#pragma once
#include <string>
using namespace std;

// CSC2034 ++ class project
//Header file for class Casino
// Header file for class Casino

namespace CSC2034 {
	class Casino {
	public:
		static void play(string);
		virtual void start();
		~Casino();

	};

	class NoGame {
	public:
		NoGame(string s) {
			msg = s;
		}
		string getMsg() { return msg; }
	private:
		string msg;
	};
}
