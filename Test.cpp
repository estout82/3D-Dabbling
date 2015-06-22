#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include "VertexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Math.hpp"

#ifdef _DEBUG

#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

#endif

#ifdef NDEBUG

#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

#endif

sf::Window window;

ShaderProgram* program;
Texture* texture;
VertexBuffer* buffer;

Matrix4f worldMatrix;

unsigned int worldMatrixPos;

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);

	Vertex vertecies[3] =
	{
		Vertex(Vector3<float>(0.0f, 1.0f, 0.0f), Vector2<float>(0.5f, 1.0f)),
		Vertex(Vector3<float>(-1.0f, -1.0f, 0.0f), Vector2<float>(0.0f, 0.0f)),
		Vertex(Vector3<float>(1.0f, -1.0f, 0.0f), Vector2<float>(1.0f, 0.0f))
	};

	buffer = new VertexBuffer(vertecies, 3);

	texture = new Texture("image.png");

	program = new ShaderProgram();
	program->create(Shader("vertex.s", GL_VERTEX_SHADER), 
		Shader("fragment.s", GL_FRAGMENT_SHADER));
	program->use();

	worldMatrixPos = program->getUniformLocation("worldMatrix");
	worldMatrix = Matrix4f(Vector4f(1.0f, 0.0f, 0.0f, 0.0f),
		Vector4f(0.0f, 1.0f, 0.0f, 0.0f),
		Vector4f(0.0f, 0.0f, 1.0f, 0.0f),
		Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program->setUniformMatrix4f(70, worldMatrix);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	buffer->bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);

	glDrawArrays(GL_TRIANGLES, 0, buffer->getNumVertecies());

	buffer->unbind();
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
}

void update()
{

}

void dispose()
{
	delete buffer;
	delete texture;
	delete program;
}

int main(char** args, int argc)
{
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	window.create(sf::VideoMode(800, 600), "Test", sf::Style::Default, settings);

	// init glew
	if (window.isOpen())
	{
		std::cout << "Window created sucessfully." << std::endl;

		unsigned int glewStatus = glewInit();

		if (glewStatus != GLEW_OK)
		{
			std::cout << "Glew not initalized sucessfully. Exiting" << std::endl;

			window.close();
			dispose();
			return 0;
		}

		std::cout << "GLEW initalized sucessfully." << std::endl;
	}

	else
	{
		std::cout << "Window not creaeted sucesssfully. Exiting" << std::endl;
		return 0;
	}

	init();

	// main loop
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				dispose();
				return 0;
			}
		}

		update();
		render();
	}

	return 0;
}