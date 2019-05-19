#include "window.h"
#include <iostream>

Window::Window(const std::string &a_title, int a_width, int a_height)
:title(a_title), width(a_width), height(a_height), closed(false)
{
	if (!init())
	{
		closed = true;
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::init()
{	//initializes window, returns false if an error occured
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL" << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);
	if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		return false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC );
	if (!renderer)
	{
		std::cerr << "Failed to create renderer" << std::endl;
		return 0;
	}
	return true;
}

void Window::pollEvents(char &direction, char &rotation)
{
	SDL_Event event;
	//if an event occurs
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				closed = true;
				std::cout << "closing" << std::endl;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_a:
						direction = 'L';
						break;
					case SDLK_d:
						direction = 'R';
						break;
					case SDLK_z:
						rotation = 'R';
						break;
					case SDLK_c:
						rotation = 'L';
						break;
				}
				break;
			default:
				break;
		}
	}
}

void Window::clear() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
}

void Window::drawSquare(int x, int y, int r, int g, int b) const
{	//draws a square of specified color at the x, y location in the tetris board
	SDL_Rect rect;
	rect.w = 30;
	rect.h = 30;
	rect.x = 260 + x*30;
	rect.y = y*30;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Window::drawGrid() const
{	//draws the tetris board
	int tileSize = 30;
	int x = 260;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, x-1, 0, x-1, 600);
	SDL_RenderDrawLine(renderer, x +tileSize *10, 0, x+tileSize*10, 600);
	SDL_RenderPresent(renderer);
}
