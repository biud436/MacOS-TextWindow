//
//  TextureManager.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/05.
//

#include "TextureManager.hpp"
#include "App.hpp"
#include <SDL_image.h>

TextureData::TextureData()
{
    width = 0;
    height = 0;
    texture = 0;
}

TextureData::~TextureData()
{
}

TextureManager::TextureManager() :
    m_crTransparent(RGB(255, 255, 255)),
    m_bitmapColor(0, 0, 0, 255)

{
    
}

TextureManager::~TextureManager()
{
    TextureGroup::iterator iter;

    for (iter = m_textureMap.begin(); iter != m_textureMap.end(); iter++)
    {
        SAFE_DELETE(iter->second)
    }

}

bool TextureManager::Remove(std::string id)
{
    TextureGroup::iterator iter;

    iter = m_textureMap.find(id);

    if (iter != m_textureMap.end()) {
        SAFE_DELETE(iter->second)
    }

    m_textureMap.erase(id);
        
    return true;
}

bool TextureManager::valid(std::string id)
{
    TextureGroup::iterator iter;

    iter = m_textureMap.find(id);
    return iter != m_textureMap.end();
}

bool TextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{

    TextureData *pTextureData = new TextureData();
    
    std::string fmt = fileName.substr(fileName.size() - 4, 4);


    SDL_Surface* pTempSurface = IMG_Load(&fileName[0]);
    if(pTempSurface == 0)
    {
        return false;
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    if(pTexture != 0)
    {
        // 폭과 높이를 구합니다.
        SDL_QueryTexture(pTexture, 0, 0, &pTextureData->width, &pTextureData->height);
        
        pTextureData->texture = pTexture;
        m_textureMap[id] = pTextureData;
        return true;
    }
        
    return false;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    
    destRect.x = x;
    destRect.y = y;
    
    const double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
        
    SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &srcRect, angle, 0, flip);
}
