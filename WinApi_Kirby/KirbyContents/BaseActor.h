#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

#define BASEHP 200
#define BASEATT 70
#define MONSTERATT 50

#define GRAVITYPOWER 700.0f
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

	void FlyGravity(float _Delta);

	inline void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	inline float4 GetGravityVector() const
	{
		return GravityVector;
	}

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

	void SetGroundBitMap(GameEngineWindowTexture* _BitMap);

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
	inline int GetHp() const
	{
		return Hp;
	}

	inline int GetAtt() const
	{
		return Att;
	}

	inline void Damage(int _Value)
	{
		Hp -= Att;
	}

	inline void IsCheckPosPointChange()
	{
		IsCheckPosPoint = !IsCheckPosPoint;
	}

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineRenderer* MainRenderer = nullptr;

	bool IsCheckPosPoint = false;

private:
	int Hp = BASEHP;
	int Att = BASEATT;

	GameEngineWindowTexture* GroundBitMap = nullptr;

	bool IsGravity = true;

	float GravityAcceleration = GRAVITYPOWER;

	float4 GravityVector = float4::ZERO;
};

