#pragma once
#include "GameEngineWindowTexture.h"

#include <Windows.h>
#include <string>

class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC() const
	{
		return Hdc;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	static void WindowLoopOff()
	{
		IsWindowUpdate = false;
	}

	void ClearBackBuffer();
	void DoubleBuffering();
protected:

private:
	static bool IsWindowUpdate;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;
	float4 Scale = float4::ZERO;
	GameEngineWindowTexture* WindowBuffer = nullptr;
	GameEngineWindowTexture* BackBuffer = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};