#include <iostream>
#include <vector>
#include <cmath>

#include "AudioFile.h"

#include <SDL2/SDL.h>

int main()
{
    const int width = 700;
    const int height = 700;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Audio Visualizer");

    AudioFile<double> file = AudioFile<double>("./audio/EraseMe.wav");

    std::vector<double> samplesChannel1 = file.samples[0];
    std::vector<double> samplesChannel2 = file.samples[1];

    double partitions = 1000;

    // Outer Dots
    SDL_SetRenderDrawColor(
        renderer,
        150 - 100 * cbrtf(samplesChannel1[(int) (0.25 * samplesChannel1.size())]),
        150 + 100 * cbrtf(samplesChannel1[(int) (0.5 * samplesChannel1.size())]),
        150 - 100 * cbrtf(samplesChannel1[(int) (0.75 * samplesChannel1.size())]),
        255
    );
    for(int i = 0;i<partitions;i++)
    {
        double middleSample = samplesChannel1[(int) (i * samplesChannel1.size() / partitions)];
        double lowerSample;
        if(i - 2 < 0){
            lowerSample = samplesChannel1[(int) ((i + partitions - 2) * samplesChannel1.size() / partitions)];
        } else {
            lowerSample = samplesChannel1[(int) ((i - 2) * samplesChannel1.size() / partitions)];
        };
        double upperSample;
        if(i + 2 >= partitions){
            upperSample = samplesChannel1[(int) ((i - partitions + 2) * samplesChannel1.size() / partitions)];
        } else {
            upperSample = samplesChannel1[(int) ((i + 2) * samplesChannel1.size() / partitions)];
        };
        if(middleSample > lowerSample && middleSample > upperSample){
            double theta = (2 * M_PI) * (i / partitions);
            double radius = 200 + 90 * samplesChannel1[(int) (i * samplesChannel1.size() / partitions)];

            double x = 0.5 * width + cosf(theta) * radius;
            double y = 0.5 * height + sinf(theta) * radius;

            SDL_RenderDrawPoint(renderer, x, y);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x, y + 1);
            SDL_RenderDrawPoint(renderer, x + 1, y + 1);
        };
    };

    // Channel 1 Wave
    SDL_SetRenderDrawColor(
        renderer,
        100 - 100 * cbrtf(samplesChannel1[(int) (0.25 * samplesChannel1.size())]),
        100 + 100 * cbrtf(samplesChannel1[(int) (0.5 * samplesChannel1.size())]),
        100 - 100 * cbrtf(samplesChannel1[(int) (0.75 * samplesChannel1.size())]),
        255
    );
    for(int i = 0;i<partitions;i++){
        double theta1 = (2 * M_PI) * (i / partitions);
        double radius1 = 180 + 90 * samplesChannel1[(int) (i * samplesChannel1.size() / partitions)];

        double x1 = 0.5 * width + cosf(theta1) * radius1;
        double y1 = 0.5 * height + sinf(theta1) * radius1;

        double theta2 = (2 * M_PI) * ((i + 1) / partitions);
        double radius2;
        if(i == partitions - 1){
            radius2 = 180 + 90 * samplesChannel1[0];
        } else {
            radius2 = 180 + 90 * samplesChannel1[(int) ((i + 1) * samplesChannel1.size() / partitions)];
        };

        double x2 = 0.5 * width + cosf(theta2) * radius2;
        double y2 = 0.5 * height + sinf(theta2) * radius2;
        
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    };

    // Channel 2 Wave
    SDL_SetRenderDrawColor(
        renderer,
        100 + 100 * cbrtf(samplesChannel2[(int) (0.25 * samplesChannel2.size())]),
        100 - 100 * cbrtf(samplesChannel2[(int) (0.5 * samplesChannel2.size())]),
        100 + 100 * cbrtf(samplesChannel2[(int) (0.75 * samplesChannel2.size())]),
        255
    );
    for(int i = 0;i<partitions;i++){
        double theta1 = (2 * M_PI) * (i / partitions);
        double radius1 = 140 + 70 * samplesChannel2[(int) (i * samplesChannel2.size() / partitions)];

        double x1 = 0.5 * width + cosf(theta1) * radius1;
        double y1 = 0.5 * height + sinf(theta1) * radius1;

        double theta2 = (2 * M_PI) * ((i + 1) / partitions);
        double radius2;
        if(i == partitions - 1){
            radius2 = 140 + 70 * samplesChannel2[0];
        } else {
            radius2 = 140 + 70 * samplesChannel2[(int) ((i + 1) * samplesChannel2.size() / partitions)];
        };

        double x2 = 0.5 * width + cosf(theta2) * radius2;
        double y2 = 0.5 * height + sinf(theta2) * radius2;
        
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    };

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT){
                running = false;
            };
        };
    };

    return 0;
};