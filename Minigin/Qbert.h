#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "Observer.h"

class Qbert final : public BaseComponent
{
public:
	Qbert(Subject* pLifeSubject, Subject* pScoreSubject);
	~Qbert();

	void Die();
	void GetPoint();
	void Update(float) override {};
	void Render() const override {};

	Qbert(const Qbert& other) = delete;
	Qbert(Qbert&& other) = delete;
	Qbert& operator=(const Qbert& other) = delete;
	Qbert& operator=(Qbert&& other) = delete;

private:
	Subject* m_pLifeSubject;
	Subject* m_pScoreSubject;
};

