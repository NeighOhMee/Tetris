/*
Handels the window GUI for the Tetris game
*/
#pragma once
#ifndef __window_h_
#define __window_h_

#include <string>
#include <SDL.h>
class Window
{
	public:
		Window(const std::string &a_title, int a_width, int a_height);
		~Window();

		void pollEvents(char &direction, char &rotaion);
		void clear() const;
		void drawSquare(int x, int y, int r, int g, int b) const;
		void drawGrid() const;
		inline bool isClosed() const { return closed; }
		void update() const { SDL_RenderPresent(renderer);}
	private:
		bool init();
	private:
		std::string title;
		int width, height;
		bool closed;
		SDL_Window *window = NULL;
		SDL_Renderer *renderer = NULL;
};

#endif