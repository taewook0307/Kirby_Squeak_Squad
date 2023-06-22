#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define FORMUIPOS { 65.0f, -60.0f }
#define FORMUISCALE { 140.0f, 120.0f }

#define HPBARPOS { 300.0f, -30.0f }
#define HPBARSCALE { 300.0f, 50.0f }

#define LIFECOUNTPOS { 275.0f, -90.0f }
#define LIFECOUNTSCALE { 70.0f, 50.0f }

#define LIFEICONPOS { 200.0f, -90.0f }
#define LIFEICONSCALE { 70.0f, 50.0f }

class GameEngineRenderer;
class KirbyUI : public GameEngineActor
{
public:
	// constrcuter destructer
	KirbyUI();
	~KirbyUI();

	// delete Function
	KirbyUI(const KirbyUI& _Other) = delete;
	KirbyUI(KirbyUI&& _Other) noexcept = delete;
	KirbyUI& operator=(const KirbyUI& _Other) = delete;
	KirbyUI& operator=(KirbyUI&& _Other) noexcept = delete;

protected:
	inline void IsCheckPosPointChange()
	{
		IsCheckPosPoint = !IsCheckPosPoint;
	}

	bool IsCheckPosPoint = false;
private:
	GameEngineRenderer* FormUI = nullptr;
	GameEngineRenderer* HpBar = nullptr;
	GameEngineRenderer* LifeIcon = nullptr;
	GameEngineRenderer* LifeCount = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;

	void KirbyFormUIUpdate(const std::string& _ImageName);
	void KirbyHpBarImageUpdate(const std::string& _ImageName);
	void KirbyLifeCountImageUpdate(const std::string& _ImageName);
};

