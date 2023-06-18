#pragma once

#include <GameEngineCore/GameEngineActor.h>

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
	void Render(float _Delta) override;
};

