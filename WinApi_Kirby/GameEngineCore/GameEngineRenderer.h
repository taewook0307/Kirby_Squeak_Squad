#pragma once
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>
#include <vector>

enum class CameraType
{
	MAIN,
	UI,
};

// 설명 :
class GameEngineSprite;
class GameEngineActor;
class GameEngineWindowTexture;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend class GameEngineCamera;
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetSprite(const std::string& _Name, size_t _Index = 0);

	void SetTexture(const std::string& _Name);

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}


	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}

	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetScaleRatio(const float& _Scale)
	{
		ScaleRatio = _Scale;
	}


	void SetRenderScaleToTexture();


	void SetOrder(int _Order) override;

protected:
	void Start() override;


private:
	GameEngineCamera* Camera = nullptr;
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineSprite* Sprite = nullptr;

	float ScaleRatio = 1.0f;

	bool ScaleCheck = false;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	void Render(float _DeltaTime);

private:
	class Animation
	{
	public:
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector<size_t> Frames;
		std::vector<float> Inters;
		bool Loop = true;
		bool IsEnd = false;
	};

public:
	Animation* FindAnimation(const std::string& _AniamtionName);

	/// <summary>
	/// 애니메이션 생성함수
	/// </summary>
	/// <param name="_AniamtionName">애니메이션 이름</param>
	/// <param name="_SpriteName">스프라이트 이름</param>
	/// <param name="_Start">시작 프레임</param>
	/// <param name="_End">끝 프레임</param>
	/// <param name="_Inter">애니메이션 시간</param>
	/// <param name="_Loop">애니메이션 반복</param>
	void CreateAnimation(
		const std::string& _AniamtionName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _Loop = true);

	void ChangeAnimation(const std::string& _AniamtionName, bool _ForceChange = false);

	void MainCameraSetting();
	void UICameraSetting();

	size_t GetCurFrame()
	{
		return CurAnimation->CurFrame;
	}

	bool IsAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	CameraType CameraTypeValue = CameraType::MAIN;

	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};

