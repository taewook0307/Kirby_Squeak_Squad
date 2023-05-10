#include "GameEngineWindow.h"

#include <GameEngineBase/GameEngineDebug.h>

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != WindowBuffer)
    {
        delete WindowBuffer;
        WindowBuffer = nullptr;
    }

    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = nullptr;
    }
}

void GameEngineWindow::ClearBackBuffer()
{
    Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
    WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
    Instance = _hInstance;
    Title = _Title;

    if (nullptr == Instance)
    {
        MsgBoxAssert("HInstance없이 윈도우를 만들수는 없습니다.");
        return;
    }

    MyRegisterClass();
    InitInstance();
}


void GameEngineWindow::InitInstance()
{
    // 윈도우 만드는 함수인
    // const char* == std::string
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("윈도우 생성에 실패했습니다.");
        return;
    }

    Hdc = GetDC(hWnd);

    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    BackBuffer = new GameEngineWindowTexture();
    BackBuffer->ResCreate(WindowBuffer->GetScale());

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        IsWindowUpdate = false;
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void GameEngineWindow::MyRegisterClass()
{
    static bool Check = false;

    if (true == Check)
    {
        return;
    }

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // LRESULT(CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, unsigned int);
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr;

    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("윈도우 클래스 동록에 실패했습니다.");
        return;
    }

    Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;
    while (IsWindowUpdate)
    {
        // 윈도우에 무슨 일이 있는게 아니라 메시지가 없어도 리턴되어야 함
        // 동기함수 : 함수가 제대로 끝날때까지 기다리는 함수, 함수가 제대로 끝이 나야 return
        // 동기 ex) _getch(), GetMessage() 등
        // 비동기함수
        // PeekMessage : 윈도우 메세지가 없으면 그냥 0이 리턴
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 여기에서 한바퀴가 도는 것을 프레임
            // FPS : 초당 화면이 그려지는 횟수
            if (nullptr != _Update)
            {
                _Update();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // 윈도우 메세지가 없는 시간을 데드타임
        // 게임은 보통 데드타임에 돌아가는게 보통

        if (nullptr != _Update)
        {
            _Update();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    // (int)msg.wParam;

    return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    Scale = _Scale;

    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture();
        BackBuffer->ResCreate(Scale);
    }

    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}