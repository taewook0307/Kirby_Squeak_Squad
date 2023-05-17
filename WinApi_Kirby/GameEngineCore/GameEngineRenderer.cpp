#include "GameEngineRenderer.h"
#include "ResourcesManager.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineSprite.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetSprite(const std::string& _Name, size_t _Index /* = 0*/)
{
	Sprite = ResourcesManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 세팅하려고 했습니다." + _Name);
		return;
	}

	const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(_Index);

	Texture = SpriteInfo.BaseTexture;

	SetCopyPos(SpriteInfo.RenderPos);
	SetCopyScale(SpriteInfo.RenderScale);
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐입니다" + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

void GameEngineRenderer::SetRenderScaleToTexture()
{
	if (nullptr != Texture)
	{
		RenderScale = Texture->GetScale();
	}
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->CurInter -= _Delta;
		if (0.0f >= CurAnimation->CurInter)
		{
			CurAnimation->CurInter = CurAnimation->Inters[CurAnimation->CurFrame - CurAnimation->StartFrame];
			++CurAnimation->CurFrame;

			if (CurAnimation->CurFrame > CurAnimation->EndFrame)
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurFrame = CurAnimation->StartFrame;
				}
				else
				{
					--CurAnimation->CurFrame;
				}
			}
		}
		Sprite = CurAnimation->Sprite;
		const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(CurAnimation->CurFrame);
		Texture = SpriteInfo.BaseTexture;
		SetCopyPos(SpriteInfo.RenderPos);
		SetCopyScale(SpriteInfo.RenderScale);

		if (false == ScaleCheck)
		{
			SetRenderScale(SpriteInfo.RenderScale * ScaleRatio);
		}
	}

	if (nullptr == Texture)
	{
		MsgBoxAssert("이미지를 세팅하지 않은 렌더러입니다");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
}

bool GameEngineRenderer::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}

GameEngineRenderer::Animation* GameEngineRenderer::FindAnimation(const std::string& _AniamtionName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniamtionName);

	std::map<std::string, Animation>::iterator FindIter = AllAnimation.find(UpperName);

	if (AllAnimation.end() == FindIter)
	{
		return nullptr;
	}

	return &FindIter->second;
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _AniamtionName,
	const std::string& _SpriteName,
	size_t _Start /*= -1*/,
	size_t _End /*= -1*/,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniamtionName);

	if (nullptr != FindAnimation(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션 이름입니다." + UpperName);
		return;
	}

	GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + _SpriteName);
		return;
	}

	GameEngineRenderer::Animation& Animation = AllAnimation[UpperName];

	Animation.Sprite = Sprite;

	if (_Start != -1)
	{
		Animation.StartFrame = _Start;
	}
	else
	{
		Animation.StartFrame = 0;
	}

	if (_End != -1)
	{
		Animation.EndFrame = _End;
	}
	else
	{
		Animation.EndFrame = Animation.Sprite->GetSpriteCount() - 1;
	}

	Animation.Inters.resize((Animation.EndFrame - Animation.StartFrame) + 1);

	for (size_t i = 0; i < Animation.Inters.size(); i++)
	{
		Animation.Inters[i] = _Inter;
	}

	Animation.Loop = _Loop;

}

void GameEngineRenderer::ChangeAnimation(const std::string& _AniamtionName, bool _ForceChange)
{
	Animation* ChangeAni = FindAnimation(_AniamtionName);

	if (ChangeAni == CurAnimation && false == _ForceChange)
	{
		return;
	}

	CurAnimation = FindAnimation(_AniamtionName);

	CurAnimation->CurInter = CurAnimation->Inters[0];
	CurAnimation->CurFrame = CurAnimation->StartFrame;

	if (nullptr == CurAnimation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다." + _AniamtionName);
		return;
	}
}