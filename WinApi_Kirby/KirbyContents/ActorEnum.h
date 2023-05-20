#pragma once

enum class KirbyState
{
	Idle,
	Down,
	Slide,
	Jump,
	JumpToDown,
	JumptoLand,
	Walk,
	Run,
	Stop,
	StopToIdle,
	Breathe,
	BreatheOut,
	Fly,
	Drop,
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