//
//  main.cpp
//  DVA336Project
//

#include <stdlib.h>
#include <stdio.h>
#include "bitmap_image.hpp"
#include <omp.h>

#define SIDE 1000


typedef struct 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;

pixel** in = (pixel**)malloc(sizeof(pixel*) * SIDE);
pixel** out = (pixel**)malloc(sizeof(pixel*) * SIDE);



int main(int argc, const char * argv[]) {
  srand(time(NULL));
    time_t time;

  // gen images...
  for (int i = 0; i < SIDE; ++i)
  {
    in[i] = (pixel*) malloc(sizeof(pixel) * SIDE);
    out[i] = (pixel*) malloc(sizeof(pixel) * SIDE);

    for (int j = 0; j < SIDE; ++j)
    {
      in[i][j].red = rand() % 255;
      in[i][j].green = rand() % 255;
      in[i][j].blue = rand() % 255;
      
      out[i][j].red = rand() % 255;
      out[i][j].green = rand() % 255;
      out[i][j].blue = rand() % 255;
    }
  }

  

    int height = SIDE;
    int width = SIDE;


  time = clock();

      for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
          int red = 0;
          int green = 0;
          int blue = 0;
          int neighbors = 0;
          rgb_t colour;
          
          for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
              if(i >= 0 && j >= 0 && i < width && j < height){
                  neighbors++;
                  red   += in[i][j].red;
                  green += in[i][j].green;
                  blue  += in[i][j].blue;
                }
              }
            }
            red   /= neighbors;
            green /= neighbors;
            blue  /= neighbors;
            out[y][x].red = red;
            out[y][x].green = green;
            out[y][x].blue = blue;
          }
      }

    time = clock() - time;
    printf("%f\n", ((float)time/CLOCKS_PER_SEC));
    
    bitmap_image bmpin = bitmap_image(width, height);
    bitmap_image bmpout = bitmap_image(width, height);

    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++){
        rgb_t colour;
        colour = make_colour(in[x][y].red, in[x][y].green, in[x][y].blue);
        bmpin.set_pixel(y, x, colour);
        colour = make_colour(out[x][y].red, out[x][y].green, out[x][y].blue);
        bmpout.set_pixel(y, x,colour);
      }
    }

    bmpin.save_image("in.bmp");
    bmpout.save_image("out.bmp");
    
    return 0;
}