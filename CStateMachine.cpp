#include "pch.h"
#include "CStateMachine.h"

#include "CState.h"

CStateMachine::CStateMachine()
	: CComponent(COMPONENT_TYPE::STATE_MACHINE)
	, m_CurState(nullptr)
{

}

CStateMachine::CStateMachine(const CStateMachine& _Other)
	: CComponent(_Other)
	, m_CurState(nullptr)
{
	map<wstring, CState*>::const_iterator iter = _Other.m_mapState.begin();
	for (; iter != _Other.m_mapState.end(); ++iter)
	{
		CState* pCloneState = iter->second->Clone();
		AddState(iter->first, pCloneState);
	}
		
	if (nullptr != _Other.m_CurState)
	{
		ChangeState(_Other.m_CurState->GetName());
	}
}

CStateMachine::~CStateMachine()
{
	Release_Map(m_mapState);
}


void CStateMachine::FinalTick()
{
	if (nullptr == m_CurState)
		return;

	m_CurState->FinalTick();
}


void CStateMachine::AddState(const wstring& _StateName, CState* _State)
{
	CState* pState = FindState(_StateName);
	assert(pState == nullptr);

	_State->SetName(_StateName);
	m_mapState.insert(make_pair(_StateName, _State));
	_State->m_Owner = this;
}

CState* CStateMachine::FindState(const wstring& _StateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_StateName);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CStateMachine::ChangeState(const wstring& _StateName)
{
	CState* pNextState = FindState(_StateName);

	// ���� ���¸� ����������(Exit)
	if (nullptr != m_CurState)
	{
		m_CurState->Exit();
	}

	// ���ο� ���¸� ����Ű��
	m_CurState = pNextState;
	assert(m_CurState);

	m_CurState->SetName(_StateName);

	// ���ο� ���·� ����(Enter) �Ѵ�.
	m_CurState->Enter();
}


