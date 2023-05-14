#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);

protected:

private:
	std::string FileName;

	void Update(float _Delta) override;
};

