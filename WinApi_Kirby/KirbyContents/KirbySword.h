#pragma once
#include "KirbyNormal.h"

class KirbySword : public KirbyNormal
{
public:
	// constrcuter destructer
	KirbySword();
	~KirbySword();

	// delete Function
	KirbySword(const KirbySword& _Other) = delete;
	KirbySword(KirbySword&& _Other) noexcept = delete;
	KirbySword& operator=(const KirbySword& _Other) = delete;
	KirbySword& operator=(KirbySword&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;

	void Render() override;

	void Release() override;
};

