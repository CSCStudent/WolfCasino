#include <iostream>
#ifdef _WIN32
#include <Windows.h> // Windows system()
#else
#include <unistd.h> // Linux system()
#endif
#include "Casino.h"
using namespace std;

//defined namespace CSC2034 for project
using namespace CSC2034;
int main(int argc, char* argv[]) {

	if (argc > 1) {
		cout << "Welcome to the Wolf Casino.  You have chosen to play: " << argv[1] << std::endl;
		cout << "Getting game ready." << endl;
		Sleep(3000);
		try {
			Casino::play(argv[1]); //static function call
		}
		catch (NoGame e) {
			cout << e.getMsg();
		}
	}
	else
		std::cout << "Usage: WolfCasinoGame game_to_play" << std::endl;
}