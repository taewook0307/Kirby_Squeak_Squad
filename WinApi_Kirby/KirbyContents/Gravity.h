#pragma once

class Gravity
{
public:
	// delete Function
	Gravity(const Gravity& _Other) = delete;
	Gravity(Gravity&& _Other) noexcept = delete;
	Gravity& operator=(const Gravity& _Other) = delete;
	Gravity& operator=(Gravity&& _Other) noexcept = delete;

	static void GravityOn(float _Delta);

	static void GravityOff();

protected:

private:
	static float Acceleration;

	static bool GravityCheck;

	// constrcuter destructer
	Gravity();
	~Gravity();
};

