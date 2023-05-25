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
	BreatheOutLand,
	BreatheOut,
	Fly,
	Drop,
	FlyToLand,
	FlyToTurnUp,
	FlyToTurnLand,
	LevelMove,
	Damage,
	DamageLand,
	AttackReady,
	Attack,
	Keep,
	Max
};

enum class MonsterState
{
	Idle,
	Walk,
	Attack,
	Damage,
	Max
};

enum class ActorDir
{
	Left,
	Right
};