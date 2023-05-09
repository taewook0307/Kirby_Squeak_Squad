#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KirbyGameMap : public GameEngineActor
{
public:
	// constrcuter destructer
	KirbyGameMap();
	~KirbyGameMap();

	// delete Function
	KirbyGameMap(const KirbyGameMap& _Other) = delete;
	KirbyGameMap(KirbyGameMap&& _Other) noexcept = delete;
	KirbyGameMap& operator=(const KirbyGameMap& _Other) = delete;
	KirbyGameMap& operator=(KirbyGameMap&& _Other) noexcept = delete;

protected:

private:

};

