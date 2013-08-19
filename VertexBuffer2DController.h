#ifndef VERTEXBUFFER2DCONTROLLER_H
#define VERTEXBUFFER2DCONTROLLER_H
/**
 * 管理顶点缓存。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <map>

class VertexBuffer2D;

class VertexBuffer2DController
{
public:
    VertexBuffer2DController();
    virtual ~VertexBuffer2DController();
    VertexBuffer2D* getVertexBuffer(int textureX1, int textureY1,
                                    int textureX2, int textureY2,
                                    int textureWidth, int textureHeight);

private:
    struct VertexBufferInfo
    {
        int textureX1, textureY1;
        int textureX2, textureY2;
        int textureWidth, textureHeight;
        friend bool operator <(const VertexBufferInfo &a, const VertexBufferInfo &b)
        {
            if (a.textureX1 == b.textureX1)
            {
                if (a.textureY1 == b.textureY1)
                {
                    if (a.textureX2 == b.textureX2)
                    {
                        if (a.textureY2 == b.textureY2)
                        {
                            if (a.textureWidth == b.textureWidth)
                            {
                                return a.textureHeight < b.textureHeight;
                            }
                            return a.textureWidth < b.textureWidth;
                        }
                        return a.textureY2 < b.textureY2;
                    }
                    return a.textureX2 < b.textureX2;
                }
                return a.textureY1 < b.textureY1;
            }
            return a.textureX1 < b.textureX1;
        }
    };
    std::map<VertexBufferInfo, VertexBuffer2D*> _buffers;
};

#endif // VERTEXBUFFER2DCONTROLLER_H
