#pragma once
#include "fonts/fonts.h"
#include <d3d9.h>
#include <d3dx9tex.h>


struct t_limage
{
	int w, h;
	PDIRECT3DTEXTURE9 texture;
};

class Render
{
public:
	ImDrawList* draw_list = nullptr;
	IDirect3DDevice9* device = nullptr;
	t_limage img;
	
	void init(IDirect3DDevice9* device);
	
}; extern Render* render;