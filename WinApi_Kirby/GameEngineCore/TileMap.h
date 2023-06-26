#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <vector>
#include "GameEngineActor.h"

class LerpTileInfo
{
public:
	GameEngineRenderer* LerpTileRenderer;
	// 보통 타일이나 턴제 게임에서 사용하게 된다.
	float4 StartPos;
	float4 EndPos;
	float4 LerpTilePos;
};

// 설명 :
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

	// A위치에 B위치로 가려고 하는것.
	// 서서히 움직여서 목적지에 도달시키는 기능.
	bool LerpTile(int X1, int Y1, int X2, int Y2, float4 _TilePos);

	GameEngineRenderer* SetTile(int X, int Y, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

	GameEngineRenderer* SetTile(float4 _Pos, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

	bool IsOver(int X, int Y);

	float4 IndexToPos(int X, int Y);

	float4 PosToIndex(float4 _Pos);

	void DeathTile(float4 _Pos);

	void DeathTile(int X, int Y);

	void Update(float _DeltaTime) override;

	float4 GetTileSize()
	{
		return TileSize;
	}

	bool IsLerpMove()
	{

		return LerpInfos.size() != 0;
		// return nullptr != LerpTileRenderer;
	}

	void SetLerpSpeed(float _Speed)
	{
		LerpSpeed = _Speed;
	}

protected:
	float LerpSpeed = 5.0f;

	//GameEngineRenderer* LerpTileRenderer;
	//// 보통 타일이나 턴제 게임에서 사용하게 된다.
	//float4 StartPos;
	//float4 EndPos;
	//float4 LerpTilePos;
	float LerpTime = 0.0f;

	std::vector<LerpTileInfo> LerpInfos;


private:
	int TileX = 0;
	int TileY = 0;
	int Order = 0;
	float4 TileSize;
	std::string Sprite;
	std::vector<std::vector<class GameEngineRenderer*>> Tiles;

	bool IsLerpRenderer(GameEngineRenderer* _Renderer);
};

