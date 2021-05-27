#pragma once
#include "Command.h"


namespace qbert
{
	class QbertComponent;
	
	class Move : public dae::Command
	{
	public:
		Move(QbertComponent* pQbertComp, int movePosition);
		~Move() override;
		void Execute() override;
		void Undo() override;
	private:
		QbertComponent* m_pQbert;
		int m_MovePosition;
	};
	/*class MoveRightUp : public dae::Command
	{
	public:
		MoveRightUp(QbertComponent* pQbertComp);
		~MoveRightUp() override;
		void Execute() override;
		void Undo() override;
	private:
		QbertComponent* m_pQbert;
	};
	class MoveLeftDown : public dae::Command
	{
	public:
		MoveLeftDown(QbertComponent* pQbertComp);
		~MoveLeftDown() override;
		void Execute() override;
		void Undo() override;
	private:
		QbertComponent* m_pQbert;
	};
	class MoveRightDown : public dae::Command
	{
	public:
		MoveRightDown(QbertComponent* pQbertComp);
		~MoveRightDown() override;
		void Execute() override;
		void Undo() override;
	private:
		QbertComponent* m_pQbert;
	};*/
}

