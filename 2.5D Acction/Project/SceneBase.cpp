#include "SceneBase.h"

CSceneBase::CSceneBase() :
	m_bEnd(false),
	m_NextSceneNo(SceneNo::SCENENO_TITLE) {
	memset(m_SelectNo, 0, sizeof(m_SelectNo));
}