#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KirbyNormal : public GameEngineActor
{
public:
	// constrcuter destructer
	KirbyNormal();
	~KirbyNormal();

	// delete Function
	KirbyNormal(const KirbyNormal& _Other) = delete;
	KirbyNormal(KirbyNormal&& _Other) noexcept = delete;
	KirbyNormal& operator=(const KirbyNormal& _Other) = delete;
	KirbyNormal& operator=(KirbyNormal&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;

	void Render() override;

	void Release() override;
};

