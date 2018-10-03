#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#define log(x) std::cout << x << "\n";
#define logg(x) std::cout << x << "\n"

class Game {
  static const int W = 4, H = 4;
  int m[H][W];
  int xpos = SDL_WINDOWPOS_CENTERED, ypos = SDL_WINDOWPOS_CENTERED,
    width = 800, height = 900;
  bool fullscreen = false;
  SDL_Window *window;
  SDL_Renderer *renderer;
  char* score = "Score:";
public:
  bool runningOnEmpty = false;
  void init();
  void render();
  void clean();
  void handleEvents();
  void handleMove(auto key);
  void renderText(char* text, SDL_Color color, TTF_Font* font, int x, int y);
};

void Game::init(){
  int flags = 0;
  if(fullscreen){
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if(!SDL_Init(SDL_INIT_EVERYTHING)){
    log("SDL initialised!");
    window = SDL_CreateWindow("2048", xpos, ypos, width, height, flags);
    if(window){
      log("window created!");
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer){
      log("renderer initialised");
    }

    runningOnEmpty = true;
  } else {
    runningOnEmpty = false;
  }

  if(TTF_Init() == -1){
    log("ttf cannot be initialised!");
  } else log("ttf initialised!!!");
}

void Game::render(){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  //render the text (score from above, than text from suqares)
  TTF_Font* rFont = TTF_OpenFont("./fonts/roboto.ttf", 20);
  ((!rFont) ? logg("cannot open font!") : logg("opend font!"));
  SDL_Color white = {0, 0, 0};

  //render the squares!!!
  for(int i = 125; i <= 900; i+=200){
    for(int j = 25; j <= 900; j+=200){
       SDL_Rect r;
       r.x = j, r.y = i, r.w = 150, r.h = 150;
       std::string s = std::to_string(i);
       const char *tetx = s.c_str();
       int wt, ht;
       TTF_SizeText(rFont, tetx, &wt, &ht);

       SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
       SDL_RenderFillRect(renderer, &r);
       renderText(tetx, white, rFont, (j+((150 - wt)/2)), (i+((150 - ht)/2)));
    }
  }

  renderText(score, white, rFont, 10, 10);

  SDL_RenderPresent(renderer);
}

void Game::renderText(char* text, SDL_Color color, TTF_Font* font, int x,
                      int y){
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
  ((surface == NULL) ? logg("cannot make surface!") : logg("surface made!!!"));
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
  ((message == NULL) ? logg("cannot make texture!") : logg("texture made!!!"));
  SDL_Rect mr;
  mr.x = x, mr.y = y;
  //so we don't distort? the text
  TTF_SizeText(font, text, &mr.w, &mr.h);
  ((SDL_RenderCopy(renderer, message, NULL, &mr)) ? logg("cannot render text!")
   : logg("rendered text!"));
  SDL_DestroyTexture(message);
  SDL_FreeSurface(surface);
}

void Game::clean(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  log("Game cleaned!");
}

void Game::handleEvents(){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type){
  case SDL_QUIT:
    runningOnEmpty = false;
    break;
  case SDL_KEYDOWN:
    handleMove(event.key.keysym.sym);
  default:
    break;
  }
}

void Game::handleMove(auto key){
  switch(key){
  case 119:
    log("UP");
    render();
    break;
  case 97:
    log("LEFT");
    render();
    break;
  case 115:
    log("DOWN");
    render();
    break;
  case 100:
    log("RIGHT");
    render();
    break;
  default:
    break;
  }
}

int main(){
  Game* g = new Game();

  g->init();
  g->render();

  while(g->runningOnEmpty){
    g->handleEvents();
  }

  g->clean();
  return 0;
}
