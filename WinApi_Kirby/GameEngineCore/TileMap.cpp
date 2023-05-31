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

void TileMap::SetTile(float4 _Pos, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	float4 Index = PosToIndex(_Pos);

	SetTile(Index.iX(), Index.iY(), _Index, _TilePos, _IsImageSize/* = false*/);
}

void TileMap::SetTile(int X, int Y, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	if (true == IsOver(X, Y))
	{
		return;
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
}