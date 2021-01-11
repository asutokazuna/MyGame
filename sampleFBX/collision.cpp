/**
 * @file Collision
 * @brief 当たり判定クラス
 */
#include "collision.h"
#include "GameObject.h"
#include "ModelData.h"
#include "MyMath.h"
#include "Transform.h"
#include "CollisionManager.h"

static bool m_isViewCol = true;

/**
 * @breif コンストラクタ
 */
Collision::Collision()
{
	m_isActive = true;
	m_tag = 0;
	m_offsetPos = Vector3();
	m_offsetSize = Vector3(0.5f,0.5f,0.5f);

	CollisionManager::GetInstance().Set(this);
}

/**
 * @brief デストラクタ
 */
Collision::~Collision()
{
}

/**
 * @breif 初期化処理
 * @return なし
 */
HRESULT Collision::Init()
{
	m_transform = &m_Parent->GetTransform();
	m_tag = m_Parent->GetTag();
	Vector3 pos = m_transform->position + m_offsetPos;
	Vector3 size = m_offsetSize * m_transform->scale;

#ifdef _DEBUG
	XMFLOAT3 halfsize(1,1,1);
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
 * @breif 終了
 * @return なし
 */
void Collision::Uninit()
{
#ifdef _DEBUG
	m_box.Uninit();
#endif
}

/**
 * @breif 更新
 * @return なし
 */
void Collision::Update()
{
	Vector3 pos = m_transform->position + m_offsetPos;
#ifdef _DEBUG

	Vector3 size = m_offsetSize * m_transform->scale;
	Transform trans = *m_transform;
	trans.position = pos;
	trans.scale = size;
	XMFLOAT4X4 mtx;// = m_box.GetWorld();
	//mtx._41 = pos.x;
	//mtx._42 = pos.y;
	//mtx._43 = pos.z;
	//m_box.SetWorld(mtx);
	mtx = MyMath::StoreXMFloat4x4(trans);
	m_box.SetWorld(mtx);
#endif
}

/**
 * @breif 描画
 * @return なし
 */
void Collision::Draw()
{
#if _DEBUG

	//if (ImGui::TreeNode("Collsiion")) {

		ImGui::Begin("PlayerCollision");
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
//	ImGui::TreePop();}
#endif
}

/**
 * @breif 描画
 * @return なし
 */
void Collision::DrawAlpha()
{
#ifdef _DEBUG
	if(m_isViewCol == true)
	m_box.Draw();
#endif
}

/**
 * @breif タグの設定
 * @return なし
 */
void Collision::SetTag(int tag)
{
	m_tag = tag;
}

/**
 * @breif 座標の設定
 * @return 実体
 */
Collision * Collision::SetPos(Vector3 position)
{
	m_offsetPos = position;
	return this;
}

/**
 * @breif 大きさの設定
 * @return 実体
 */
Collision * Collision::SetSize(Vector3 Size)
{
	m_offsetSize = Size;
	return this;
}
/**
 * @breif モデルの種類設定 半分の大きさをセット
 * @param[in] kind モデルの種類
 * @return 実体
 */
Collision * Collision::SetModelKind(int modelkind)
{
	m_offsetSize =  ModelData::GetSize(modelkind);

	return this;
}

/**
 * @breif タグの取得
 * @return タグの数値
 */
int Collision::GetTag()
{
	return m_tag;
}

/**
 * @breif バウンディングボックスでの当たり判定の比較
 * @return 当たっていればtrue
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

// EOF