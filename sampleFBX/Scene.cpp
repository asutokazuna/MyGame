#include "Scene.h"
#include "Graphics.h"

// �ÓI�����o
CScene*	CScene::m_pScene = nullptr;

// �R���X�g���N�^
CScene::CScene() : m_FPS(0)
{
	m_szDebug[0] = _T('\0');
}

// �f�X�g���N�^
CScene::~CScene()
{

}

// ������
HRESULT CScene::Init()
{
	HRESULT hr = S_OK;
	
	for (auto& obj : m_pObj) {
		obj->Awake();
	}

	for (auto& obj : m_pObj) {
		obj->Init();
	}

	return hr;
}

// �I������
void CScene::Uninit()
{
	// �S�I�u�W�F�N�g�I��
	for (auto& obj : m_pObj) {
		obj->Uninit();
	}
}

// �X�V
void CScene::Update()
{
	// �S�I�u�W�F�N�g�X�V
	for (auto& obj : m_pObj) {
		obj->Update();
	}
	for (auto& obj : m_pObj) {
		obj->LateUpdate();
	}

}

// �`��
void CScene::Draw()
{
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf_s(str, _countof(str), _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	// �J�������f
	//if (m_pCamera) {
	//	//m_pCamera->Draw();
	//}

	// �O�ʃJ�����O (FBX�͕\�������]���邽��)
	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	CGraphics::SetZWrite(true);

	for (auto& obj : m_pObj) {
		obj->Draw();
	}

	CGraphics::SetZWrite(false);
	CGraphics::SetBlendState(BS_ALPHABLEND);	// �������`��
	for (auto& obj : m_pObj) {
		obj->DrawAlpha();
	}
}

// �V�[���ؑ�
void CScene::Set(CScene* pScene)
{
	// �V�[���̏I��
	if (m_pScene) {
		m_pScene->Uninit();
	}

	// �V�[������
	m_pScene = pScene;

	// �V�[���̊J�n
	if (m_pScene) {
		m_pScene->Init();
	}
}

//=======================================================================================
//	End of File
//=======================================================================================
