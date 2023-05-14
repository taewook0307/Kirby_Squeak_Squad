#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _LevelName, const std::string& _FileName);

protected:

private:
	std::string FileName;

	void Update(float _Delta) override;
};