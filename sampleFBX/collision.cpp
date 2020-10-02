/**
 * @file Collision
 * @brief �����蔻��N���X
 */
#include "collision.h"
#include "GameObject.h"
#include "ModelData.h"
#include "MyMath.h"

std::unordered_map<int, Collision*> Collision::m_List;
static bool m_isViewCol = true;

/**
 * @breif �R���X�g���N�^
 */
Collision::Collision()
{
	static int num = 0;
	id = num;
	m_List[num] = this;
	num++;
	m_isActive = true;
	m_tag = 0;
	m_offsetPos = Vector3();
	m_offsetSize = Vector3(1,1,1);
}

/**
 * @brief �f�X�g���N�^
 */
Collision::~Collision()
{
	m_List.erase(id);
}

/**
 * @breif ����������
 * @return �Ȃ�
 */
HRESULT Collision::Init()
{
	m_transform = &m_Parent->GetTransform();
	m_tag = m_Parent->GetTag();
	Vector3& pos = m_transform->position;
	Vector3 size = m_offsetSize * m_transform->scale;

#ifdef _DEBUG
	XMFLOAT3 halfsize(size.x, size.y, size.z);
	//XMFLOAT3 halfsize(50, 50, 50);
	m_box.Init(&halfsize);
	XMFLOAT4X4 mtx = m_box.GetWorld();
	mtx._41 = pos.x;
	mtx._42 = pos.y;
	mtx._43 = pos.z;
	m_box.SetWorld(mtx);

	XMFLOAT4 color = XMFLOAT4(0,0,1,0.5f);
	m_box.SetColor(&color);
#endif

	return S_OK;
}

/**
 * @breif �I��
 * @return �Ȃ�
 */
void Collision::Uninit()
{
#ifdef _DEBUG
	m_box.Uninit();
#endif
}

/**
 * @breif �X�V
 * @return �Ȃ�
 */
void Collision::Update()
{
	Vector3& pos = m_transform->position;
#ifdef _DEBUG
	XMFLOAT4X4 mtx = m_box.GetWorld();
	mtx._41 = pos.x;
	mtx._42 = pos.y;
	mtx._43 = pos.z;
	m_box.SetWorld(mtx);
#endif
}

/**
 * @breif �`��
 * @return �Ȃ�
 */
void Collision::Draw()
{
#if _DEBUG

	ImGui::Begin("collision");
	//ImGui::Text("fps: %.2f", pos.x);
	//static char text1[8] = "";
	//ImGui::InputText("textbox 1", text1, sizeof(text1));
	//ImGui::Text("fps: %.2f", pos.x);
	//static char text1[8] = "";
	//ImGui::InputText("textbox 1", text1, sizeof(text1));
	//ImGui::SliderFloat("slider 1", &pos.x, 0.0f, 1.0f);
	//static bool show_another_window = false;
	//ImGui::Begin("Another Window", &show_another_window);
	//ImGui::Text("Hello from another window!");

	ImGui::Checkbox("view", &m_isViewCol);

	ImGui::End();
#endif
}

/**
 * @breif �`��
 * @return �Ȃ�
 */
void Collision::DrawAlpha()
{
#ifdef _DEBUG
	if(m_isViewCol == true)
	m_box.Draw();
#endif
}

/**
 * @breif �^�O�̐ݒ�
 * @return �Ȃ�
 */
void Collision::SetTag(int tag)
{
	m_tag = tag;
}

/**
 * @breif ���X�g�ɂ���S�ẴI�u�W�F�N�g���������Ă��邩���肷��
 * @return �Ȃ�
 */
void Collision::Check()
{
	for (std::unordered_map<int, Collision*>::iterator col = m_List.begin(), colend = m_List.end(); col != colend; ++col) {
		for (std::unordered_map<int, Collision*>::iterator othor = m_List.begin(), e = colend; othor != e; ++othor) {

			if (othor == col) {
				continue; 
			}
			if (col->second->m_isActive == false || othor->second->m_isActive == false) {
				continue;
			}

			Vector3 size = col->second->m_transform->scale *  col->second->m_offsetSize;
			Vector3 othorsize = othor->second->m_transform->scale *  othor->second->m_offsetSize;

			if (CheckBox(col->second->m_transform->position, size, othor->second->m_transform->position, othorsize)) {
				col->second->m_Parent->OnCollisionEnter((othor->second->m_Parent));
			}
		}
	}
}

/**
 * @breif ���W�̐ݒ�
 * @return ����
 */
Collision * Collision::SetPos(Vector3 position)
{
	m_offsetPos = position;
	return this;
}

/**
 * @breif �傫���̐ݒ�
 * @return ����
 */
Collision * Collision::SetSize(Vector3 Size)
{
	m_offsetSize = Size;
	return this;
}
/**
 * @breif ���f���̎�ސݒ�
	 * @param[in] kind ���f���̎��
 * @return ����
 */
Collision * Collision::SetModelKind(int modelkind)
{
	m_offsetSize =  ModelData::GetSize(modelkind);

	return this;
}

/**
 * @breif �^�O�̎擾
 * @return �^�O�̐��l
 */
int Collision::GetTag()
{
	return m_tag;
}

/**
 * @breif �o�E���f�B���O�{�b�N�X�ł̓����蔻��̔�r
 * @return �������Ă����true
 */
bool Collision::CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize)
{
	bool isHit = false;

	float& Ax = mypos.x;
	float& Ay = mypos.y;
	float& Az = mypos.z;
	float& Aw = halfsize.x;
	float& Ah = halfsize.y;
	float& Ad = halfsize.z;
	float& Bx = othorPos.x;
	float& By = othorPos.y;
	float& Bz = othorPos.z;
	float& Bw = othorhalsize.x;
	float& Bh = othorhalsize.y;
	float& Bd = othorhalsize.z;
	isHit = Ax - Aw <= Bx + Bw &&
		Bx - Bw <= Ax + Aw &&
		Ay - Ah <= By + Bh &&
		By - Bh <= Ay + Ah &&
		Az - Ad <= Bz + Bd &&
		Bz - Bd <= Az + Ad;
	return isHit;
}

/**
 * @breif �����蔻��̃��X�g�̏�����
 * @return �Ȃ�
 */
void Collision::Clear()
{
	m_List.clear();
}

// EOF