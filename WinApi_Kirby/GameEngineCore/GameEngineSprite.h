#pragma once

#include <vector>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

class GameEngineSprite
{
public:
	class Sprite
	{
	public:
		GameEngineWindowTexture* BaseTexture = nullptr;
		float4 RenderPos = float4::ZERO;
		float4 RenderScale = float4::ZERO;
	};

	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	void CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount);

	const Sprite& GetSprite(size_t _Index);

	size_t GetSpriteCount()
	{
		return AllSprite.size();
	}
protected:

private:
	std::vector<Sprite> AllSprite;
};