#include <GameEnginePlatform/GameEngineWindow.h>
#include <iostream>

void TestStart(HINSTANCE _Inst)
{
    GameEngineWindow::MainWindow.Open("MainWindow", _Inst);
}

void TestUpdate()
{

}

void TestEnd()
{

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineWindow::MessageLoop(hInstance, TestStart, TestUpdate, TestEnd);
    return 0;
}