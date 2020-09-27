//=======================================================================================
//
//	  DirectX11 Graphics �N���X��` [Graphics.h]
//
//=======================================================================================
#pragma once
#include "Main.h"

enum EBlendState {
	BS_NONE = 0,		// ��������������
	BS_ALPHABLEND,		// ����������
	BS_ADDITIVE,		// ���Z����
	BS_SUBTRACTION,		// ���Z����

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,	// �J�����O���Ȃ�
	CULLMODE_CW,		// �O�ʃJ�����O
	CULLMODE_CCW,		// �w�ʃJ�����O

	MAX_CULLMODE
};
//// �V�F�[�_�ɓn���l
//struct SHADER_GLOBAL {
//	XMMATRIX	mWVP;		// ���[���h�~�r���[�~�ˉe�s��(�]�u�s��)
//	XMMATRIX	mW;			// ���[���h�s��(�]�u�s��)
//	XMMATRIX	mTex;		// �e�N�X�`���s��(�]�u�s��)
//};
//struct SHADER_GLOBAL2 {
//	XMVECTOR	vEye;		// ���_���W
//	// ����
//	XMVECTOR	vLightDir;	// ��������
//	XMVECTOR	vLa;		// �����F(�A���r�G���g)
//	XMVECTOR	vLd;		// �����F(�f�B�t���[�Y)
//	XMVECTOR	vLs;		// �����F(�X�y�L����)
//	// �}�e���A��
//	XMVECTOR	vAmbient;	// �A���r�G���g�F(+�e�N�X�`���L��)
//	XMVECTOR	vDiffuse;	// �f�B�t���[�Y�F
//	XMVECTOR	vSpecular;	// �X�y�L�����F(+�X�y�L�������x)
//	XMVECTOR	vEmissive;	// �G�~�b�V�u�F
//};

class SceneManager;
class CGraphics
{
private:
	static ID3D11Device*			m_pDevice;				// �f�o�C�X
	static ID3D11DeviceContext*		m_pDeviceContext;		// �f�o�C�X �R���e�L�X�g
	static IDXGISwapChain*			m_pSwapChain;			// �X���b�v�`�F�[��
	static ID3D11RenderTargetView*	m_pRenderTargetView;	// �t���[���o�b�t�@
	static ID3D11Texture2D*			m_pDepthStencilTexture;	// Z�o�b�t�@�p������
	static ID3D11DepthStencilView*	m_pDepthStencilView;	// Z�o�b�t�@
	static UINT						m_uSyncInterval;		// �������� (0:��, 1:�L)
	static ID3D11RasterizerState*	m_pRs[MAX_CULLMODE];	// ���X�^���C�U �X�e�[�g
	static ID3D11BlendState*		m_pBlendState[MAX_BLENDSTATE];// �u�����h �X�e�[�g
	static ID3D11DepthStencilState*	m_pDSS[2];				// Z�o�b�t�@/�X�e���V�� �X�e�[�g
	static ID3D11SamplerState*		m_pSamplerState;		// �e�N�X�`�� �T���v��

private:
	static HRESULT CreateBackBuffer();
	static void ReleaseBackBuffer();

public:
	static HRESULT Init(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	static void Uninit();
	static void Update();
	static void Draw(SceneManager* pScene);

	static ID3D11Device* GetDevice() { return m_pDevice; }
	static ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }
	static ID3D11DeviceContext* GetContext() { return m_pDeviceContext; }
	static ID3D11SamplerState* GetSamplerState() { return m_pSamplerState; }
	static void SetZBuffer(bool bEnable);
	static void SetZWrite(bool bEnable);
	static void SetBlendState(int nBlendState);
	static void SetCullMode(int nCullMode);
};
