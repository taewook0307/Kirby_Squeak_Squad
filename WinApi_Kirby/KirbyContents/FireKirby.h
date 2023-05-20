#pragma once

#include "Kirby.h"

class FireKirby : public Kirby
{
public:
	// constrcuter destructer
	FireKirby();
	~FireKirby();

	// delete Function
	FireKirby(const FireKirby& _Other) = delete;
	FireKirby(FireKirby&& _Other) noexcept = delete;
	FireKirby& operator=(const FireKirby& _Other) = delete;
	FireKirby& operator=(FireKirby&& _Other) noexcept = delete;

protected:

private:

};

