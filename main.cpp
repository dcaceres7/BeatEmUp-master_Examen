
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>
#include<list>
#include "Sho.h"
#include "EnemigoAzul.h"
#include "EnemigoVerde.h"
#include "EnemigoRojo.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Rect rect_background;

SDL_Rect rect_perder;
SDL_Texture* texture_perder;

SDL_Rect rect_ganar;
SDL_Texture* texture_ganar;



int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1024/*WIDTH*/, 768/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    texture_ganar= IMG_LoadTexture(renderer,"ganaste.png");
    texture_perder= IMG_LoadTexture(renderer,"perdiste.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    SDL_QueryTexture(texture_ganar, NULL, NULL, &w, &h);
    rect_ganar.x = rect_background.x + (rect_background.w/2) -(w/2);
    rect_ganar.y = rect_background.y + (rect_background.h/2) -(h/2);
    rect_ganar.w = w;
    rect_ganar.h = h;

    SDL_QueryTexture(texture_perder, NULL, NULL, &w, &h);
    rect_perder.x = rect_background.x + (rect_background.w/2) -(w/2);
    rect_perder.y = rect_background.y + (rect_background.h/2) -(h/2);
    rect_perder.w = w;
    rect_perder.h = h;

bool empezar=false;



    list<Personaje*> personajes;
    personajes.push_back(new Sho(renderer,&personajes));

    //Main Loop
    int frame=0;
    int animacion_sho = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    bool continuar=true,c=true;
    while(true)
    {


        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

if(currentKeyStates[SDL_SCANCODE_E])
    {
        empezar=true;
    }

 if(empezar){
        if(frame%950==0)
        {
          personajes.push_back(new EnemigoRojo(renderer,&personajes));
          personajes.push_back(new EnemigoAzul(renderer,&personajes));
        }

        if(frame%3000==0)
        {
          personajes.push_back(new EnemigoVerde(renderer,&personajes));
        }
 }


        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++){
               (*p)->act();
            if((*p)->ganar>=3){
               continuar=false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, background, NULL, &rect_background);

if(continuar){
        if(c){
        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->draw(renderer);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            if((*p)->muerto)
            {
                personajes.erase(p);
              if((*p)->tipoPersonaje=="sho"){
                    cout<<""<<endl;
              background = IMG_LoadTexture(renderer,"perdiste.png");
                //c=false;
              }
                break;
            }
        }
}
else
    SDL_RenderCopy(renderer, texture_ganar, NULL, &rect_ganar);
        SDL_RenderPresent(renderer);

        frame++;

    }

	return 0;
}




