#pragma once

#include "Kirby.h"

class GameEngineCollision;
class FormKirby : public Kirby
{
public:
	// constrcuter destructer
	FormKirby();
	~FormKirby();

	// delete Function
	FormKirby(const FormKirby& _Other) = delete;
	FormKirby(FormKirby&& _Other) noexcept = delete;
	FormKirby& operator=(const FormKirby& _Other) = delete;
	FormKirby& operator=(FormKirby&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta) override;
	void ChangeState(KirbyState _State) override;

	void ChangeStart() override;
	void ChangeUpdate(float _Delta) override;

private:
};

