#include <globjects/TextureAttachment.h>

#include <cassert>

#include <globjects/Texture.h>

namespace glo
{

TextureAttachment::TextureAttachment(Framebuffer * fbo, gl::GLenum attachment, Texture * texture, gl::GLint level, gl::GLint layer)
: FramebufferAttachment(fbo, attachment)
, m_texture(texture)
, m_level(level)
, m_layer(layer)
{
}

bool TextureAttachment::isTextureAttachment() const
{
	return true;
}

Texture * TextureAttachment::texture()
{
	return m_texture;
}

const Texture * TextureAttachment::texture() const
{
    return m_texture;
}

gl::GLint TextureAttachment::level() const
{
    return m_level;
}

bool TextureAttachment::hasLayer() const
{
    return m_layer >= 0;
}

gl::GLint TextureAttachment::layer() const
{
    return m_layer;
}

} // namespace glo
