#pragma once

#include <vector>

#include "../vec3/vec3.h"
using color = vec3;

class Framebuffer
{
	public:
		//Constructors
		Framebuffer();
		Framebuffer(int x, int y);


		//utility functions
		void clearToColor(color c);
        void clearToGradient(color c1, color c2);

		void setPixelColor(int i, int j, color c);
        void setPixelColor(int index, color c);

		void exportAsPng(std::string fileName);



		///Getters and Setters
        void setWidth(int w);
        int getWidth();

        void setHeight(int h);
        int getHeight();

		std::vector<vec3> getFbStorage();
        void setFbStorage(std::vector<vec3> v);

	private:
		int width, height;
		std::vector<vec3> fbStorage;
};