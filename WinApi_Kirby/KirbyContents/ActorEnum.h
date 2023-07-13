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
	AttackRun,
	Attack,
	AttackToIdle,
	FlyReady,
	FlyUp,
	Fly,
	FlyDrop,
	MonsterSummonReady,
	MonsterSummonJump,
	MonsterSummonDrop,
	MonsterSummon,
	Damage,
	DeathJump,
	Death,
	Max
};

enum class CollisionOrder
{
	Body,
	Inhale,
	Attack,
	SpecialAttack,
	ItemBody,
	MonsterBody,
	MonsterAttack,
	MonsterSearch,
	BossBody,
	BossAttackBody,
	BossAttack,
	BossSearch,
	Obstacle,
	FloorObstacle,
	Max
};

enum class ActorDir
{
	Left,
	Right
};