#include "VertexArray.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

std::shared_ptr<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        assert(false, "RendererAPI::None is not a valid RenderAPI!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::shared_ptr<OpenGLVertexArray>();
    }

    assert(false, "Unknown RendererAPI!");
    return nullptr;
}