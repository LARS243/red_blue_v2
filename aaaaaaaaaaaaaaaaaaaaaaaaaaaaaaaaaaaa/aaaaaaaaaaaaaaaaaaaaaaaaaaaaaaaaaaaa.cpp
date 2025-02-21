#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int size_window_x = 2000;
const int size_window_y = 1000;
const int size_field_x = 80;
const int size_field_y = 40;
const int max_zoom = 4;
const int min_zoom = 1;
const int size_cell = 30;
RenderWindow window(VideoMode(size_window_x, size_window_y), "shiiit");


void paint_feeld(int x_camera, int y_camera, int zoom) {
	/*VertexArray line_x(Lines, 2);
	VertexArray line_y(Lines, 2);
	line_y[0].position = sf::Vector2f(5000, 5000);
	line_y[1].position = sf::Vector2f(5000, 5000);
	window.draw(line_y);*/
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
			rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
			if ((i + j) % 2 == 0) {
				rectangle.setFillColor(sf::Color(i * 3, 0, j * 5));
			}
			else {
				rectangle.setFillColor(sf::Color(i * 3, 0, j * 5));
			}
			window.draw(rectangle);
		}
		
	}
}

void change_camera(Event event, Vector2i old_mousePos, Vector2i step, int &x_camera, int &y_camera, int zoom) {
	Vector2i mousePos;
	mousePos = Mouse::getPosition(window);
	step.x = -old_mousePos.x + mousePos.x;
	step.y = -old_mousePos.y + mousePos.y;
	x_camera = (x_camera + step.x) % (size_window_x * zoom);
	y_camera = (y_camera + step.y) % (size_window_y * zoom);
	if (x_camera > 0) {
		x_camera = 0;
	}
	if (x_camera < -(size_cell * size_field_x * zoom - size_window_x)) {
		x_camera = -(size_cell * size_field_x * zoom - size_window_x);
	}
	if (y_camera > 0) {
		y_camera = 0;
	}
	if (y_camera < -(size_cell * size_field_y * zoom - size_window_y)) {
		y_camera = -(size_cell * size_field_y * zoom - size_window_y);
	}

}

void change_zoom(Event event, int &zoom) {
	if (event.mouseWheel.delta == 1 and zoom < max_zoom) {
		zoom++;
	}
	else if (event.mouseWheel.delta == -1 and zoom > min_zoom)
		zoom--;
}


void game() {
	int x_camera = 0;
	int y_camera = 0;
	int zoom = 4;
	Vector2i old_mousePos;
	Vector2i step;
	while (window.isOpen())
	{
		window.clear();
		Event event;

		while (window.pollEvent(event))
		{

			if (Mouse::isButtonPressed(Mouse::Middle)) {
				change_camera(event, old_mousePos, step, x_camera, y_camera, zoom);
			}
			if (sf::Event::MouseWheelMoved) {
				change_zoom(event, zoom);
			}

			if (event.type == Event::Closed)
				window.close();
			old_mousePos = Mouse::getPosition(window);
		}
		paint_feeld(x_camera, y_camera, zoom);
		window.display();
	}
}

int main()
{
	game();
	return 0;
}