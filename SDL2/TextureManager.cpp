//
//  TextureManager.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/05.
//

#include "TextureManager.hpp"
#include "App.hpp"
#include <SDL_image.h>
#include "Vector2D.hpp"
#include <numeric>
#include <vector>

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
        
    SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, RECT& rect, BYTE opacity, TransformData& transform, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;
    
    // 회전 행렬이 지원되지 않아 x, y를 다시 계산.
    rect.left = rect.left * transform.eM11 - rect.top * transform.eM12;
    rect.top = rect.left * transform.eM21 + rect.top * transform.eM22;
    
    // 이동 행렬이 지원되지 않아 직접 덧셈.
    destRect.x = rect.left + transform.eDx;
    destRect.y = rect.top + transform.eDy;
    
    // 스케일 행렬이 지원되지 않음.
    destRect.w = width * transform.eM11;
    destRect.h = height * transform.eM22;
    
    // 벡터의 내적을 이용하여 원점으로부터 타겟 각도가 이루는 각을 역으로 추산.
    std::vector<LONG> origin {0, 0};
    std::vector<LONG> target {rect.left, rect.top};
    
    const double angle = std::inner_product(origin.begin(), origin.end(), target.begin(), 0);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, angle, 0, flip);
}
