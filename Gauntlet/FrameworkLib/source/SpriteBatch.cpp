#include <Application.h>
#include <Texture.h>
#include <TextureManager.h>

#include <SpriteBatch.h>

using namespace NHTV;

#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

SpriteBatch::SpriteBatch( const char* filename )
    : m_TextureID( 0 )
    , m_VBO( 0 )
    , m_SourceBlendFactor( GL_SRC_ALPHA )
    , m_DestinationBlendFactor( GL_ONE_MINUS_SRC_ALPHA )
    , m_ModelTransform( 1 ) // Identity
{
    CTextureManager* textureManager = CTextureManager::GetInstance();
    if ( textureManager )
    {
        m_TextureID = textureManager->LoadTexture( filename );
    }
}

SpriteBatch::~SpriteBatch()
{
    CTextureManager* textureManager = CTextureManager::GetInstance();
    if ( textureManager )
    {
        textureManager->RemoveTexture( m_TextureID );
    }

    if ( m_VBO != 0 )
    {
        glDeleteBuffers( 1, &m_VBO );
    }
    if ( m_VAO != 0 )
    {
        glDeleteVertexArrays( 1, &m_VAO );
    }
}

unsigned int SpriteBatch::AddSprite( const Sprite& sprite )
{
    m_Sprites.push_back( sprite );
    return unsigned int(m_Sprites.size() - 1);
}

SpriteBatch::Sprite& SpriteBatch::GetSprite( unsigned int spriteID )
{
    assert( spriteID < m_Sprites.size() && "Invalid sprite ID" );
    return m_Sprites[spriteID];
}

const SpriteBatch::Sprite& SpriteBatch::GetSprite( unsigned int spriteID ) const
{
    assert( spriteID < m_Sprites.size() && "Invalid sprite ID" );
    return m_Sprites[spriteID];
}

SpriteBatch::Sprite& SpriteBatch::operator[]( unsigned int spriteID )
{
    assert( spriteID < m_Sprites.size() && "Invalid sprite ID" );
    return m_Sprites[spriteID];
}

const SpriteBatch::Sprite& SpriteBatch::operator[]( unsigned int spriteID ) const
{
    assert( spriteID < m_Sprites.size() && "Invalid sprite ID" );
    return m_Sprites[spriteID];
}

unsigned int SpriteBatch::GetNumSprites() const
{
    return (unsigned int)m_Sprites.size();
}

void SpriteBatch::SetBlendFunction( GLenum sourceFactor, GLenum destinationFactor )
{
    m_SourceBlendFactor = sourceFactor;
    m_DestinationBlendFactor = destinationFactor;
}

void SpriteBatch::GetBlendFunction( GLenum& sourceFactor, GLenum& destinationFactor ) const
{
    sourceFactor = m_SourceBlendFactor;
    destinationFactor = m_DestinationBlendFactor;
}

void SpriteBatch::Draw()
{
    if ( m_VBO == 0 )
    {
        GenBuffer();
    }

    GLuint shaderID = Application::GetInstance().GetSpriteBatchShader();

    glUseProgram( shaderID );

    // Update internal variables.
    GLint modelTranformID = glGetUniformLocation( shaderID, "Model" );
    glUniformMatrix4fv( modelTranformID, 1, GL_FALSE, glm::value_ptr( m_ModelTransform ) );

    glBindTexture( GL_TEXTURE_2D, m_TextureID );

    glEnable( GL_BLEND );
    glBlendFunc( m_SourceBlendFactor, m_DestinationBlendFactor );

    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    // Copy the sprite data to the VBO
    glBufferData( GL_ARRAY_BUFFER, m_Sprites.size() * sizeof( Sprite ), m_Sprites.data(), GL_DYNAMIC_DRAW );

    glBindVertexArray( m_VAO );

    glDrawArrays( GL_POINTS, 0, GLsizei(m_Sprites.size()) );

    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glDisable( GL_BLEND );
    glBindTexture( GL_TEXTURE_2D, 0 );

    glUseProgram( 0 );
}

void SpriteBatch::GenBuffer()
{
    // Setup VAO for rendering.
    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Sprite::Position
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Position ) );

    // Sprite::Size
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Size ) );

    // Sprite::Origin
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Origin ) );

    // Sprite::Color
    glEnableVertexAttribArray( 3 );
    glVertexAttribPointer( 3, 4, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Color ) );

    // Sprite::minUV
    glEnableVertexAttribArray( 4 );
    glVertexAttribPointer( 4, 2, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_MinUV ) );

    // Sprite::maxUV
    glEnableVertexAttribArray( 5 );
    glVertexAttribPointer( 5, 2, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_MaxUV ) );

    // Sprite::Rotation
    glEnableVertexAttribArray( 6 );
    glVertexAttribPointer( 6, 1, GL_FLOAT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Rotation ) );

    // Sprite::Alive
    glEnableVertexAttribArray( 7 );
    glVertexAttribPointer( 7, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof( Sprite ), MEMBER_OFFSET( Sprite, m_Alive ) );

    // Unbind the vertex array object.
    glBindVertexArray( 0 );
}