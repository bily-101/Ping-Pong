#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"


int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int yVelocity = 1;
int xVelocity = 1;
int last_frame_time = 0;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;
struct paddel {
	float x;
	float y;
	float width;
	float height;
} paddel;
int initialize_window() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		fprintf(stderr, "Error initializing SDL. \n");
		return FALSE;
	}

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED, //X pos
		SDL_WINDOWPOS_CENTERED, //Y pos
		WINDOW_WIDTH, // Width
		WINDOW_HEIGHT, //Height
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Making a window");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		fprintf(stderr, "ERROR MAKING RENDER");
		return FALSE;	
	}
	return TRUE;
		
};

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE){
				game_is_running = FALSE;
				break;
			}
			if(event.key.keysym.sym == SDLK_a){
				paddel.x-=5;
			}
			
			if(event.key.keysym.sym == SDLK_d){
				paddel.x+=5;
			}

	}
}

void setup() {
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;

	paddel.x = 400;
	paddel.y = 580;
	paddel.width = 200;
	paddel.height = 10;
}


void update() {

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

	last_frame_time = SDL_GetTicks();

	ball.x += xVelocity;
	ball.y += yVelocity;
	if( paddel.y >= ball.y - ball.height && paddel.y < ball.y + ball.height &&
        paddel.x > ball.x - paddel.width && paddel.x < ball.x + ball.width){
		yVelocity*=-1;
		printf("works");
	}

	if(ball.x>=800 || ball.x<=0) {
		xVelocity*=-1;
	}
	if(ball.y<=0){
		yVelocity *= -1;
	}
	if(ball.y>=600){
		game_is_running = FALSE;
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	// TODO: Here is where we draw game objects.
	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};
	SDL_Rect paddel_rect = {
		(int)paddel.x,
		(int)paddel.y,
		(int)paddel.width,
		(int)paddel.height
	};
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);


	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderFillRect(renderer, &paddel_rect);


	SDL_RenderPresent(renderer);

}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

int main() {

 	game_is_running = initialize_window();

	setup();
	 
	while (game_is_running) 
	{
		process_input();
		update();
		render();
	}

	destroy_window();

    return 0;
}
