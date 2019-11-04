//Made by Denisghgh
#include "stdafx.h"
#include < time.h > 

BOOL init();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int w1, h1, counter = 0;

BOOL init()
{
	BOOL success = TRUE;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = FALSE;
	}
	else
	{
		gWindow = SDL_CreateWindow("TI Lab 5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
		if (gWindow == NULL)
		{
			
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = FALSE;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = FALSE;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void timer() {

	time_t start, end;
	float elapsed;
	time(&start);  //стартуем таймер
	time(&end);
	elapsed = difftime(end, start); // пройденный промежуток времени
	if (elapsed >= 0) {
		SDL_GetWindowSize(gWindow, &w1, &h1);
		SDL_SetRenderDrawColor(gRenderer, 0 + rand() % 255, 0 + rand() % 255, 0 + rand() % 255, 255);
		DrawCircle(gRenderer, 10 + rand() % w1, 10 + rand() % h1, 15 + rand() % 100);
		SDL_RenderPresent(gRenderer);				//Эта функция сообщает графическому процессору отображать на экран.
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		BOOL quit = FALSE;
		SDL_Event e;
		
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if ( SDL_QUIT == e.type )
				{
					quit = TRUE;
				}
				if ( SDL_KEYDOWN == e.type )
				{
					switch (e.key.keysym.scancode)
					{
					case SDL_SCANCODE_KP_PLUS:
						printf("SDL_SCANCODE_KP_PLUS have been presssed\n");
						break;
					case SDL_SCANCODE_KP_MINUS:
						printf("SDL_SCANCODE_KP_MINUS have been presssed\n");
						break;
					default:
						break;
					}
				}
			} 
			//if ((++counter % 15000) == 0)
				timer();  
		}
	}
	close();
	return 0;
}