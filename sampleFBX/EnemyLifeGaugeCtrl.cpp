#include "EnemyLifeGaugeCtrl.h"
#include "GameObject.h"
#include "GaugeCtrl.h"
#include "EnemyLifeCtrl.h"
#include "LifeGaugeShaderInfo.h"

LifeGaugeShaderInfo* shader;
EnemyLifeCtrl* lifectrl;

HRESULT EnemyLifeGaugeCtrl::Init()
{
	GameObject* gauge = m_Parent->GetChild("LifeGauge");
	GaugeCtrl* gaugectrl = gauge->GetComponent<GaugeCtrl>();
	shader = gaugectrl->GetLifeShader();
	gaugectrl->SetOffset(Vector3(0,50,0));
	gaugectrl->SetTarget(&m_Parent->GetTransform());

	lifectrl = m_Parent->GetComponent<EnemyLifeCtrl>();
	float life= lifectrl->GetLifePercent();
	shader->SetFloat("Life", life);

	return E_NOTIMPL;
}

void EnemyLifeGaugeCtrl::Update()
{
	float life = lifectrl->GetLifePercent();
	shader->SetFloat("Life", life);
}

// EOF