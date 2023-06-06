#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

#define BASEPOWER 300.0f
#define EMPTYCOLOR RGB(255,255,255)
#define DOORCOLOR RGB(0,0,255)
#define SLOPECOLOR RGB(0,255,0)

#define TOPCHECKPOS { 0.0f, -80.0f }
#define LEFTTOPCHECKPOS { -40.0f , -80.0f }
#define RIGHTTOPCHECKPOS { 40.0f , -80.0f }
#define LEFTCHECKPOS { -40.0f , -40.0f }
#define RIGHTCHECKPOS { 40.0f , -40.0f }
#define LEFTBOTCHECKPOS { -40.0f , 0.0f }
#define RIGHTBOTCHECKPOS { 40.0f , 0.0f }

class GameEngineWindowTexture;
class BaseActor : public GameEngineActor
{
public:
	// constrcuter destructer
	BaseActor();
	~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	inline void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	inline void GravityOn()
	{
		IsGravity = true;
	}

	inline void GravityOff()
	{
		IsGravity = false;
	}

	void SetGroundBitMap(const std::string& _GroundBitMap);

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	GameEngineWindowTexture* GetGroundBitMap() const
	{
		return GroundBitMap;
	}

	float4 ActorCameraPos();

	GameEngineCollision* GetBodyCollision()
	{
		return BodyCollision;
	}

protected:
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineRenderer* MainRenderer = nullptr;

private:
	GameEngineWindowTexture* GroundBitMap = nullptr;

	bool IsGravity = true;

	float GravityAcceleration = 9.8f;

	float4 GravityVector = float4::ZERO;
};

