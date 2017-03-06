#include "text.h"

namespace {

SDL_Color GetColor(Color color, uint8_t alpha = 0) {
  if (color == Color::Blue) {
    return { 0, 0, 255, alpha };
  } else if (color == Color::Red) {
    return { 255, 0, 0, alpha };
  } else if (color == Color::Green) {
    return  { 0, 255, 0, alpha };
  } else if (color == Color::Black) {
    return  { 0, 0, 0, alpha };
  } else if (color == Color::Yellow) {
    return { 255, 255, 0, alpha };
  } else if (color == Color::Cyan) {
    return { 153, 255, 255, alpha };
  } else {
    return { 255, 255, 255, alpha };
  }
}

}

std::tuple<SDL_Texture*, int, int> CreateTextureFromText(SDL_Renderer *renderer, TTF_Font *font, const std::string& text, Color text_color) {
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), GetColor(text_color, 0));
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width = surface->w;
  int height = surface->h;

  SDL_FreeSurface(surface);

  return std::make_tuple(texture, width, height);
}

void RenderText(SDL_Renderer *renderer, int x, int y, TTF_Font *font, const std::string& text, Color text_color) {
  SDL_Texture* texture;
  int width;
  int height;

  std::tie(texture, width, height) = CreateTextureFromText(renderer, font, text, text_color);

  SDL_Rect rc { x, y, width, height };

  SDL_RenderCopy(renderer, texture, nullptr, &rc);
  SDL_DestroyTexture(texture);
}

std::tuple<SDL_Texture*, int, int> CreateTextureFromFramedText(SDL_Renderer *renderer,
                                                               TTF_Font *font,
                                                               const std::string& text,
                                                               Color text_color,
                                                               Color background_color) {
  SDL_Surface* surface = TTF_RenderText_Shaded(font, text.c_str(), GetColor(text_color), GetColor(background_color));
  SDL_Texture* source_texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width = surface->w + 2;
  int height = surface->h + 2;

  SDL_FreeSurface(surface);

  SDL_Texture *target_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

  SDL_SetRenderTarget(renderer, target_texture);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

  SDL_Rect rc { 0, 0, width, height };

  SDL_RenderFillRect(renderer, &rc);
  rc = { 1, 1, width - 2, height - 2 };
  SDL_RenderCopy(renderer, source_texture, nullptr, &rc);
  SDL_SetRenderTarget(renderer, nullptr);

  SDL_DestroyTexture(source_texture);
  return std::make_tuple(target_texture, width, height);
}
