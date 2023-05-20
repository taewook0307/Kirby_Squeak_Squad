#pragma once

#include "Kirby.h"

class TornadoKirby : public Kirby
{
public:
	// constrcuter destructer
	TornadoKirby();
	~TornadoKirby();

	// delete Function
	TornadoKirby(const TornadoKirby& _Other) = delete;
	TornadoKirby(TornadoKirby&& _Other) noexcept = delete;
	TornadoKirby& operator=(const TornadoKirby& _Other) = delete;
	TornadoKirby& operator=(TornadoKirby&& _Other) noexcept = delete;

protected:

private:

};

