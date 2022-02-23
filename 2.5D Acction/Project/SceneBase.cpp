#include "SceneBase.h"

CSceneBase::CSceneBase() :
	m_bEnd(false),
	m_NextSceneNo(0){
	memset(m_SelectNo, 0, sizeof(m_SelectNo));
}