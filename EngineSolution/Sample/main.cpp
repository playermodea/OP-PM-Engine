#include "glm/glm.hpp"

#include "GameCore.h"
#include "Project.h"
#include "Scene.h"
#include "Sound.h"
#include "RendererFactory.h"
#include "CameraObject.h"
#include "TestObject.h"
#include "MeshRendererComponent.h"
#include "FreeMoveComponent.h"
#include "TestToolComponent.h"
#include "BoxColliderComponent.h"

class SampleProject : public Project
{
private:

public:
	SampleProject() {};
	~SampleProject() {};

	virtual void ProjectInit(GraphicAPI mode) override;
};

void SampleProject::ProjectInit(GraphicAPI mode)
{
	Project::ProjectInit(mode);

	//////////////////////// Scene 생성
	// 1번 Scene : 전체적인 기본 소개
	// 2번 Scene : Transform 소개1
	// 3번 Scene : Transform 소개2 (자식 포함)
	// 4번 Scene : Collision 소개
	Scene* SampleScene_1 = new Scene("BasicScene");
	Scene* SampleScene_2 = new Scene("TransformScene1");
	Scene* SampleScene_3 = new Scene("TransformScene2");
	Scene* SampleScene_4 = new Scene("CollisionScene");

	//조작설명
	{
		// 마우스 + WASD - 카메라 이동
		// 키보드 방향키 - TestToolComponent가 부착된 오브젝트 앞뒤좌우 이동
		// 키보드 QE - TestToolComponent가 부착된 오브젝트 좌우 회전
		// F - TestToolComponent가 부착된 오브젝트가 Scene에 존재하면 있을 시 Music 재생
		// G - TestToolComponent가 부착된 오브젝트가 Scene에 존재하면 Music 재생 중단
		// 숫자 1번 - 이전 Scene으로 이동
		// 숫자 2번 - 다음 Scene으로 이동
	}

	// 사운드 세팅
	Sound* TestSound = new Sound("../../Resources/Sound/Music.mp3", true);

	//////////////////////// SampleScene_1 구성
	{
		// 메인 카메라
		GameObject* Scene1_MainCam = new CameraObject("Camera", "MainCamera");
		Component* Scene1_MoveCamComp = new FreeMoveComponent();
		Scene1_MainCam->AddComponent(Scene1_MoveCamComp);

		// GameObject
		GameObject* Scene1_TestObject1 = new TestObject("TestObject_Name1", "TestTag");
		Scene1_TestObject1->GetTransform()->SetWorldPos(glm::vec3(-10.0f, -1.0f, -20.0f));
		Component* Scene1_TestRenderer1 = RendererFactory::GetRenderer()->CreateMesh("../../Resources/Obj/plane.obj", "../../Resources/Texture/bricks.jpg");
		Scene1_TestObject1->AddComponent(Scene1_TestRenderer1);

		GameObject* Scene1_TestObject2 = new TestObject("TestObject_Name2", "TestTag");
		Scene1_TestObject2->GetTransform()->SetWorldPos(glm::vec3(-10.0f, 4.0f, -20.0f));
		Component* Scene1_TestRenderer2 = RendererFactory::GetRenderer()->CreateMesh("../../Resources/Obj/computer.obj", "../../Resources/Texture/computer.jpg");
		Scene1_TestObject2->AddComponent(Scene1_TestRenderer2);

		GameObject* Scene1_TestObject3 = new TestObject("TestObject_Name3", "TestTag");
		Scene1_TestObject3->GetTransform()->SetWorldPos(glm::vec3(10.0f, -1.0f, -20.0f));
		Component* Scene1_TestRenderer3 = RendererFactory::GetRenderer()->CreatePlaneMesh();
		Scene1_TestObject3->AddComponent(Scene1_TestRenderer3);

		GameObject* Scene1_TestObject4 = new TestObject("TestObject_Name4", "TestTag");
		Scene1_TestObject4->GetTransform()->SetWorldPos(glm::vec3(10.0f, 5.0f, -20.0f));
		Component* Scene1_TestRenderer4 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene1_TestObject4->AddComponent(Scene1_TestRenderer4);

		GameObject* Scene1_TestObject5 = new TestObject("TestObject_Name5", "TestTag");
		Scene1_TestObject5->GetTransform()->SetWorldPos(glm::vec3(15.0f, 5.0f, -20.0f));
		Component* Scene1_TestRenderer5 = RendererFactory::GetRenderer()->CreateSphereMesh();
		Scene1_TestObject5->AddComponent(Scene1_TestRenderer5);

		GameObject* Scene1_TestObject6 = new TestObject("TestObject_Name6", "TestTag");
		Scene1_TestObject6->GetTransform()->SetWorldPos(glm::vec3(15.0f, 5.0f, -15.0f));
		Component* Scene1_TestRenderer6 = RendererFactory::GetRenderer()->CreateCylinderMesh();
		Scene1_TestObject6->AddComponent(Scene1_TestRenderer6);

		GameObject* Scene1_TestObject7 = new TestObject("TestObject_Name7", "TestTag");
		Component* SoundTester = new TestToolComponent();
		Scene1_TestObject6->AddComponent(SoundTester);

		// Scene에 GameObject 추가 및 프로젝트에 Scene 추가
		SampleScene_1->AddGameObject(Scene1_MainCam);
		SampleScene_1->AddGameObject(Scene1_TestObject1);
		SampleScene_1->AddGameObject(Scene1_TestObject2);
		SampleScene_1->AddGameObject(Scene1_TestObject3);
		SampleScene_1->AddGameObject(Scene1_TestObject4);
		SampleScene_1->AddGameObject(Scene1_TestObject5);
		SampleScene_1->AddGameObject(Scene1_TestObject6);
		SampleScene_1->AddGameObject(Scene1_TestObject7);

		AddScene(SampleScene_1);
		//////////////////////// SampleScene_1 구성 끝
	}

	//////////////////////// SampleScene_2 구성
	{
		// 메인 카메라
		GameObject* Scene2_MainCam = new CameraObject("Camera", "MainCamera");
		Component* Scene2_MoveCamComp = new FreeMoveComponent();
		Scene2_MainCam->AddComponent(Scene2_MoveCamComp);

		// GameObject
		GameObject* Scene2_TestObject1 = new TestObject("TestObject_Name1", "TestTag");
		Scene2_TestObject1->GetTransform()->SetWorldPos(glm::vec3(-10.0f, -1.0f, -20.0f));
		Component* Scene2_TestRenderer1 = RendererFactory::GetRenderer()->CreateMesh("../../Resources/Obj/plane.obj", "../../Resources/Texture/bricks2.jpg");
		Scene2_TestObject1->AddComponent(Scene2_TestRenderer1);

		GameObject* Scene2_TestObject2 = new TestObject("TestObject_Name2", "TestTag");
		Scene2_TestObject2->GetTransform()->SetWorldPos(glm::vec3(-10.0f, 5.0f, -20.0f));
		Component* Scene2_TestRenderer2 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene2_TestObject2->AddComponent(Scene2_TestRenderer2);
		Component* Scene2_TestMoveComp = new TestToolComponent();
		Scene2_TestObject2->AddComponent(Scene2_TestMoveComp);

		//  Scene에 GameObject 추가 및 프로젝트에 Scene 추가
		SampleScene_2->AddGameObject(Scene2_MainCam);
		SampleScene_2->AddGameObject(Scene2_TestObject1);
		SampleScene_2->AddGameObject(Scene2_TestObject2);

		AddScene(SampleScene_2);
		//////////////////////// SampleScene_2 구성 끝
	}

	//////////////////////// SampleScene_3 구성
	{
		// 메인 카메라
		GameObject* Scene3_MainCam = new CameraObject("Camera", "MainCamera");
		Component* Scene3_MoveCamComp = new FreeMoveComponent();
		Scene3_MainCam->AddComponent(Scene3_MoveCamComp);

		// GameObject
		GameObject* Scene3_TestObject1 = new TestObject("TestObject_Name1", "TestTag");
		Scene3_TestObject1->GetTransform()->SetWorldPos(glm::vec3(10.0f, -1.0f, -20.0f));
		Component* Scene3_TestRenderer1 = RendererFactory::GetRenderer()->CreateMesh("../../Resources/Obj/plane.obj", "../../Resources/Texture/bricks2.jpg");
		Scene3_TestObject1->AddComponent(Scene3_TestRenderer1);

		// 부모
		GameObject* Scene3_TestObject2 = new TestObject("TestObject_Name2", "TestTag");
		Scene3_TestObject2->GetTransform()->SetWorldPos(glm::vec3(10.0f, 5.0f, -20.0f));
		Component* Scene3_TestRenderer2 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene3_TestObject2->AddComponent(Scene3_TestRenderer2);
		Component* Scene3_TestMoveComp = new TestToolComponent();
		Scene3_TestObject2->AddComponent(Scene3_TestMoveComp);

		// 자식
		GameObject* Scene3_TestObject3 = new TestObject("TestObject_Name3", "TestTag");
		Scene3_TestObject3->GetTransform()->SetWorldPos(glm::vec3(7.0f, 7.0f, -20.0f));
		Component* Scene3_TestRenderer3 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene3_TestObject3->AddComponent(Scene3_TestRenderer3);
		Scene3_TestObject2->AddChild(Scene3_TestObject3);

		//  Scene에 GameObject 추가 및 프로젝트에 Scene 추가
		SampleScene_3->AddGameObject(Scene3_MainCam);
		SampleScene_3->AddGameObject(Scene3_TestObject1);
		SampleScene_3->AddGameObject(Scene3_TestObject2);
		SampleScene_3->AddGameObject(Scene3_TestObject3);

		AddScene(SampleScene_3);
		//////////////////////// SampleScene_3 구성 끝
	}

	//////////////////////// SampleScene_4 구성
	{
		// 메인 카메라
		GameObject* Scene4_MainCam = new CameraObject("Camera", "MainCamera");
		Component* Scene4_MoveCamComp = new FreeMoveComponent();
		Scene4_MainCam->AddComponent(Scene4_MoveCamComp);

		// GameObject
		GameObject* Scene4_TestObject1 = new TestObject("TestObject_Name1", "TestTag");
		Scene4_TestObject1->GetTransform()->SetWorldPos(glm::vec3(0.0f, -1.0f, -20.0f));
		Component* Scene4_TestRenderer1 = RendererFactory::GetRenderer()->CreateMesh("../../Resources/Obj/plane.obj", "../../Resources/Texture/bricks.jpg");
		Scene4_TestObject1->AddComponent(Scene4_TestRenderer1);

		GameObject* Scene4_TestObject2 = new TestObject("TestObject_Name2", "TestTag");
		Scene4_TestObject2->GetTransform()->SetWorldPos(glm::vec3(5.0f, 7.0f, -20.0f));
		Component* Scene4_TestRenderer2 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene4_TestObject2->AddComponent(Scene4_TestRenderer2);
		Component* Scene4_TestMoveComp = new TestToolComponent();
		Scene4_TestObject2->AddComponent(Scene4_TestMoveComp);
		Component* TestCollision_1 = new BoxColliderComponent();
		Scene4_TestObject2->AddComponent(TestCollision_1);

		GameObject* Scene4_TestObject3 = new TestObject("TestObject_Name3", "TestTag");
		Scene4_TestObject3->GetTransform()->SetWorldPos(glm::vec3(0.0f, 7.0f, -20.0f));
		Component* Scene4_TestRenderer3 = RendererFactory::GetRenderer()->CreateCubeMesh();
		Scene4_TestObject3->AddComponent(Scene4_TestRenderer3);
		Component* TestCollision_2 = new BoxColliderComponent();
		Scene4_TestObject3->AddComponent(TestCollision_2);

		//  Scene에 GameObject 추가 및 프로젝트에 Scene 추가
		SampleScene_4->AddGameObject(Scene4_MainCam);
		SampleScene_4->AddGameObject(Scene4_TestObject1);
		SampleScene_4->AddGameObject(Scene4_TestObject2);
		SampleScene_4->AddGameObject(Scene4_TestObject3);

		AddScene(SampleScene_4);
		//////////////////////// SampleScene_4 구성 끝
	}
}

int main()
{ 
	SampleProject* TestProj = new SampleProject();
	GameCore::Instance()->Init("PMEngine Demo", 800, 600, TestProj);
	GameCore::Instance()->StartEngine();

	return 0;
}