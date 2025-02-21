#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int size_window = 1000;
const int size_field_x = 80;
const int size_field_y = 40;
const int max_zoom = 4;
const int min_zoom = 1;
const int start_x_camera = size_window / 2;
const int start_y_camera = size_window / 2;
const int size_cell = 30;
RenderWindow window(VideoMode(size_window, size_window), "shiiit");

class construction {
private:
	int health;
public:
	construction() {
		health = 100;
	}
	int get_health() {
		return(health);
	}
	void set_health(int new_health) {
		health = new_health;
	}
};

class tank {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;
public:
	tank() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 20;
		mobility = 10;
		supply = 50;
	}
	int get_health() {
		return(health);
	}
	int get_damage_to_living_force() {
		return(damage_to_living_force);
	}
	int get_damage_to_war_machine() {
		return(damage_to_war_machine);
	}
	int get_mobility() {
		return(mobility);
	}
	int get_supply() {
		return(supply);
	}
	void set_mobility(int new_mobility) {
		mobility = new_mobility;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_supply(int new_supply) {
		supply = new_supply;
	}
};

class anti_tank {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;

public:
	anti_tank() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 20;
		mobility = 10;
		supply = 50;
	}
	int get_health() {
		return(health);
	}
	int get_damage_to_living_force() {
		return(damage_to_living_force);
	}
	int get_damage_to_war_machine() {
		return(damage_to_war_machine);
	}
	int get_mobility() {
		return(mobility);
	}
	int get_supply() {
		return(supply);
	}
	void set_mobility(int new_mobility) {
		mobility = new_mobility;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_supply(int new_supply) {
		supply = new_supply;
	}
};

class infantry {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;

public:
	infantry() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 2;
		mobility = 10;
		supply = 50;
	}
	int get_health() {
		return(health);
	}
	int get_damage_to_living_force() {
		return(damage_to_living_force);
	}
	int get_damage_to_war_machine() {
		return(damage_to_war_machine);
	}
	int get_mobility() {
		return(mobility);
	}
	int get_supply() {
		return(supply);
	}
	void set_mobility(int new_mobility) {
		mobility = new_mobility;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_supply(int new_supply) {
		supply = new_supply;
	}
};

class motorised_infantry {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;

public:
	motorised_infantry() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 5;
		mobility = 10;
		supply = 50;
	}
	int get_health() {
		return(health);
	}
	int get_damage_to_living_force() {
		return(damage_to_living_force);
	}
	int get_damage_to_war_machine() {
		return(damage_to_war_machine);
	}
	int get_mobility() {
		return(mobility);
	}
	int get_supply() {
		return(supply);
	}
	void set_mobility(int new_mobility) {
		mobility = new_mobility;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_supply(int new_supply) {
		supply = new_supply;
	}
};

class supply_car {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply_for_supply;

public:
	supply_car() {
		health = 10000;
		damage_to_living_force = 1000;
		damage_to_war_machine = 3000;
		mobility = 4000;
		supply_for_supply = 2147483647;
	}
	int get_health() {
		return(health);
	}
	int get_damage_to_living_force() {
		return(damage_to_living_force);
	}
	int get_damage_to_war_machine() {
		return(damage_to_war_machine);
	}
	int get_mobility() {
		return(mobility);
	}
	int get_supply() {
		return(supply_for_supply);
	}
	void set_mobility(int new_mobility) {
		mobility = new_mobility;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_supply(int new_supply) {
		supply_for_supply = new_supply;
	}
};

void paint_feeld(int x_camera, int y_camera, int zoom) {
	VertexArray line_x(Lines, 2);
	VertexArray line_y(Lines, 2);
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
			/*line_y[0].position = sf::Vector2f(0, i * size_cell * zoom + y_camera);
			line_y[1].position = sf::Vector2f(size_window, i * size_cell * zoom + y_camera);
			window.draw(line_y);*/
		}
		
	}
}

void change_camera(Event event, Vector2i old_mousePos, Vector2i step, int &x_camera, int &y_camera, int zoom) {
	Vector2i mousePos;
	mousePos = Mouse::getPosition(window);
	step.x = -old_mousePos.x + mousePos.x;
	step.y = -old_mousePos.y + mousePos.y;
	x_camera = (x_camera + step.x) % (size_window * zoom);
	y_camera = (y_camera + step.y) % (size_window * zoom);
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