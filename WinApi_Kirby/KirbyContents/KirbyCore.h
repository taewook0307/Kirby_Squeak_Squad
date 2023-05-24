#pragma once

#include <GameEngineCore/GameEngineCore.h>

class KirbyCore : public CoreProcess
{
public:
	// constrcuter destructer
	KirbyCore();
	~KirbyCore();

	// delete Function
	KirbyCore(const KirbyCore& _Other) = delete;
	KirbyCore(KirbyCore&& _Other) noexcept = delete;
	KirbyCore& operator=(const KirbyCore& _Other) = delete;
	KirbyCore& operator=(KirbyCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;
};