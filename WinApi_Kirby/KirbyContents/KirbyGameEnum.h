#pragma once

enum class UpdateOrder
{
	PlayUI,
	Player,
	PlayerObject,
	Monster,
	SummonObject
};

enum class RenderOrder
{
	BackGround,
	Map,
	Boss,
	Play,
	Monster,
	Item,
	PlayUI,
	Fade
};