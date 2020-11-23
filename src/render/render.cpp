#include "render.h"



Render* render = new Render();


bool load_texture_from_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    // Load texture from disk
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileA(render->device, filename, &texture);
    if (hr != S_OK)
        return false;
	
    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;
}

void Render::init(IDirect3DDevice9* device)
{
	fonts->init();

    this->device = device;

    bool r = load_texture_from_file("D:\\Admin\\Pictures\\morgen.jpeg", &img.texture, &img.w, &img.h);
}
