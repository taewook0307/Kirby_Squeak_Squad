#pragma once

class Default Class
{
public:
	// constrcuter destructer
	Default Class();
	~Default Class();

	// delete Function
	Default Class(const Default Class& _Other) = delete;
	Default Class(Default Class&& _Other) noexcept = delete;
	Default Class& operator=(const Default Class& _Other) = delete;
	Default Class& operator=(Default Class&& _Other) noexcept = delete;

protected:

private:

};

