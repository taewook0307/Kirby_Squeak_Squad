#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define EMPTYCOLOR RGB(255,255,255)

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

protected:

private:
	class GameEngineWindowTexture* GroundBitMap = nullptr;

	bool IsGravity = true;

	float GravityAcceleration = 9.8f;

	float4 GravityVector = float4::ZERO;
};

