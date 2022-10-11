#include "Scene.h"
#include "RenderUtil.h"
#include "ColliderComponent.h"

Scene::Scene(string sceneName) : SceneName(sceneName)
{
	QueryPerformanceCounter(&PrevFrameCounter);

	IsStart = true;
}

Scene::~Scene()
{
	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		delete *iter;
	}

	GameObjectArray.clear();
}

void Scene::AddGameObject(GameObject* gameObj)
{
	GameObjectArray.push_back(gameObj);
}

void Scene::Start()
{
	RenderUtil::SetMainCamera(GameObjectArray);

	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		GameObject* gameObj = *iter;
		gameObj->Start();
	}
}

void Scene::SceneLoop(double perframe)
{
	QueryPerformanceCounter(&NowFrameCounter);

	double FrameTimeDistance = (NowFrameCounter.QuadPart - PrevFrameCounter.QuadPart);

	// FixedUpdate
	if (FrameTimeDistance > perframe)
	{
		for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
		{
			GameObject* gameObj = *iter;
			gameObj->FixedUpdate();
		}

		PrevFrameCounter = NowFrameCounter;
	}

	// Collision Checking
	CollisionCheck();

	// OnCollision
	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		GameObject* gameObj = *iter;
		gameObj->OnCollision();
	}

	// Update
	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		GameObject* gameObj = *iter;
		gameObj->Update();
	}

	// LateUpdate
	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		GameObject* gameObj = *iter;
		gameObj->LateUpdate();
	}

	// Render
	for (vector<GameObject*>::iterator iter = GameObjectArray.begin(); iter != GameObjectArray.end(); iter++)
	{
		GameObject* gameObj = *iter;
		gameObj->Render();
	}
}

void Scene::CollisionCheck()
{
	for (vector<GameObject*>::iterator iter_1 = GameObjectArray.begin(); iter_1 != GameObjectArray.end(); iter_1++)
	{
		GameObject* gameObj_1 = *iter_1;
		vector<Component*> compArray_1 = gameObj_1->GetCompArray();

		for (vector<Component*>::iterator iter_2 = compArray_1.begin(); iter_2 != compArray_1.end(); iter_2++)
		{
			Component* comp_1 = *iter_2;

			if (comp_1->GetCompType() == "Collider")
			{
				for (vector<GameObject*>::iterator iter_3 = (iter_1 + 1); iter_3 != GameObjectArray.end(); iter_3++)
				{
					GameObject* gameObj_2 = *iter_3;
					vector<Component*> compArray_2 = gameObj_2->GetCompArray();

					for (vector<Component*>::iterator iter_4 = compArray_2.begin(); iter_4 != compArray_2.end(); iter_4++)
					{
						Component* comp_2 = *iter_4;
						if (comp_2->GetCompType() == "Collider")
						{
							static_cast<ColliderComponent*>(comp_1)->SetCollisionState(static_cast<ColliderComponent*>(comp_1)->GetCollision(static_cast<ColliderComponent*>(comp_2)));
							static_cast<ColliderComponent*>(comp_2)->SetCollisionState(static_cast<ColliderComponent*>(comp_2)->GetCollision(static_cast<ColliderComponent*>(comp_1)));
						}
					}
				}
			}
		}
	}
}