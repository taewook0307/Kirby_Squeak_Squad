#pragma once

enum class ActorState
{
	Idle,
	Walk,
	Run,
	Stop,
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