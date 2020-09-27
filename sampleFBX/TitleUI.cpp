/**
 * @file TitleUI
 * @brief �^�C�g����UI���b�V���N���X
 */
#include "TitleUI.h"
#include "UIMesh.h"

#define	TEXTURE_PressSpace	L"data/texture/Press_Space.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_shooting	L"data/texture/shooting.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

TitleUI::TitleUI()
{
}

TitleUI::~TitleUI()
{
}

HRESULT TitleUI::Init()
{
	m_RogoMesh = new GameObject();
	m_RogoMesh->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_shooting);
	m_StartMesh = new GameObject();
	m_StartMesh->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos( 0,-200,0 )->SetTexture(TEXTURE_PressSpace);
	GameObject::Init();

	return E_NOTIMPL;
}

void TitleUI::Uninit()
{
	m_StartMesh->Uninit();
	m_RogoMesh->Uninit();
	GameObject::Uninit();
	delete m_StartMesh;
	delete m_RogoMesh;
}

void TitleUI::Update()
{
	m_RogoMesh->Update();
	m_StartMesh->Update();
	GameObject::Update();
}

void TitleUI::Draw()
{
	m_RogoMesh->Draw();
	m_StartMesh->Draw();
	GameObject::Draw();
}


// EOF