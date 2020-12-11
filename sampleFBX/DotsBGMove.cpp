#include "DotsBGMove.h"
#include "ShaderInfo.h"
/**
 * @brief 初期化
 * @retrun なし
 */
void DotsBGMove::Awake()
{
	uv = Vector3(1, 1, 1);
}

/**
 * @brief 更新
 * @retrun なし
 */
void DotsBGMove::Update()
{
	uv.x += 0.0003f;
	m_shader->SetFloat("TexWorld", MyMath::LoadPosisiton(uv));
}

void DotsBGMove::SetShader(ShaderInfo * shader)
{
	m_shader = shader;
}
// EOF