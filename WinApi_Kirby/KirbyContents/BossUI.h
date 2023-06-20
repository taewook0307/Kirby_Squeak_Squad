#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define BOSSHPBARPOS { 200.0f, 50.0f }
#define BOSSHPBARSCALE { 200.0f, 30.0f }

class GameEngineRenderer;
class BossUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BossUI();
	~BossUI();

	// delete Function
	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* BossHpBar = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};