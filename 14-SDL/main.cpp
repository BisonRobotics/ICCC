#include <iostream>
#include <SDL/SDL.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cerr << "Failed to initialize SDL\n";
        return 1;
    }

    SDL_Surface* s = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    srand(time(NULL));

    // lookup-table
    vector<unsigned int> color_lut;

    // add elements to the lookup table
    for(int i = 0; i < 256; i++) {
        color_lut.push_back(
            SDL_MapRGB(
                s->format, 
                rand() % 256,
                rand() % 256,
                rand() % 256)
        );
    }

    //
    // Drawing:
    //   SDL_Rect { h, w, x, y }
    //   call drawing function
    //      - pass SDL_Surface*
    //      - pass SDL_Rect*
    //      - supply a color
    //

    for(int x = 0; x < 600; x++) {
        //SDL_FillRect(s, NULL, 0);
        
        SDL_Rect r;
            r.h = 3;
            r.w = 3;
            r.x = rand() % 800;
            r.y = rand() % 600;

        SDL_FillRect(s, &r, color_lut[rand() % 256]);
        SDL_Flip(s);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}