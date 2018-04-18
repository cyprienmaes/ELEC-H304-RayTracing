#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>

int numberWall;

typedef struct WALL WALL;

struct WALL{
/*
Creation of different kinds of wall for reflexion and refraction.
*/
    float conductivity;
    float permeability;
    char vertical;
    // Position of the top right corner of a rectangle.
    SDL_Rect position;
    //
    SDL_Surface *newWall;
};

void StayDisplay() {
/*
Function which wait the event of exit screen. It's better than a while(1).
*/
    int continu = 1;
    SDL_Event event;

    while (continu){
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT :
                continu = 0;
        }
    }
}

WALL *SquareMap(SDL_Surface *screen, WALL *wall){
    numberWall = 4;
    wall = malloc(numberWall*sizeof(WALL));
    if (wall == NULL) exit(0);
    int i = 0;
    for(i=0;i<=1;i++){
        wall[i].conductivity = 0;
        wall[i].permeability = 0;
        wall[i].vertical = 0;
        wall[i].position.x = 0;
        wall[i].position.y = i*596;
        // (memory, length, higth, color, others)
        wall[i].newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, 600, 4, 32, 0, 0, 0, 0);
        SDL_FillRect(wall[i].newWall, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        // Put the new rectangle inside de frame int the position x and y
        SDL_BlitSurface(wall[i].newWall, NULL, screen, &wall[i].position);
    }
    for(i=0;i<=1;i++) {
        wall[i+2].conductivity = 0;
        wall[i+2].permeability = 0;
        wall[i+2].vertical = 1;
        wall[i+2].position.x = i*596;
        wall[i+2].position.y = 4;
        wall[i+2].newWall = SDL_CreateRGBSurface(SDL_SWSURFACE, 4, 592, 32, 0, 0, 0, 0);
        SDL_FillRect(wall[i+2].newWall, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(wall[i+2].newWall, NULL, screen, &wall[i+2].position);
    }
    return wall;
}

void freeWALL(WALL *wall) {
    int i = 0;
    for (i=0; i<numberWall; i++) {
    SDL_FreeSurface(wall[i].newWall);
    }
}

