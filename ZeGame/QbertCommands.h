#pragma once
#include "Command.h"
#include "Helpers.h"


namespace qbert
{
	class QbertComponent;
	
	class Move final : public dae::Command
	{
	public:
		Move(QbertComponent* pQbertComp, id movePosition);
		~Move() override;
		void Execute() override;
		void Undo() override;
	private:
		QbertComponent* m_pQbert;
		id m_MovePosition;
		//dae::SoundSystem* m_SoundSystem;
		//const std::string& m_Path;
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

