#include "GameEngineWindowTexture.h"

#include <GameEngineBase/GameEngineDebug.h>

GameEngineWindowTexture::GameEngineWindowTexture()
{
}

GameEngineWindowTexture::~GameEngineWindowTexture()
{
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
{
	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 로드에 실패했습니다" + _Path);
		return;
	}

	BitMap = static_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(nullptr);

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}

float4 GameEngineWindowTexture::GetScale()
{
	return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
}

void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4 _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	BitBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		0,
		0,
		SRCCOPY);
}

void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4 _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//TransparentBlt(ImageDC,
	//	_Pos.iX() - _Scale.ihX(),
	//	_Pos.iY() - _Scale.ihY(),
	//	_Scale.iX(),
	//	_Scale.iY(),
	//	CopyImageDC,
	//	0,		// 카피 하려는 이미지의 왼쪽 위 x
	//	0,		// 카피 하려는 이미지의 오른쪽 위 x
	//	0,		// 카피 하려는 이미지의 크기 x
	//	0,		// 카피 하려는 이미지의 크기 y
	//	0
	//);
}