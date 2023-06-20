#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <vector>
#include "GameEngineActor.h"

// Ό³Έν :
class GameEngineSprite;
class TileMap : public GameEngineActor
{
public:
	// constrcuter destructer
	TileMap();
	~TileMap();

	// delete Function
	TileMap(const TileMap& _Other) = delete;
	TileMap(TileMap&& _Other) noexcept = delete;
	TileMap& operator=(const TileMap& _Other) = delete;
	TileMap& operator=(TileMap&& _Other) noexcept = delete;

	void CreateTileMap(const std::string& _Sprite, int X, int Y, float4 _TileSize, int _Order);

	GameEngineRenderer* GetTile(int X, int Y);

	// ChangeTile(int X1, int Y1, int X2, int Y2);

	bool MoveTile(int X1, int Y1, int X2, int Y2, float4 _TilePos);

	void SetTile(int X, int Y, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

	void SetTile(float4 _Pos, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

	bool IsOver(int X, int Y);

	float4 IndexToPos(int X, int Y);

	float4 PosToIndex(float4 _Pos);

	void Update(float _DeltaTime) override;

protected:

private:
	int TileX = 0;
	int TileY = 0;
	int Order = 0;
	float4 TileSize;
	std::string Sprite;
	std::vector<std::vector<class GameEngineRenderer*>> Tiles;
};

