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
	Death,
	Max
};

enum class MonsterType
{
	Normal,
	Ice,
	Fire,
	Tornado,
	Spark,
	Boss,
	Max
};

enum class MonsterState
{
	Idle,
	Walk,
	Attack,
	Inhale,
	Damage,
	Death,
	Max
};

enum class BossState
{
	Idle,
	Walk,
	JumpReady,
	Jump,
	Drop,
	AttackReady,
	Attack,
	AttackToIdle,
	MonsterSummonReady,
	MonsterSummonJump,
	MonsterSummonDrop,
	MonsterSummon,
	Damage,
	Death,
	Max
};

enum class CollisionOrder
{
	Body,
	Inhale,
	Attack,
	SpecialAttack,
	MonsterBody,
	MonsterAttack,
	MonsterSearch,
	BossBody,
	BossAttack,
	BossSearch,
	Max
};

enum class ActorDir
{
	Left,
	Right
};