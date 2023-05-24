#pragma once

enum class KirbyState
{
	Idle,
	Down,
	Slide,
	Jump,
	JumpToDown,
	JumpToLand,
	Walk,
	Run,
	Stop,
	StopToIdle,
	Breathe,
	BreatheOut,
	Fly,
	Drop,
	FlyLand,
	FlyLandTurn,
	Move,
	Damage,
	Max
};

enum class MonsterState
{
	Idle,
	Walk,
	Attack,
	Damage,
	Jump,
	Max
};

enum class ActorDir
{
	Left,
	Right
};