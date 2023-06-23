#pragma once

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class CutScene : public GameEngineActor
{
public:
	// constrcuter destructer
	CutScene();
	~CutScene();

	// delete Function
	CutScene(const CutScene& _Other) = delete;
	CutScene(CutScene&& _Other) noexcept = delete;
	CutScene& operator=(const CutScene& _Other) = delete;
	CutScene& operator=(CutScene&& _Other) noexcept = delete;

	void CutSceneAnimationInit(const std::string& _FolderName, float Inter = 0.5f);
protected:

private:
	std::string FileName = "";
	float4 Scale = float4::ZERO;
	class GameEngineSprite* MainSprite = nullptr;
	class GameEngineRenderer* MainRenderer = nullptr;
};