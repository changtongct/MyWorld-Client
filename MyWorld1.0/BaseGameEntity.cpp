#include "BaseGameEntity.h"

int BaseGameEntity::m_iNextValidID = 0;

void BaseGameEntity::SetID(int val) {
	m_ID = val;
	m_iNextValidID = m_ID + 1;
}
