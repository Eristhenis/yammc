#include <SDL2/SDL.h>
#include <sstream>
#include "board.h"

const int kFPS = 30;
const int kFrameDelay = 1000 / kFPS;

class MidasMiner {
 public:
  MidasMiner() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
      exit(-1);
    }
    if (TTF_Init() != 0) {
      std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
      exit(-1);
    }
  }
  ~MidasMiner() = default;

  void Play() {
    Board board;
    bool quit = false;
    std::vector<std::shared_ptr<Animation>> animation = {std::make_shared<NoneAnim>()};

    while (!quit) {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          quit = true;
          break;
        }
        switch (event.type) {
          case SDL_KEYDOWN:
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
              board.Restart();
              animation = { std::make_shared<NoneAnim>() };
            }
            break;
#if !defined(NDEBUG)
          case SDL_MOUSEMOTION: {

            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            int row = pixel_to_row(mouseY);
            int col = pixel_to_col(mouseX);
            int id = -1;

            if (row != -1 && col != -1) {
              id = board(row, col);
            }
            std::stringstream ss;
            ss << "X: " << mouseX << " Y: " << mouseY << " Row: " <<  row << " Col: " << col << " Id: " << id;

            SDL_SetWindowTitle(board, ss.str().c_str());
          } break;
#endif
          case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
              case SDL_BUTTON_LEFT:
                animation = board.GetInteraction(pixel_to_row(event.motion.y), pixel_to_col(event.motion.x));
                break;
            }
        }
      }
      int frame_start_rendering = SDL_GetTicks();

      animation = { board.Render(animation) };

      int frame_rendering_time = (SDL_GetTicks() - frame_start_rendering);

      if (frame_rendering_time < kFrameDelay) {
        SDL_Delay(kFrameDelay - frame_rendering_time);
      }
    }
    SDL_Quit();
  }
};

int main(int, char * []) {
  MidasMiner midas_miner;

  midas_miner.Play();

  return 0;
}
