#pragma once
#include "SceneTitle.h"
#include "SceneMenu.h"
#include "SceneSelectOpponent.h"
#include "SceneCharacterSelect.h"
#include "SceneBattle.h"
#include "SceneOption.h"

class CSceneFactory {
private:

public:
	CSceneBase* CreateSceneFactory(SceneNo no)
	{
		switch (no)
		{
		case SCENENO_TITLE:
			return new CSceneTitle;
			break;
		case SCENENO_MENU:
			return new CSceneMenu;
			break;
		case SCENENO_OPPOENT:
			return new CSceneSelectOpponent;
			break;
		case SCENENO_CHARACTERSELECT:
			return new CSceneCharacterSelect;
			break;
		case SCENENO_BATTLE:
			return new CSceneBattle;
			break;
		case SCENENO_OPTION:
			return new CSceneOption;
			break;
		default:
			return nullptr;
			break;
		}
		return nullptr;
	}
};