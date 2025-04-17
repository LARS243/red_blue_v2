#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
using namespace sf;

const int ID_black_hole = 0;
const int ID_construction = 1;
const int ID_tank = 2;
const int ID_anti_tank = 3;
const int ID_infantry = 4;
const int ID_motorised_infantry = 5;
const int ID_supply_car = 6;

const int size_window_x = 2000;
const int size_window_y = 1000;
const int size_field_x = 80;
const int size_field_y = 40;
const int max_zoom = 4;
const int min_zoom = 1;
const int size_cell = 30;

const int field = 0;
const int forest = 1;
const int mount = 2;

vector<vector<Texture>> textures_relief;

Color field_color = { 40, 100, 0 };
Color forest_color = { 0,69,36 };
Color mount_color = { 150, 150, 150 };
Color black_for_Oleg = { 0, 0, 0 };//Потом делитнуть 



RenderWindow window(VideoMode(size_window_x, size_window_y), "shiiit");

int matrix_relief[size_field_x][size_field_y];
int matrix_units[size_field_x][size_field_y];

class construction {
private:
	int health;
	int armor;
	int ID;
public:
	construction() {
		health = 100;
		armor = 50;
		ID = ID_construction;
	}
	int get_health() {
		return(health);
	}
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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
	int armor = 50;
	int ID;
public:
	tank() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 20;
		mobility = 10;
		supply = 50;
		armor = 50;
		ID = ID_tank;
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
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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
	int armor;
	int ID;

public:
	anti_tank() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 20;
		mobility = 10;
		supply = 50;
		armor = 50;
		ID = ID_anti_tank;
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
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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
	int armor;
	int ID;

public:
	infantry() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 2;
		mobility = 10;
		supply = 50;
		armor = 50;
		ID_infantry;
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
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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
	int armor;
	int ID;

public:
	motorised_infantry() {
		health = 100;
		damage_to_living_force = 10;
		damage_to_war_machine = 5;
		mobility = 10;
		supply = 50;
		armor = 50;
		ID = ID_motorised_infantry;
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
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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
	int armor;
	int ID;

public:
	supply_car() {
		health = 10000;
		damage_to_living_force = 1000;
		damage_to_war_machine = 3000;
		mobility = 4000;
		supply_for_supply = 2147483647;
		armor = 50;
		ID = ID_supply_car;
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
	int get_armor() {
		return(armor);
	}
	int get_ID() {
		return(ID);
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

void print(int matrix[size_field_x][size_field_y]) {
	for (int j = 0; j < size_field_y; j++) {
		for (int i = 0; i < size_field_x; i++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void reflect_reliesf(int matrix[size_field_x][size_field_y]) {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (i < size_field_y / 2) {
				matrix[size_field_x - i - 1][size_field_y - j - 1] = matrix[i][j];
			}
		}
	}

	for (int j = 0; j < size_field_y; j++) {
		for (int i = 0; i < size_field_y - j - 1; i++) {
			matrix[size_field_y + size_field_y / 2 - i - 1][size_field_y - j - 1] = matrix[size_field_y / 2 + i][j];
		}


	}


}

void clear_field(int matrix[size_field_x][size_field_y]) {
	int rand_element;
	int matrix_elements[3];

	for (int i = 1; i < size_field_x - 1; i++) {
		for (int j = 1; j < size_field_y - 1; j++) {

			matrix_elements[field] = 0;
			matrix_elements[forest] = 0;
			matrix_elements[mount] = 0;

			matrix_elements[matrix[i][j + 1]]++;
			matrix_elements[matrix[i + 1][j]]++;
			matrix_elements[matrix[i - 1][j]]++;
			matrix_elements[matrix[i][j - 1]]++;

			if (matrix_elements[matrix[i][j]] == 0) {
				if (matrix[i][j] == field) {
					if (matrix_elements[forest] == 4) {
						matrix[i][j] = forest;
					}
					else if (matrix_elements[mount] == 4) {
						matrix[i][j] = mount;
					}
					else {
						matrix[i][j] = rand() % 2 + 1;
					}
				}
				else if (matrix[i][j] == forest) {
					if (matrix_elements[field] == 4) {
						matrix[i][j] = field;
					}
					else if (matrix_elements[mount] == 4) {
						matrix[i][j] = mount;
					}
					else {
						rand_element = rand() % 2;
						if (rand_element) {
							matrix[i][j] = field;
						}
						else {
							matrix[i][j] = mount;
						}

					}
				}
				else {
					if (matrix_elements[forest] == 4) {
						matrix[i][j] = forest;
					}
					else if (matrix_elements[field] == 4) {
						matrix[i][j] = field;
					}
					else {
						matrix[i][j] = rand() % 2;
					}
				}
			}
		}


	}

}

void generate_relief() {
	srand(time(0));
	int rand_element;
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			rand_element = rand() % 4;
			if (i == 0 and j == 0) {
				matrix_relief[i][j] = 0;
			}
			else if (i == 0) {
				if (matrix_relief[i][j - 1] == field) {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = field;
					}
				}
				else if (matrix_relief[i][j - 1] == forest) {
					if (rand_element == 3) {
						matrix_relief[i][j] = mount;
					}
					else if (rand_element == 0) {
						matrix_relief[i][j] = field;
					}
					else {
						matrix_relief[i][j] = forest;
					}
				}
				else {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = mount;
					}
				}
			}
			else if (j == 0) {
				if (matrix_relief[i - 1][j] == field) {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = field;
					}
				}
				else if (matrix_relief[i - 1][j] == forest) {
					if (rand_element == 3) {
						matrix_relief[i][j] = mount;
					}
					else if (rand_element == 0) {
						matrix_relief[i][j] = field;
					}
					else {
						matrix_relief[i][j] = forest;
					}
				}
				else {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = mount;
					}
				}
			}
			else {
				int average = (matrix_relief[i - 1][j] + matrix_relief[i][j - 1]) / 2;
				if (average == field) {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = field;
					}
				}
				else if (average == forest) {
					if (rand_element == 3) {
						matrix_relief[i][j] = mount;
					}
					else if (rand_element == 0) {
						matrix_relief[i][j] = field;
					}
					else {
						matrix_relief[i][j] = forest;
					}
				}
				else {
					if (rand_element == 3) {
						matrix_relief[i][j] = forest;
					}
					else {
						matrix_relief[i][j] = mount;
					}
				}

			}
		}

	}
	reflect_reliesf(matrix_relief);
	clear_field(matrix_relief);
}

Color get_color(int color) {
	if (color == field) {
		return field_color;
	}
	else if (color == forest) {
		return forest_color;
	}
	else {
		return mount_color;
	}
}

void matrix_unit_to_zero() {
	for (int i = 0; i < size_field_x; i++)
	{
		for (int j = 0; j < size_field_y; j++)
		{
			matrix_units[i][j] = ID_black_hole;
		}
	}
}
void load_texture() {
	vector<Texture> field_textures;
	vector<Texture> forest_textures;
	vector<Texture> mount_textures;

	Image image_field_30;
	Texture texture_field_30;
	Image image_field_60;
	Texture texture_field_60;
	Image image_field_90;
	Texture texture_field_90;
	Image image_field_120;
	Texture texture_field_120;

	Image image_forets_30;
	Texture texture_forets_30;
	Image image_forets_60;
	Texture texture_forets_60;
	Image image_forets_90;
	Texture texture_forets_90;
	Image image_forets_120;
	Texture texture_forets_120;

	Image image_mount_30;
	Texture texture_mount_30;
	Image image_mount_60;
	Texture texture_mount_60;
	Image image_mount_90;
	Texture texture_mount_90;
	Image image_mount_120;
	Texture texture_mount_120;

	image_field_30.loadFromFile("field_30px.png");
	texture_field_30.loadFromImage(image_field_30);
	image_field_60.loadFromFile("field_60px.png");
	texture_field_60.loadFromImage(image_field_60);
	image_field_90.loadFromFile("field_90px.png");
	texture_field_90.loadFromImage(image_field_90);
	image_field_120.loadFromFile("field_120px.png");
	texture_field_120.loadFromImage(image_field_120);
	field_textures.push_back(texture_field_30);
	field_textures.push_back(texture_field_60);
	field_textures.push_back(texture_field_90);
	field_textures.push_back(texture_field_120);

	image_forets_30.loadFromFile("forest_30px.png");
	texture_forets_30.loadFromImage(image_forets_30);
	image_forets_60.loadFromFile("forest_60px.png");
	texture_forets_60.loadFromImage(image_forets_60);
	image_forets_90.loadFromFile("forest_90px.png");
	texture_forets_90.loadFromImage(image_forets_90);
	image_forets_120.loadFromFile("forest_120px.png");
	texture_forets_120.loadFromImage(image_forets_120);
	forest_textures.push_back(texture_forets_30);
	forest_textures.push_back(texture_forets_60);
	forest_textures.push_back(texture_forets_90);
	forest_textures.push_back(texture_forets_120);

	image_mount_30.loadFromFile("mount_30px.png");
	texture_mount_30.loadFromImage(image_mount_30);
	image_mount_60.loadFromFile("mount_60px.png");
	texture_mount_60.loadFromImage(image_mount_60);
	image_mount_90.loadFromFile("mount_90px.png");
	texture_mount_90.loadFromImage(image_mount_90);
	image_mount_120.loadFromFile("mount_120px.png");
	texture_mount_120.loadFromImage(image_mount_120);
	mount_textures.push_back(texture_mount_30);
	mount_textures.push_back(texture_mount_60);
	mount_textures.push_back(texture_mount_90);
	mount_textures.push_back(texture_mount_120);

	textures_relief.push_back(field_textures);
	textures_relief.push_back(forest_textures);
	textures_relief.push_back(mount_textures);
}

Vector2f zoom_to_scale(int zoom) {
	Vector2f scale;
	if (zoom == 1) {
		scale = { 1.f, 1.f };
	}
	else if (zoom == 2) {
		scale = { 2.f, 2.f };
	}
	else if (zoom == 3) {
		scale = { 3.f, 3.f };
	}
	else {
		scale = { 4.f, 4.f };
	}
	return (scale);
}

void paint_relief(int x_camera, int y_camera, int zoom) {
	Image image_oil_30;
	Texture texture_oil_30;
	Sprite sprite_oil;
	image_oil_30.loadFromFile("oil_30px.png");
	texture_oil_30.loadFromImage(image_oil_30);
	sprite_oil.setTexture(texture_oil_30);
	Vector2f scale = zoom_to_scale(zoom);
	sprite_oil.setScale(scale);
	Sprite sprite_field;
	Sprite sprite_forest;
	Sprite sprite_mount;

	sprite_field.setTexture(textures_relief[field][zoom - 1]);
	sprite_forest.setTexture(textures_relief[forest][zoom - 1]);
	sprite_mount.setTexture(textures_relief[mount][zoom - 1]);

	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
			rectangle.setFillColor(get_color(matrix_relief[i][j]));
			window.draw(rectangle);
			if (i == 0 and j == 0) {
				sprite_oil.setScale(scale);
				sprite_oil.setPosition(0, 0);
				window.draw(sprite_oil);
			}
			else if (matrix_relief[i][j] == field) {
				sprite_field.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_field);

			}
			else if (matrix_relief[i][j] == forest) {
				sprite_field.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_field);
				sprite_forest.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_forest);

			}
			else {
				sprite_mount.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_mount);
			}


		}
	}
}

void paint_units(int x_camera, int y_camera, int zoom) {//Допилить под новые реалии, но потом
	int type_units;
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			type_units = matrix_units[i][j];
			if (type_units != 0) {

				rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				switch (type_units) {
				case 1:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				case 2:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				case 3:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				case 4:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				case 5:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				case 6:
					rectangle.setFillColor(black_for_Oleg);
					window.draw(rectangle);
					break;
				default:
					break;
				}
			}
		}

	}
}

void paint_game(int x_camera, int y_camera, int zoom) {
	paint_relief(x_camera, y_camera, zoom);
	paint_units(x_camera, y_camera, zoom);
}

void change_camera(Event event, Vector2i old_mousePos, Vector2i step, int& x_camera, int& y_camera, int zoom) {

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

void change_zoom(Event event, int& zoom, int& x_camera, int& y_camera) {

	if (event.mouseWheelScroll.delta == 1 and zoom < max_zoom) {
		zoom++;
	}
	if (event.mouseWheelScroll.delta == -1 and zoom > min_zoom) {

		zoom--;
	}

	if (x_camera < -(size_cell * size_field_x * zoom - size_window_x)) {
		x_camera = -(size_cell * size_field_x * zoom - size_window_x);
	}
	if (y_camera < -(size_cell * size_field_y * zoom - size_window_y)) {
		y_camera = -(size_cell * size_field_y * zoom - size_window_y);
	}
}

void select_element(Event event, int& zoom) {//Костыль
	Vector2i mousePos;
	mousePos = Mouse::getPosition(window);
	cout << mousePos.x << " " << mousePos.y << endl;
}

void game() {
	load_texture();
	generate_relief();
	int x_camera = 0;
	int y_camera = 0;
	int zoom = 4;
	Vector2i old_mousePos;
	Vector2i step;
	Event event;
	while (window.isOpen())
	{
		window.clear();

		while (window.pollEvent(event))
		{

			if (Mouse::isButtonPressed(Mouse::Middle)) {

				change_camera(event, old_mousePos, step, x_camera, y_camera, zoom);
			}
			if (sf::Event::MouseWheelScrolled) {

				change_zoom(event, zoom, x_camera, y_camera);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//Костыль
				select_element(event, zoom);
			}

			if (event.type == Event::Closed)
				window.close();

			old_mousePos = Mouse::getPosition(window);

		}
		paint_game(x_camera, y_camera, zoom);
		window.display();
	}
}

int main()
{
	matrix_unit_to_zero();
	game();
	return 0;
}