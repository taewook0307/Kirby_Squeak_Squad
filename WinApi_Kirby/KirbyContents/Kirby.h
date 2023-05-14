#pragma once

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class Kirby : public GameEngineActor
{
public:
	// constrcuter destructer
	Kirby();
	~Kirby();

	// delete Function
	Kirby(const Kirby& _Other) = delete;
	Kirby(Kirby&& _Other) noexcept = delete;
	Kirby& operator=(const Kirby& _Other) = delete;
	Kirby& operator=(Kirby&& _Other) noexcept = delete;

	void FormInit(const std::string& _ImagePath, const std::string& _ImageName);
protected:

private:
	void Update(float _Delta) override;

	std::string ImagePath;
	std::string ImageName;
};