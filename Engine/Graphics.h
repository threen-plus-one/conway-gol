/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Vec2.h"
#include "RectF.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	void FillRect( int x0,int y0,int x1,int y1,Color c );
	void FillRectDim( int x,int y,int width,int height,Color c )
	{
		FillRect( x,y,x + width,y + height,c );
	}
	void DrawRect( int x0,int y0,int x1,int y1,Color c );
	void DrawRectDim( int x,int y,int width,int height,Color c )
	{
		DrawRect( x,y,x + width,y + height,c );
	}
	void FillCircle( int cx,int cy,int radius,Color c );
	void DrawCircle( int cx,int cy,int radius,Color c );
	void DrawLine( int x0,int y0,int x1,int y1,Color c );

	// Wrappers
	void PutPixel( const Vec2& pos,Color c )
	{
		PutPixel( int( pos.x ),int( pos.y ),c );
	}
	void FillRect( const RectF& rect,Color c )
	{
		FillRect( int( rect.left ),int( rect.top ),int( rect.right ),int( rect.bottom ),c );
	}
	void DrawRect( const RectF& rect,Color c )
	{
		DrawRect( int( rect.left ),int( rect.top ),int( rect.right ),int( rect.bottom ),c );
	}
	void FillCircle( const Vec2& ctr,float radius,Color c )
	{
		FillCircle( int( ctr.x ),int( ctr.y ),int( radius + 0.5f ),c );
	}
	void DrawCircle( const Vec2& ctr,float radius,Color c )
	{
		DrawCircle( int( ctr.x ),int( ctr.y ),int( radius + 0.5f ),c );
	}
	void DrawLine( const Vec2& a,const Vec2& b,Color c )
	{
		DrawLine( int( a.x ),int( a.y ),int( b.x ),int( b.y ),c );
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};