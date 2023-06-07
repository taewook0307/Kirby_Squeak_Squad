#pragma once

enum class KirbyState
{
	Idle,
	Down,
	Slide,
	Jump,
	JumpToDrop,
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
	AttackToIdle,
	Keep,
	KeepIdle,
	KeepWalk,
	KeepJump,
	KeepJumpToDrop,
	KeepJumpToLand,
	KeepDamage,
	Change,
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

enum class MonsterType
{
	Normal,
	Ice,
	Fire,
	Tornado,
	Spark,
	Max
};

enum class CollisionOrder
{
	Body,
	Attack,
	SpecialAttack,
	MonsterBody,
	MonsterAttack,
	MonsterSearch
};

enum class ActorDir
{
	Left,
	Right
};