#include "pch.h"
#include "12. AmbientDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"

void AmbientDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"09. Lighting_Ambient.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f,0.f,-10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	//Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		//Texture
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	//Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f,0.f,2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh2 = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh2);
	}
	{
		//Texture
		auto texture2 = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture2);
	}

	RENDER->Init(_shader);
}

void AmbientDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	//조명
	Vec4 lightAmbient{ 0.2f, 0.f, 0.f, 1.f };
	_shader->GetVector("LightAmbient")->SetFloatVector((float*)&lightAmbient);

	{
		//모든 색을 다 받아주는 재질
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj->Update();
	}

	{
		//모든 색을 다 받아주는 재질
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj2->Update();
	}
	
}

void AmbientDemo::Render()
{
	
}
