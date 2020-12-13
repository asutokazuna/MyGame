#pragma once

// 警告非表示
//#pragma warning(disable : 4996)

#include <d3d11.h>

HRESULT LoadVertexShader(LPCWSTR pwszVSFName, ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
HRESULT LoadPixelShader(LPCWSTR pwszPSFName, ID3D11PixelShader** ppPixelShader);
HRESULT LoadHullShader(LPCWSTR pwszPSFName, ID3D11HullShader** ppHullShader);
HRESULT LoadDomainShader(LPCWSTR pwszPSFName, ID3D11DomainShader** ppDomeinhader);
HRESULT LoadGeometryShader(LPCWSTR pwszPSFName, ID3D11GeometryShader** ppGeometryShader);
HRESULT LoadShader(LPCWSTR pwszVSFName, LPCWSTR pwszPSFName,
	ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout, ID3D11PixelShader** ppPixelShader,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);

HRESULT LoadVertexShader(LPCSTR pszVSFName, ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
HRESULT LoadPixelShader(LPCSTR pszPSFName, ID3D11PixelShader** ppPixelShader);
HRESULT LoadHullShader(LPCSTR pszPSFName, ID3D11HullShader** ppHullShader);
HRESULT LoadDomainShader(LPCSTR pszPSFName, ID3D11DomainShader** ppDomainShader);
HRESULT LoadGeometryShader(LPCSTR pszPSFName, ID3D11GeometryShader** ppGeometryShader);
HRESULT LoadShader(LPCSTR pszVSFName, LPCSTR pszPSFName,
	ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout,
	ID3D11PixelShader** ppPixelShader,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
