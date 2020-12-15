#include "WingParticle.h"
#include "WingPtclMove.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"

WingParticle::WingParticle()
{
}


WingParticle::~WingParticle()
{
}

void WingParticle::Awake()
{
	AddComponent<WingPtclMove>();
	AddComponent<UIMesh>()->ChangeSize(100,100,1);
	AddComponent<DefaultShaderInfo>();
}

// EOF