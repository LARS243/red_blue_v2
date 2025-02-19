#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int size_window = 1500;

RenderWindow window(VideoMode(size_window, size_window), "shiiit");

void paint_feeld(int size, int x_camera, int y_camera, int zoom) {
	VertexArray line_x(Lines, 2);
	VertexArray line_y(Lines, 2);
	for (int i = 0; i < size_window / size; i++) {
		line_x[0].position = sf::Vector2f(i * size * zoom + x_camera, 0);
		line_x[1].position = sf::Vector2f(i * size * zoom + x_camera, size_window);
		window.draw(line_x);
		line_y[0].position = sf::Vector2f(0, i * size * zoom + y_camera);
		line_y[1].position = sf::Vector2f(size_window, i * size * zoom + y_camera);
		window.draw(line_y);
	}
}

int main()
{
	const int size = 30;
	int x_camera = 0;
	int y_camera = 0;
	int zoom = 4;
	Vector2i mousePos;
	Vector2i old_mousePos;
	Vector2i step;
	while (window.isOpen())
	{
		window.clear();
		Event event;
		
		while (window.pollEvent(event))
		{
			
			if (Mouse::isButtonPressed(Mouse::Middle)){
				mousePos = Mouse::getPosition(window);
				step.x = -old_mousePos.x + mousePos.x;
				step.y = -old_mousePos.y + mousePos.y;
				if (x_camera < size_window) {
					x_camera = (x_camera + step.x) % size_window;
				}
				if (y_camera < size_window) {
					y_camera = (y_camera + step.y) % size_window;
				}
				cout << x_camera << " " << y_camera << "\n";
				}
			if(sf::Event::MouseWheelMoved) {
				if (event.mouseWheel.delta == 1 and zoom < 4) {
					zoom++;
				}
				else if (event.mouseWheel.delta == -1 and zoom > 1)
					zoom--;
			}
				
			if (event.type == Event::Closed)
				window.close();
			old_mousePos = Mouse::getPosition(window);
		}
		
		paint_feeld(size, x_camera, y_camera, zoom);
		
		window.display();
	}

	return 0;
}