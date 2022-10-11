#pragma once

#include <vector>
#include <Windows.h>

#include "GameObject.h"

using namespace std;

class Scene
{
private:
	bool IsStart;
	string SceneName;
	LARGE_INTEGER NowFrameCounter;
	LARGE_INTEGER PrevFrameCounter;

	vector<GameObject*> GameObjectArray;

public:
	Scene(string sceneName);
	~Scene();

	void Start();
	void AddGameObject(GameObject* gameObj);
	void SceneLoop(double perFrame);
	void CollisionCheck();

	// Setter
	void SetIsStart(bool value)
	{ 
		IsStart = value; 
	}

	// Getter
	bool GetIsStart() 
	{ 
		return IsStart; 
	}
};