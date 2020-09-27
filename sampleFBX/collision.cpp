/**
 * @file Collision
 * @brief “–‚½‚è”»’èƒNƒ‰ƒX
 */
#include "collision.h"
#include "GameObject.h"

std::unordered_map<int, Collision*> Collision::m_List;
static bool m_isViewCol = true;

Collision::Collision()
{
	static int num = 0;
	id = num;
	m_List[num] = this;
	num++;
	m_isActive = true;
	m_tag = 0;
}

Collision::~Collision()
{
	m_List.erase(id);
}

HRESULT Collision::Init()
{
	//pos = m_Parent->GetTransform().position;
	//size = m_Parent->GetTransform().scale;
	//m_tag = 0;
	//m_isActive = true;

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

void Collision::Uninit()
{
#ifdef _DEBUG
	m_box.Uninit();
#endif
}

void Collision::Update()
{
	pos = m_Parent->GetTransform().position;
#ifdef _DEBUG
	XMFLOAT4X4 mtx = m_box.GetWorld();
	mtx._41 = pos.x;
	mtx._42 = pos.y;
	mtx._43 = pos.z;
	m_box.SetWorld(mtx);
#endif
}

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

void Collision::DrawAlpha()
{
#ifdef _DEBUG
	if(m_isViewCol == true)
	m_box.Draw();
#endif
}

void Collision::SetTag(int tag)
{
	m_tag = tag;
}

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

			if (CheckBox(col->second->pos, col->second->size, othor->second->pos, othor->second->size)) {
				col->second->Check((othor->second));
			}
		}
	}
}

void Collision::Check(Collision* othor)
{
	for (auto col : m_List)
	{
		//if (col == this) {//tag
	}
}

Collision * Collision::SetPos(Vector3 position)
{
	pos = position;
	return this;
}

Collision * Collision::SetSize(Vector3 Size)
{
	size = Size;
	return this;
}

int Collision::GetTag()
{
	return m_tag;
}

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

void Collision::Clear()
{
	m_List.clear();
}

// EOF