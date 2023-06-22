#pragma once

#include <GameEngineCore/GameEngineActor.h>

class TranslucentBlock : public GameEngineActor
{
public:
	// constrcuter destructer
	TranslucentBlock();
	~TranslucentBlock();

	// delete Function
	TranslucentBlock(const TranslucentBlock& _Other) = delete;
	TranslucentBlock(TranslucentBlock&& _Other) noexcept = delete;
	TranslucentBlock& operator=(const TranslucentBlock& _Other) = delete;
	TranslucentBlock& operator=(TranslucentBlock&& _Other) noexcept = delete;

protected:

private:
	class GameEngineRenderer* MainRenderer = nullptr;

	void Start() override;
};

