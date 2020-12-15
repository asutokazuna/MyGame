#include "WingPtclMove.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Transform.h"

void WingPtclMove::Awake()
{
	m_move = Vector3();
	m_ParentTrans = &m_Parent->GetTransform();
}

void WingPtclMove::Update()
{
	//m_Parent->GetTransform().position += m_move;
	//m_Parent->GetTransform().rotation += m_rot;
	Vector3 wind = Vector3(0, 0, 0);
	Vector3 grav = Vector3(0, 0.01f, 0);
	float r = 0.1f;
	Move(wind,grav,r);
}

void WingPtclMove::Create(Vector3 velocity, Vector3 pos)
{
	//const int MAX_MOVE = 5;

	//m_move.x = rand() % MAX_MOVE / 10.0f;
	//m_move.y = rand() % MAX_MOVE / 10.0f;
	//m_move.z = rand() % MAX_MOVE / 10.0f;
	//m_rot.x = rand() % MAX_MOVE / 20.0f;
	//m_rot.y = rand() % MAX_MOVE / 20.0f;
	//m_rot.z = rand() % MAX_MOVE / 20.0f;

	//this.normalBendRatio = normalBendRatio;
	//this.quarternion = m_ParentTrans->quaternion;
	m_ParentTrans->position = pos;
	Vector3 t = m_ParentTrans->GetForward() * m_ParentTrans->scale.z / 2;
	Vector3 dp = velocity * (1 / (float)60);
	prevPosition0 = pos - t;
	prevPosition1 = pos + t;
	prevPosition0 -= dp;
	prevPosition1 -= dp;
}

void WingPtclMove::Move(Vector3 wind, Vector3 gravity, float resistance)
{
	Vector3 t = m_ParentTrans->GetForward() * m_ParentTrans->scale.z / 2;
	Vector3 p0 = m_ParentTrans->position - t;
	Vector3 p1 = m_ParentTrans->position + t;
	// 相対的な風ベクトルを出す
	Vector3 v0 = (p0 - prevPosition0) / (1/(float)60);
	Vector3 v1 = (p1 - prevPosition1) / (1/(float)60);
	Vector3 relativeWind0 = wind - v0;
	Vector3 relativeWind1 = wind - v1;
	// 頂点ごとの法線を生成
	// 曲げる
	t = m_ParentTrans->GetForward() * 0.1f;
	Vector3 n0 = m_ParentTrans->GetUp() + t;
	Vector3 n1 = m_ParentTrans->GetUp() - t;
	// 正規化。n1はn0と同じ長さなので長さを計算して使い回す
	MyMath::Normalize(n0);
	MyMath::Normalize(n1);
	// 風ベクトルの法線方向成分を、加速度とする
	float dot0 = MyMath::Dot(n0, relativeWind0);
	float dot1 = MyMath::Dot(n1, relativeWind1);
	Vector3 accel0 = n0 * (dot0 * resistance);
	Vector3 accel1 = n1 * (dot1 * resistance);
	// 重力を追加
	accel0 += gravity;
	accel1 += gravity;
	// 独立に積分
	float dt2 = (1 / (float)60) * (1 / (float)60);
	Vector3 dp0 = p0 - prevPosition0 + (accel0 * dt2);
	Vector3 dp1 = p1 - prevPosition1 + (accel1 * dt2);
	Vector3 nextP0 = p0 + dp0;
	Vector3 nextP1 = p1 + dp1;
	prevPosition0 = p0;
	prevPosition1 = p1;
	p0 = nextP0;
	p1 = nextP1;
	// 拘束
	Vector3 newForward = (p1 - p0);
	MyMath::Normalize(newForward);
	m_ParentTrans->position = (p0 + p1) * 0.5f;
	// 姿勢更新
	// forward -> newForwardに向くような、回転軸右ベクタの回転を作用させる
	Vector3 quat = m_ParentTrans->GetForward();
	Quaternion dq = MyMath::LookAt(quat, newForward);
	m_ParentTrans->quaternion = MyMath::CalcQuaternion( dq , m_ParentTrans->quaternion); // dqは時間的に後の回転だから、ベクタから遠い方、つまり前から乗算
	//quarternion.Normalize();
}

// EOF