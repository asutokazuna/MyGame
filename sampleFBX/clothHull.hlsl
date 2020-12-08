// ���͐���_

struct HS_IN {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

struct HS_OUT {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

// �o�̓p�b�`�萔�f�[�^�B
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor; // ���Ƃ��΁A�N���h �h���C���� [4] �ɂȂ�܂�
	float InsideTessFactor[2]			: SV_InsideTessFactor; // ���Ƃ��΁A�N���h �h���C���� Inside[2] �ɂȂ�܂�
	// TODO: ���̃X�^�b�t�̕ύX/�ǉ�
};

#define NUM_CONTROL_POINTS 4

// �p�b�`�萔�֐�
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_IN, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// �����ɃR�[�h��}�����ďo�͂��v�Z���܂�
	Output.EdgeTessFactor[0] = 
		Output.EdgeTessFactor[1] = 
		Output.EdgeTessFactor[2] = 
		Output.EdgeTessFactor[3] = 
		Output.InsideTessFactor[0] = // ���Ƃ��΁A����ɓ��I�e�Z���[�V�����W�����v�Z�ł��܂�
		Output.InsideTessFactor[1] = 20; // ���Ƃ��΁A����ɓ��I�e�Z���[�V�����W�����v�Z�ł��܂�

	return Output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_OUT main( 
	InputPatch<HS_IN, NUM_CONTROL_POINTS> ip, 
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID )
{
	HS_OUT Output;

	// �����ɃR�[�h��}�����ďo�͂��v�Z���܂�
	Output.Position = ip[i].Position;
	Output.Normal = ip[i].Normal;
	Output.TexCoord = ip[i].TexCoord;
	Output.Color = ip[i].Color;

	return Output;
}
