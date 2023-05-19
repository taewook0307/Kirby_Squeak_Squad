#pragma once

enum class KirbyState
{
	Idle,
	Down,
	Slide,
	Jump,
	Walk,
	Run,
	Stop,
	Breathe,
	BreatheOut,
	Drop,
	Fly,
	Move,
	Attack,
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