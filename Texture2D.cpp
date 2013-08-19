#include "Texture2D.h"

Texture2D::Texture2D()
{
    this->_texture = NULL;
}

Texture2D::~Texture2D()
{
    if (NULL != this->_texture)
    {
        this->_texture->Release();
    }
}

LPDIRECT3DTEXTURE9 Texture2D::texture() const
{
    return this->_texture;
}

bool Texture2D::readFromFile(const char *fileName)
{
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    return D3DXCreateTextureFromFile(device, fileName, &this->_texture) == D3D_OK;
}
