#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <list>

bool (*GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(const CollisionData& _LeftData, const CollisionData& _RightData) = { nullptr };

bool GameEngineCollision::PointToPoint(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	MsgBoxAssert("충돌체크함수를 만들지 않았습니다.");
	return false;
}
bool GameEngineCollision::PointToRect(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	if (_RightData.Bot() < _LeftData.Pos.Y)
	{
		return false;
	}

	if (_RightData.Top() > _LeftData.Pos.Y)
	{
		return false;
	}

	if (_RightData.Left() > _LeftData.Pos.X)
	{
		return false;
	}

	if (_RightData.Right() < _LeftData.Pos.X)
	{
		return false;
	}

	return true;
}
bool GameEngineCollision::PointToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	float Len = (_LeftData.Pos - _RightData.Pos).Size();
	float RadiusSum = _RightData.Scale.Max2D();
	RadiusSum *= 0.5f;

	if (Len <= RadiusSum)
	{
		return true;
	}

	return false;
}
bool GameEngineCollision::RectToPoint(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	if (_LeftData.Bot() < _RightData.Pos.Y)
	{
		return false;
	}

	if (_LeftData.Top() > _RightData.Pos.Y)
	{
		return false;
	}

	if (_LeftData.Left() > _RightData.Pos.X)
	{
		return false;
	}

	if (_LeftData.Right() < _RightData.Pos.X)
	{
		return false;
	}

	return true;
}
bool GameEngineCollision::RectToRect(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	if (_LeftData.Bot() < _RightData.Top())
	{
		return false;
	}

	if (_LeftData.Top() > _RightData.Bot())
	{
		return false;
	}

	if (_LeftData.Left() > _RightData.Right())
	{
		return false;
	}

	if (_LeftData.Right() < _RightData.Left())
	{
		return false;
	}

	return true;
}
bool GameEngineCollision::RectToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	CollisionData PointData = _RightData;

	CollisionData Rect1 = _LeftData;
	Rect1.Scale.Y += _RightData.Scale.Max2D();

	CollisionData Rect2 = _LeftData;
	Rect2.Scale.X += _RightData.Scale.Max2D();

	if (true == RectToPoint(Rect1, PointData))
	{
		return true;
	}

	if (true == RectToPoint(Rect2, PointData))
	{
		return true;
	}

	CollisionData CirCle;
	CirCle.Pos = { _LeftData.Left(), _LeftData.Top() };
	CirCle.Scale = _RightData.Scale;
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _LeftData.Right(), _LeftData.Top() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _LeftData.Left(), _LeftData.Bot() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _LeftData.Right(), _LeftData.Bot() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}


	// MsgBoxAssert("충돌체크함수를 만들지 않았습니다.");
	// 원4개 충돌이니까.

	return false;
}
bool GameEngineCollision::CirCleToPoint(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	float Len = (_LeftData.Pos - _RightData.Pos).Size();
	float RadiusSum = _LeftData.Scale.Max2D();
	RadiusSum *= 0.5f;

	if (Len <= RadiusSum)
	{
		return true;
	}

	return false;
}
bool GameEngineCollision::CirCleToRect(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	CollisionData PointData = _LeftData;

	CollisionData Rect1 = _RightData;
	Rect1.Scale.Y += _LeftData.Scale.Max2D();

	CollisionData Rect2 = _RightData;
	Rect2.Scale.X += _LeftData.Scale.Max2D();

	if (true == RectToPoint(Rect1, PointData))
	{
		return true;
	}

	if (true == RectToPoint(Rect2, PointData))
	{
		return true;
	}

	CollisionData CirCle;
	CirCle.Pos = { _RightData.Left(), _RightData.Top() };
	CirCle.Scale = _LeftData.Scale;
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _RightData.Right(), _RightData.Top() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _RightData.Left(), _RightData.Bot() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}

	CirCle.Pos = { _RightData.Right(), _RightData.Bot() };
	if (true == CirCleToPoint(CirCle, PointData))
	{
		return true;
	}


	// MsgBoxAssert("충돌체크함수를 만들지 않았습니다.");
	// 원4개 충돌이니까.

	return false;
}
bool GameEngineCollision::CirCleToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData)
{
	float Len = (_LeftData.Pos - _RightData.Pos).Size();
	float RadiusSum = _LeftData.Scale.Max2D() + _RightData.Scale.Max2D();
	RadiusSum *= 0.5f;

	if (Len <= RadiusSum)
	{
		return true;
	}

	return false;
}

class CollisionInitClass
{
public:
	CollisionInitClass()
	{
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::PointToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::PointToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::PointToCirCle;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::RectToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::RectToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::RectToCirCle;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::CirCleToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::CirCleToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::CirCleToCirCle;
	}
};

CollisionInitClass ColInitInst = CollisionInitClass();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
	//Points.push_back({1, 0});
	//Points.push_back({ 1, 0 });
}

float4 GameEngineCollision::GetActorPivotPos()
{
	return GetActor()->GetPos() + CollisionPos;
}


bool GameEngineCollision::Collision(int _Order,
	std::vector<GameEngineCollision*>& _Result,
	CollisionType _ThisType,
	CollisionType _OtherType)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::list<GameEngineCollision*>& OtherCollision = GetActor()->GetLevel()->AllCollision[_Order];

	if (0 == OtherCollision.size())
	{
		return false;
	}

	bool Check = false;

	for (GameEngineCollision* Collision : OtherCollision)
	{
		if (nullptr == Collision)
		{
			MsgBoxAssert("존재하지 않는 콜리전이 있습니다.");
			return false;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		// 도대체 어느순간에 콜리전은 레벨에 들어가는가?
		// 언제 관리되는가?
		// 어떻게 꺼내오는가 ?
		// Level 

		// 상대랑 나랑 충돌을 해보는 것.
		if (true == CollisonCheck(Collision, _ThisType, _OtherType))
		{
			_Result.push_back(Collision);
			Check = true;
		}
	}

	return Check;
}


void GameEngineCollision::SetOrder(int _Order)
{
	std::list<GameEngineCollision*>& PrevCollisions = GetActor()->GetLevel()->AllCollision[GetOrder()];
	PrevCollisions.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineCollision*>& NextCollisions = GetActor()->GetLevel()->AllCollision[GetOrder()];
	NextCollisions.push_back(this);

}

bool GameEngineCollision::CollisonCheck(GameEngineCollision* _Other
	, CollisionType _ThisType
	, CollisionType _OtherType)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("충돌체크함수를 만들지 않았습니다.");
		return false;
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](this->GetCollisionData(), _Other->GetCollisionData());
}

void GameEngineCollision::DebugRender()
{

	if (false == CollisionRenderValue)
	{
		return;
	}

	CollisionData Data = GetCollisionData();

	Data.Pos -= GetActor()->GetLevel()->GetMainCamera()->GetPos();


	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	switch (ColType)
	{
	case CollisionType::Point:
		Data.Scale.X = 3;
		Data.Scale.Y = 3;
		Ellipse(BackBuffer->GetImageDC(), Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		break;
	case CollisionType::Rect:
		Rectangle(BackBuffer->GetImageDC(), Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		break;
	case CollisionType::CirCle:
		Data.Scale.X = Data.Scale.Max2D();
		Data.Scale.Y = Data.Scale.X;
		Ellipse(BackBuffer->GetImageDC(), Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		break;
	case CollisionType::Max:
		break;
	default:
		break;
	}
}

bool GameEngineCollision::CollisonCheckNext(const CollisionData& _Next, GameEngineCollision* _Other
	, CollisionType _ThisType
	, CollisionType _OtherType)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("충돌체크함수를 만들지 않았습니다.");
		return false;
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](_Next, _Other->GetCollisionData());
}

bool GameEngineCollision::CollisionNext(const float4& _NextPos, int _Order, std::vector<GameEngineCollision*>& _Result
	, CollisionType _ThisType
	, CollisionType _OtherType)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::list<GameEngineCollision*>& OtherCollision = GetActor()->GetLevel()->AllCollision[_Order];

	if (0 == OtherCollision.size())
	{
		return false;
	}

	bool Check = false;

	CollisionData NextData = GetCollisionData();
	NextData.Pos += _NextPos;

	for (GameEngineCollision* Collision : OtherCollision)
	{
		if (nullptr == Collision)
		{
			MsgBoxAssert("존재하지 않는 콜리전이 있습니다.");
			return false;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		// 도대체 어느순간에 콜리전은 레벨에 들어가는가?
		// 언제 관리되는가?
		// 어떻게 꺼내오는가 ?
		// Level 

		// 상대랑 나랑 충돌을 해보는 것.
		if (true == CollisonCheckNext(NextData, Collision, _ThisType, _OtherType))
		{
			_Result.push_back(Collision);
			Check = true;
		}
	}

	return Check;
}