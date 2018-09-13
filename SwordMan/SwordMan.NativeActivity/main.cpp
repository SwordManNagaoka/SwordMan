#include "DxLib.h"
#include "GameController/GameMain.hpp"

#ifdef __ANDROID__
// Android版のコンパイルだったら android_main
int android_main(void)
#else
// Windows版のコンパイルだったら WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	GameMain game;
	game.Run();
	return 0;                   // ソフトの終了 
}