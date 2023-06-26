#include "TileMap.h"
#include "GameEngineRenderer.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::Update(float _DeltaTime)
{
	SetPos(float4::ZERO);

	if (false == IsLerpMove())
	{
		return;
	}

	// Lerp는 Start에서 end까지 정확하게 1초만에 도달하게 해줘.
	LerpTime += _DeltaTime * LerpSpeed;

	for (size_t i = 0; i < LerpInfos.size(); i++)
	{
		GameEngineRenderer* LerpTileRenderer = LerpInfos[i].LerpTileRenderer;
		float4 Pos = float4::LerpClimp(LerpInfos[i].StartPos, LerpInfos[i].EndPos, LerpTime);
		LerpTileRenderer->SetRenderPos(Pos);
	}

	if (1 <= LerpTime)
	{
		for (size_t i = 0; i < LerpInfos.size(); i++)
		{
			GameEngineRenderer* LerpTileRenderer = LerpInfos[i].LerpTileRenderer;
			float4 Pos = PosToIndex(LerpInfos[i].EndPos - TileSize.Half() - LerpInfos[i].LerpTilePos);
			Tiles[Pos.iY()][Pos.iX()] = LerpTileRenderer;
		}
		LerpInfos.clear();
		// LerpTileRenderer = nullptr;
	}
}

//                                                      200    300
void TileMap::CreateTileMap(const std::string& _Sprite, int X, int Y, float4 _TileSize, int _Order)
{
	Sprite = _Sprite;
	Order = _Order;
	TileSize = _TileSize;

	TileX = X;
	TileY = Y;

	// nullptr로 만들어진 배열을 만들뿐이다.
	Tiles.resize(Y);

	for (size_t y = 0; y < Y; y++)
	{
		Tiles[y].resize(X);
	}
}

bool TileMap::IsOver(int X, int Y)
{
	if (X < 0)
	{
		return true;
	}

	if (Y < 0)
	{
		return true;
	}

	if (TileY <= Y)
	{
		return true;
	}

	if (TileX <= X)
	{
		return true;
	}

	return false;
}

float4 TileMap::IndexToPos(int X, int Y)
{
	// 100, 100
	// 5 8 
	// 500 800
	return { TileSize.X * X, TileSize.Y * Y };
}

GameEngineRenderer* TileMap::GetTile(int X, int Y)
{
	if (true == IsOver(X, Y))
	{
		return nullptr;
	}

	return Tiles[Y][X];
}

float4 TileMap::PosToIndex(float4 _Pos)
{
	return { _Pos.X / TileSize.X , _Pos.Y / TileSize.Y };
}

GameEngineRenderer* TileMap::SetTile(float4 _Pos, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	float4 Index = PosToIndex(_Pos);

	return SetTile(Index.iX(), Index.iY(), _Index, _TilePos, _IsImageSize/* = false*/);
}

GameEngineRenderer* TileMap::SetTile(int X, int Y, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	if (true == IsOver(X, Y))
	{
		return nullptr;
	}

	if (nullptr == Tiles[Y][X])
	{
		Tiles[Y][X] = CreateRenderer(Order);
	}

	Tiles[Y][X]->SetSprite(Sprite, _Index);
	Tiles[Y][X]->SetRenderPos(IndexToPos(X, Y) + TileSize.Half() + _TilePos);

	if (false == _IsImageSize)
	{
		Tiles[Y][X]->SetRenderScale(TileSize);
	}
	else {
		Tiles[Y][X]->SetRenderScaleToTexture();
	}

	return Tiles[Y][X];
}

bool TileMap::MoveTile(int X1, int Y1, int X2, int Y2, float4 _TilePos)
{
	if (nullptr == Tiles[Y1][X1])
	{
		return false;
	}

	if (nullptr != Tiles[Y2][X2])
	{
		return false;
	}

	GameEngineRenderer* Tile = Tiles[Y1][X1];
	Tiles[Y1][X1] = nullptr;

	Tiles[Y2][X2] = Tile;
	Tile->SetRenderPos(IndexToPos(X2, Y2) + TileSize.Half() + _TilePos);
	return true;
}

bool TileMap::LerpTile(int X1, int Y1, int X2, int Y2, float4 _TilePos)
{
	if (nullptr == Tiles[Y1][X1])
	{
		return false;
	}

	if (true == IsLerpRenderer(Tiles[Y1][X1]))
	{
		return false;
	}

	if (nullptr != Tiles[Y2][X2])
	{
		return false;
	}

	// Lerp
	// 100, 100

	// 200, 200

	// 200, 200 - 100, 100
	// 100, 100

	// 여기서는 이동하는게 아니라
	// 서서히 움직일 준비를 하는 함수.
	// LerpTileRenderer = Tiles[Y1][X1];
	LerpTileInfo NewInfo;
	NewInfo.LerpTileRenderer = Tiles[Y1][X1];
	NewInfo.LerpTilePos = _TilePos;
	NewInfo.StartPos = IndexToPos(X1, Y1) + TileSize.Half() + _TilePos;
	NewInfo.EndPos = IndexToPos(X2, Y2) + TileSize.Half() + _TilePos;

	Tiles[Y1][X1] = nullptr;
	Tiles[Y2][X2] = nullptr;


	//LerpTilePos = _TilePos;
	//StartPos = IndexToPos(X1, Y1) + TileSize.Half() + _TilePos;
	//EndPos = IndexToPos(X2, Y2) + TileSize.Half() + _TilePos;
	//LerpTime = 0.0f;


	LerpTime = 0.0f;

	LerpInfos.push_back(NewInfo);

	return true;
}


void TileMap::DeathTile(float4 _Pos)
{
	float4 Index = PosToIndex(_Pos);

	DeathTile(Index.iX(), Index.iY());
}

void TileMap::DeathTile(int X, int Y)
{
	if (true == IsOver(X, Y))
	{
		return;
	}

	if (nullptr == Tiles[Y][X])
	{
		return;
	}

	Tiles[Y][X]->Death();
	Tiles[Y][X] = nullptr;

}


bool TileMap::IsLerpRenderer(GameEngineRenderer* _Renderer)
{
	for (size_t i = 0; i < LerpInfos.size(); i++)
	{
		if (LerpInfos[i].LerpTileRenderer == _Renderer)
		{
			return true;
		}
	}

	return false;
}