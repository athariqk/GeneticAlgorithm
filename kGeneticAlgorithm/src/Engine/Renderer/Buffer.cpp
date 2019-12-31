#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <assert.h>

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        assert(false, "RendererAPI: None is not a valid API!");
		return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
	}

	assert(false, "Unknown RendererAPI!");
	return nullptr;
}

IndexBuffer* IndexBuffer::Create(float* indices, uint32_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        assert(false, "RendererAPI: None is not a valid API!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }

    assert(false, "Unknown RendererAPI!");
    return nullptr;
}
