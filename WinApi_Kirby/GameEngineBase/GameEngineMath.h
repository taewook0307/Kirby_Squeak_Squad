#pragma once

class GameEngineMath
{
};

class float4
{
public:
	static const float4 ZERO;

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return X * 0.5f;
	}

	inline float hY() const
	{
		return Y * 0.5f;
	}

	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	float4 operator+(const float4& _Other)
	{
		float4 ResultValue;

		ResultValue.X = X + _Other.X;
		ResultValue.Y = Y + _Other.Y;
		ResultValue.Z = Z + _Other.Z;

		return ResultValue;
	}

	float4 operator*(const float4& _Other)
	{
		float4 ResultValue;

		ResultValue.X = X * _Other.X;
		ResultValue.Y = Y * _Other.Y;
		ResultValue.Z = Z * _Other.Z;

		return ResultValue;
	}

	float4 operator*(const float _Other)
	{
		float4 ResultValue;

		ResultValue.X = X * _Other;
		ResultValue.Y = Y * _Other;
		ResultValue.Z = Z * _Other;

		return ResultValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Other)
	{
		X *= _Other;
		Y *= _Other;
		Z *= _Other;

		return *this;
	}
};