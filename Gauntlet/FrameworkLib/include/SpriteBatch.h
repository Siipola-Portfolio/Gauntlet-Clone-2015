#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace NHTV
{
    class SpriteBatch
    {
    public:
        struct Sprite
        {
            // Sprite position in screen space.
            glm::vec2   m_Position;
            // Size of the sprite in pixels.
            glm::vec2   m_Size;
            // Origin of the sprite in normalized coordinates (0, 0) is bottom-left, (1, 1) is top-right.
            // Can also be considered an "Anchor" because it also effects where the sprite is drawn on screen.
            glm::vec2   m_Origin;
            // Color of the sprite. Can be used to fade sprites.
            glm::vec4   m_Color;
            // Min texture coordinates. Default value is (0, 0) which refers to the bottom-left point in a texture.
            glm::vec2   m_MinUV;
            // Max texture coordinates. Default value is (1, 1) which refers to the top-right point in a texture.
            glm::vec2   m_MaxUV;
            // Rotation of the sprite in radians. The sprite will be rotated relative to it's origin.
            float       m_Rotation;

            // If the sprite should not be rendered, set this to false (0).
            uint32_t     m_Alive;

            Sprite()
                : m_Position( 0.0f, 0.0f )
                , m_Size( 0, 0 )
                , m_Origin( 0.5f, 0.5f ) // Default origin is center of sprite.
                , m_Color( 1.0f, 1.0f, 1.0f, 1.0f )
                , m_MinUV( 0.0f, 0.0f )
                , m_MaxUV( 1.0f, 1.0f )
                , m_Rotation( 0.0f )
                , m_Alive( 1 )
            {}
        };

        // Construct a sprite batch.
        // filename is the texture to use to render all 
        // sprites in the sprite batch.
        SpriteBatch( const char* filename );

        virtual ~SpriteBatch();

        // Adds a sprite to the sprite batch.
        // The sprite is copied to the sprite buffer.
        // To modify the sprite after it has been added to the sprite buffer, 
        // use the SpriteBatch::GetSprite method.
        // Returns the ID that can be used to reference the sprite again later.
        unsigned int AddSprite( const Sprite& sprite = Sprite() );
        Sprite& GetSprite( unsigned int spriteID );
        const Sprite& GetSprite( unsigned int spriteID ) const;

        // Gets the number of sprites in the sprite batch.
        unsigned int GetNumSprites() const;

        // Access the sprites of the sprite batch like an array.
        Sprite& operator[]( unsigned int spriteID );
        const Sprite& operator[]( unsigned int spriteID ) const;

        void SetBlendFunction( GLenum sourceFactor, GLenum destinationFactor );
        void GetBlendFunction( GLenum& sourceFactor, GLenum& destinationFactor ) const;

        void Draw();

    protected:

    private:
        // Generates the VAO & VBO
        void GenBuffer();

        typedef std::vector<Sprite> SpriteList;
        SpriteList m_Sprites;

        // Blend factors will be applied to all sprites in the sprite batch
        GLenum m_SourceBlendFactor;
        GLenum m_DestinationBlendFactor;

        unsigned int m_TextureID;

        GLuint  m_VBO;
        GLuint  m_VAO;

        glm::mat4 m_ModelTransform;

    };
}