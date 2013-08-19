#ifndef TEXTURE2D_H
#define TEXTURE2D_H
/**
 * 基本的纹理。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Framework.h"

class Texture2D
{
public:
    Texture2D();
    virtual ~Texture2D();
    LPDIRECT3DTEXTURE9 texture() const;
    bool readFromFile(const char *fileName);

private:
    LPDIRECT3DTEXTURE9 _texture;
};

#endif // TEXTURE2D_H
