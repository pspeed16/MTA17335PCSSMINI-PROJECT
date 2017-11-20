#include "Game.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace std;



[STAThreadAttribute]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PcssGame::Game game;
	Application::Run(%game);



	return 0;
}
