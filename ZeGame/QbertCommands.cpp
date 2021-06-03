#include "QbertCommands.h"

#include "QbertComponent.h"

#pragma region Move
qbert::Move::Move(QbertComponent* pQbertComp,id movePosition)
	:m_MovePosition(movePosition)
{
	m_pQbert = pQbertComp;
}

qbert::Move::~Move()
{
	
}

void qbert::Move::Execute()
{
	m_pQbert->Move(m_MovePosition);
}

void qbert::Move::Undo()
{
	
}
#pragma endregion 

//#pragma region MoveLeftDown
//qbert::MoveLeftDown::MoveLeftDown(QbertComponent* pQbertComp)
//{
//	m_pQbert = pQbertComp;
//}
//
//qbert::MoveLeftDown::~MoveLeftDown()
//{
//}
//
//void qbert::MoveLeftDown::Execute()
//{
//	m_pQbert->MoveLeftDown();
//}
//
//void qbert::MoveLeftDown::Undo()
//{
//}
//#pragma endregion 
//
//#pragma region MoveRightUp
//qbert::MoveRightUp::MoveRightUp(QbertComponent* pQbertComp)
//{
//	m_pQbert = pQbertComp;
//}
//
//qbert::MoveRightUp::~MoveRightUp()
//{
//}
//
//void qbert::MoveRightUp::Execute()
//{
//	m_pQbert->MoveRightUp();
//}
//
//void qbert::MoveRightUp::Undo()
//{
//}
//#pragma endregion
//
//#pragma region MoveRightDown
//
//qbert::MoveRightDown::MoveRightDown(QbertComponent* pQbertComp)
//{
//	m_pQbert = pQbertComp;
//}
//
//qbert::MoveRightDown::~MoveRightDown()
//{
//}
//
//void qbert::MoveRightDown::Execute()
//{
//	m_pQbert->MoveRightDown();
//}
//
//void qbert::MoveRightDown::Undo()
//{
//}
//
//#pragma endregion 

