#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 1050
#define HEIGHT 700

#define BALL_WIDTH_HEIGHT 20

#define PAD_MOVEMENT_SPEED 40

#define LEFT_PAD_W 10
#define LEFT_PAD_H 150

#define RIGHT_PAD_W 10
#define RIGHT_PAD_H 150

#define RAND_X 8
#define RAND_Y 6

void LoadGame()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect left_line;
    SDL_Rect right_line;

    SDL_Rect ball;
    ball.x = (WIDTH/2) - (BALL_WIDTH_HEIGHT/2);
    ball.y = (HEIGHT/2) - (BALL_WIDTH_HEIGHT/2);
    ball.w = ball.h = BALL_WIDTH_HEIGHT;

    int left_line_y = HEIGHT/2.6;
    int left_line_x = WIDTH/8;

    int right_line_y = HEIGHT/2.6;
    int right_line_x = WIDTH - WIDTH/8;

    float bX = ball.x;
    float bY = ball.y;

    bool bumped_left;
    bool bumped_right;

    srand(time(0));

    float speedX = (rand() % RAND_X) - 1;
    float speedY = (rand() % RAND_Y) - 1;

    if(speedX >= -2.0f && speedX < 2.0f) speedX = 3.0f;
    if(speedY >= -2.0f && speedY < 2.0f) speedY = -3.0f;

    speedX /= 100.0f;
    speedY /= 100.0f;   

    // SDL_Event event;

    // Initialize SDL
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result != 0) 
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Create window
    window = SDL_CreateWindow("Pong Game",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WIDTH,
                               HEIGHT,
                               SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
    }

    // Game loop
    SDL_Event event;
    bool var = true;
    bool moving = true;

    // MAKE IT WORK
    // if(ball.y < 450)
    // {
    //     bumped_right = true;
    //     bumped_left = false;
    // }
    // if(ball.y > 450)
    // {
    //     bumped_left = true;
    //     bumped_right = false;
    // }

    while (moving) 
        {
            if(ball.x < WIDTH / 2)
            {
                
                    while (SDL_PollEvent(&event) != 0) 
                    {

                        if (event.type == SDL_QUIT)
                        {
                            moving = false;
                        }
                        
                        if (event.type == SDL_KEYDOWN)
                        {
                            switch (event.key.keysym.sym) 
                            {
                                //TO DO
                                // Make it so when the user clicks any button the games start SDL_KEYDOWN

                                case SDLK_DOWN:
                                    left_line_y += PAD_MOVEMENT_SPEED;
                                    break;

                                case SDLK_UP:
                                    left_line_y -= PAD_MOVEMENT_SPEED;
                                    break;

                                case SDLK_r:
                                    SDL_DestroyRenderer(renderer);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    break;
                                    
                            }

                        }
                    }
            }
            else if(ball.x > WIDTH / 2)
            {
                while (SDL_PollEvent(&event) != 0) 
                    {

                        if (event.type == SDL_QUIT)
                        {
                            moving = false;
                        }
                        
                        if (event.type == SDL_KEYDOWN)
                        {
                            switch (event.key.keysym.sym) 
                            {

                                case SDLK_DOWN:
                                    right_line_y += PAD_MOVEMENT_SPEED;
                                    break;

                                case SDLK_UP:
                                    right_line_y -= PAD_MOVEMENT_SPEED;
                                    break;

                                case SDLK_r:
                                    SDL_DestroyRenderer(renderer);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    break;
                                    
                            }

                        }
                    }
            }

            
            bumped_left = SDL_HasIntersection(&ball, &left_line);
            bumped_right = SDL_HasIntersection(&ball, &right_line);

            
            if(!bumped_left || !bumped_right)
            {
                
                bX -= speedX;
                bY += speedY;

                ball.x = bX;
                ball.y = -bY;

            }

            if(ball.y <= 0)
            {
                    ball.y = 0;

                    speedY = (rand() % RAND_Y) - 1;

                    speedY /= 100.0f;

                    speedY = -speedY;

                    ball.y = bY;
            }   

            if(ball.y >= HEIGHT)
            {
                    ball.y = HEIGHT;

                    speedY = (rand() % RAND_Y) - 1;

                    speedY /= -100.0f;

                    speedY = -speedY;

                    ball.y = bY;
            }
                    
            if(bumped_left)
            {
                bumped_left = true;
                bumped_right = false;
                right_line_y = HEIGHT / 2.6;
                srand(time(0));
                speedY = -speedY;
                speedX = -speedX;

                speedX = (rand() % RAND_X) - 1;
                speedY = (rand() % RAND_Y) - 1;

                if(speedX >= -2.0f && speedX <= 2.0f) speedX = 3.0f;
                if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                speedX /= 100.0f;
                speedY /= 100.0f;

                speedX = -speedX;
                speedY = -speedY;

                ball.x = bX + 1;
                ball.y = bY + 1;
                
            }

            if(bumped_right)
            {
                bumped_right = true;
                bumped_left = false;
                left_line_y = HEIGHT / 2.6;
                srand(time(0));

                speedX = (rand() % RAND_X) - 1;
                speedY = (rand() % RAND_Y) - 1;

                if(speedX >= -2.0f && speedX <= 2.0f) speedX = 3.0f;
                if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                speedX /= -100.0f;
                speedY /= -100.0f;

                speedX = -speedX;
                speedY = -speedY;

                ball.x = bX + 1;
                ball.y = bY + 1;

            }

            if(left_line_y > HEIGHT - 125)
            {
                left_line_y = HEIGHT - 125;
            }
            if(left_line_y < 0)
            {
                left_line_y = 0;
            }
            if(right_line_y > HEIGHT - 125)
            {
                right_line_y = HEIGHT - 125;
            }
            if(right_line_y < 0)
            {
                right_line_y = 0;
            }
            
            if(ball.x <= -30 || ball.x >= WIDTH - 30)
            {

                printf("You lost");

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();

                break;
                                
            }

                // Clear screen with a background color (optional)
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Black
                SDL_RenderClear(renderer);

                // Set the color for the rectangle
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red

                // Draw the left pad
                left_line.x = left_line_x;
                left_line.y = left_line_y;
                left_line.w = LEFT_PAD_W;
                left_line.h = LEFT_PAD_H;
                SDL_RenderFillRect(renderer, &left_line);

                // Draw the right pad
                right_line.x = right_line_x;
                right_line.y = right_line_y;
                right_line.w = RIGHT_PAD_W;
                right_line.h = RIGHT_PAD_H;
                SDL_RenderFillRect(renderer, &right_line);

                // Draw the ball rectangle
                SDL_RenderFillRect(renderer, &ball);

                // Present the renderer to the screen
                SDL_RenderPresent(renderer);

                // Delay to control the frame rate (optional)
                // SDL_Delay(0.5); // ~ --- FPS
            
            
        }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    LoadGame();

    return 0;
}