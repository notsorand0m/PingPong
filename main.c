#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void LoadGame()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect left_line;
    SDL_Rect right_line;

    SDL_Rect ball;
    ball.x = (900/2) - (20/2);
    ball.y = (650/2) - (20/2);
    ball.w = ball.h = 20;

    int left_line_y = 250;
    int left_line_x = 80;

    int right_line_y = 250;
    int right_line_x = 820;

    bool bumped_left = false;
    bool bumped_right = false;

    float bX = ball.x;
    float bY = ball.y;

    int counter = 0;

    srand(time(0));

    float speedX = (rand() % 10) - 1;
    float speedY = (rand() % 8) - 1;

    if(speedX >= -2.0f && speedX <= 2.0f) speedX = 3.0f;
    if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

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
                               900,
                               650,
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
    while (moving) 
        {
            if(ball.x < 400)
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
                                    left_line_y += 10;
                                    break;

                                case SDLK_UP:
                                    left_line_y -= 10;
                                    break;

                                case SDLK_r:
                                    LoadGame();
                                    SDL_DestroyRenderer(renderer);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    break;
                                    
                            }

                        }
                    }
            }
            else if(ball.x > 400)
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
                                    right_line_y += 10;
                                    break;

                                case SDLK_UP:
                                    right_line_y -= 10;
                                    break;

                                case SDLK_r:
                                    LoadGame();
                                    SDL_DestroyRenderer(renderer);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    break;
                                    
                            }

                        }
                    }
            }

            


            bool left = false;
            bumped_left = SDL_HasIntersection(&ball, &left_line);
            bumped_right = SDL_HasIntersection(&ball, &right_line);
            bool left_bump = false;
            bool right_bump = false;
            
            // Add high score
            // Add counter of hits
            // Fix the colliding with the left and right line with the ball

            // Add aesthethics *if you have time
            // Organize the code *if you have time
            
            if(!bumped_left || !bumped_right)
            {
                bX -= speedX;
                bY += speedY;

                ball.x = bX;
                ball.y = bY;

                // FIX THESE VALUES
                //if(ball.y <= 250 || ball.y >= 1000)
                //{
                //  speedY = -speedY;
                    //speedX = -speedX;

                    //speedX = (rand() % 7) - 1;
                    //speedY = (rand() % 3) - 1;

                    //if(speedX >= -0.01f && speedX <= 0.01f) speedX = 1.0f;
                    //if(speedY >= -0.01f && speedY <= 0.01f) speedY = -1.0f;

                    //speedX /= 100.0f;
                    //speedY /= 100.0f;
                //}
                
            }
                    
            if(bumped_left)
            {
                left_bump = true;
                srand(time(0));
                speedY = -speedY;
                speedX = -speedX;

                speedX = (rand() % 10) - 1;
                speedY = (rand() % 8) - 1;

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
                srand(time(0));

                speedX = (rand() % 10) - 1;
                speedY = (rand() % 8) - 1;

                if(speedX >= -2.0f && speedX <= 2.0f) speedX = 3.0f;
                if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                speedX /= -100.0f;
                speedY /= -100.0f;

                speedX = -speedX;
                speedY = -speedY;

                ball.x = bX + 1;
                ball.y = bY + 1;

            }
            
            if(ball.x <= -30 || ball.x >= 930)
            {
                printf("You lost");

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();

                break;
                                
            }
            if(ball.y <= 20)
            {
                    ball.y = 20;

                    srand(time(0));

                    speedY = (rand() % 8) - 1;

                    if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                    speedY /= 100.0f;

                    speedY = speedY;

                    ball.y = bY - 1;
            }   

            if(ball.y >= 630)
            {
                    ball.y = 630;

                    srand(time(0));

                    speedY = (rand() % 8) - 1;

                    if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                    speedY /= 100.0f;

                    speedY = speedY;

                    ball.y = bY - 1;
            }

                // Clear screen with a background color (optional)
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Black
                SDL_RenderClear(renderer);

                // Set the color for the rectangle
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red

                // Draw the left pad
                left_line.x = left_line_x;
                left_line.y = left_line_y;
                left_line.w = 10;
                left_line.h = 150;
                SDL_RenderFillRect(renderer, &left_line);

                // Draw the right pad
                right_line.x = right_line_x;
                right_line.y = right_line_y;
                right_line.w = 10;
                right_line.h = 150;
                SDL_RenderFillRect(renderer, &right_line);

                // Draw the ball rectangle
                SDL_RenderFillRect(renderer, &ball);

                // Present the renderer to the screen
                SDL_RenderPresent(renderer);

                // Delay to control the frame rate (optional)
                // SDL_Delay(0.5); // ~ --- FPS
            
            
        }
    

    if(SDL_HasIntersection(&ball, &right_line))
    {
        bool moving = true;
        while (moving) 
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
                            right_line_y += 10;
                            break;

                        case SDLK_UP:
                            right_line_y -= 10;
                            break;
                        case SDLK_r:
                            LoadGame();
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            break;
                    }

                }
            }

            bool left = false;
            bumped_left = SDL_HasIntersection(&ball, &left_line);
            bumped_right = SDL_HasIntersection(&ball, &right_line);
            bool left_bump = false;
            bool right_bump = false;
            
            // Add high score
            // Add counter of hits
            // Fix the colliding with the left and right line with the ball

            // Add aesthethics *if you have time
            // Organize the code *if you have time


            if(!bumped_left && !bumped_right)
            {
                bX -= speedX;
                bY += speedY;

                ball.x = bX;
                ball.y = bY;

                // FIX THESE VALUES
            //if(ball.y <= 250 || ball.y >= 1000)
            //{
              //  speedY = -speedY;
                //speedX = -speedX;

                //speedX = (rand() % 7) - 1;
                //speedY = (rand() % 3) - 1;

                //if(speedX >= -0.01f && speedX <= 0.01f) speedX = 1.0f;
                //if(speedY >= -0.01f && speedY <= 0.01f) speedY = -1.0f;

                //speedX /= 100.0f;
                //speedY /= 100.0f;
            //}
                
            }
                    
            if(bumped_left)
            {
                srand(time(0));
                speedY = -speedY;
                speedX = -speedX;

                speedX = (rand() % 10) - 1;
                speedY = (rand() % 8) - 1;

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
                srand(time(0));
                speedY = -speedY;
                speedX = -speedX;

                speedX = (rand() % 10) - 1;
                speedY = (rand() % 8) - 1;

                if(speedX >= -2.0f && speedX <= 2.0f) speedX = 3.0f;
                if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                speedX /= -100.0f;
                speedY /= -100.0f;

                speedX = -speedX;
                speedY = -speedY;

                ball.x = bX + 1;
                ball.y = bY + 1;

            }
            
            if(ball.x <= -30 || ball.x >= 930)
            {
                printf("You lost");

                LoadGame();
                                
            }
            if(ball.y <= 20)
            {
                    ball.y = 20;

                    srand(time(0));

                    speedY = (rand() % 8) - 1;

                    if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                    speedY /= 100.0f;

                    speedY = -speedY;

                    ball.y = bY + 1;
            }

            if(ball.y >= 600)
            {
                    ball.y = 600;

                    srand(time(0));

                    speedY = (rand() % 8) - 1;

                    if(speedY >= -2.01f && speedY <= 2.0f) speedY = -3.0f;

                    speedY /= 100.0f;

                    speedY = -speedY;

                    ball.y = bY + 1;
            }
                 

                // Clear screen with a background color (optional)
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Black
                SDL_RenderClear(renderer);

                // Set the color for the rectangle
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red

                // Draw the left pad
                left_line.x = left_line_x;
                left_line.y = left_line_y;
                left_line.w = 10;
                left_line.h = 150;
                SDL_RenderFillRect(renderer, &left_line);

                // Draw the right pad
                right_line.x = right_line_x;
                right_line.y = right_line_y;
                right_line.w = 10;
                right_line.h = 150;
                SDL_RenderFillRect(renderer, &right_line);

                // Draw the ball rectangle
                SDL_RenderFillRect(renderer, &ball);

                // Present the renderer to the screen
                SDL_RenderPresent(renderer);

                // Delay to control the frame rate (optional)
                SDL_Delay(8.33); // ~120 FPS
            
            
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    LoadGame();

    return 0;
}
