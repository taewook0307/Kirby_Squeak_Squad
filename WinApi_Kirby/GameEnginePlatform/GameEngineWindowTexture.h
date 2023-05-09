#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineWindowTexture
{
public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);

	void ResCreate(HDC _ImageDC)
	{
		ImageDC = _ImageDC;
	}

	HDC GetImageDC()
	{
		return ImageDC;
	}

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4 _Scale);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4 _Scale);
protected:

private:
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	HDC ImageDC = nullptr;

	BITMAP Info;

	void ScaleCheck();
};