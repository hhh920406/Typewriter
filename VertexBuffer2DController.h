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
    VertexBuffer2D* getVertexBuffer(int width, int height, int tun[4], int tud[4], int tvn[4], int tvd[4]);

private:
    struct VertexBufferInfo
    {
        int width, height;
        int tun[4], tvn[4];
        int tud[4], tvd[4];
        friend bool operator <(const VertexBufferInfo &a, const VertexBufferInfo &b)
        {
            if (a.width == b.width)
            {
                if (a.height == b.height)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        if (a.tun[i] * b.tud[i] != a.tud[i] * b.tun[i])
                        {
                            return a.tun[i] * b.tud[i] < a.tud[i] * b.tun[i];
                        }
                        if (a.tvn[i] * b.tvd[i] != a.tvd[i] * b.tun[i])
                        {
                            return a.tvn[i] * b.tvd[i] < a.tvd[i] * b.tun[i];
                        }
                    }
                }
                return a.height < b.height;
            }
            return a.width < b.width;
        }
    };
    std::map<VertexBufferInfo, VertexBuffer2D*> _buffers;
};

#endif // VERTEXBUFFER2DCONTROLLER_H
