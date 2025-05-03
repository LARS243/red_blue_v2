//﻿#include <SFML/Graphics.hpp>
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

const int player_bar_size_y = 200;
const int player_bar_size_x = 300;

const int size_field_x = 80;
const int size_field_y = 40;
const int max_zoom = 4;
const int min_zoom = 1;
const int size_cell = 30;

const int count_mode = 6;

const int control_mode = 0;
const int supply_mode = 1;
const int grid_mode = 2;
const int resources_mode = 3;
const int builds_mode = 4;
const int unit_mode = 5;

const int field = 0;
const int forest = 1;
const int mount = 2;

const int oil = 0;
const int iron = 1;
const int coal = 2;
const int null = 3;

const int neutral = 0;
const int red = 1;
const int blue = 2;

//const int infantry = 0;
const int jaeger = 1;
const int mount_infantry = 2;

vector<Texture> textures_relief;
vector<Texture> textures_resources;
vector<Texture> textures_blue_units;

Color field_color = { 40, 100, 0 };
Color forest_color = { 0,69,36 };
Color mount_color = { 150, 150, 150 };
Color black_for_Oleg = { 0, 0, 0 };//Потом делитнуть 
Color red_color = { 255,0,0, 100 };
Color blue_color = { 0, 0, 255 , 100 };

RenderWindow window(VideoMode(size_window_x, size_window_y), "shiiit");

int matrix_relief[size_field_x][size_field_y];
int matrix_units[size_field_x][size_field_y];
int matrix_resources[size_field_x][size_field_y];
int matrix_control[size_field_x][size_field_y];
bool matrix_mode[count_mode];

/*
Не использовать имена
infantry
tank
anti_tank
motorised_infantry
supply_car
*/
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
	int armor;
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

class buffer {
private:
	int index;
	construction* construction_point = nullptr;
	tank* tank_point = nullptr;
	anti_tank* anti_tank_point = nullptr;
	infantry* infantry_point = nullptr;
	motorised_infantry* motorised_infantry_point = nullptr;
	supply_car* supply_car_point = nullptr;

public:
	buffer(int new_index) {
		switch (new_index) {
		case 1:
			construction_point = new construction();
			index = new_index;
			break;
		case 2:
			tank_point = new tank();
			index = new_index;
			break;
		case 3:
			anti_tank_point = new anti_tank();
			index = new_index;
			break;
		case 4:
			infantry_point = new infantry();
			index = new_index;
			break;
		case 5:
			motorised_infantry_point = new motorised_infantry();
			index = new_index;
			break;
		case 6:
			supply_car_point = new supply_car();
			index = new_index;
			break;
		default:
			break;
		}
	}

	int get_health(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_health());
			break;
		case 2:
			return (tank_point->get_health());
			break;
		case 3:
			return (anti_tank_point->get_health());
			break;
		case 4:
			return (infantry_point->get_health());
			break;
		case 5:
			return (motorised_infantry_point->get_health());
			break;
		case 6:
			return (supply_car_point->get_health());
			break;
		default:
			break;
		}
	}

	int get_damage_to_living_force(int new_index) {
		switch (new_index) {
		case 2:
			return (tank_point->get_damage_to_living_force());
			break;
		case 3:
			return (anti_tank_point->get_damage_to_living_force());
			break;
		case 4:
			return (infantry_point->get_damage_to_living_force());
			break;
		case 5:
			return (motorised_infantry_point->get_damage_to_living_force());
			break;
		case 6:
			return (supply_car_point->get_damage_to_living_force());
			break;
		default:
			break;
		}
	}

	int get_damage_to_war_machine(int new_index) {
		switch (new_index) {
		case 2:
			return (tank_point->get_damage_to_war_machine());
			break;
		case 3:
			return (anti_tank_point->get_damage_to_war_machine());
			break;
		case 4:
			return (infantry_point->get_damage_to_war_machine());
			break;
		case 5:
			return (motorised_infantry_point->get_damage_to_war_machine());
			break;
		case 6:
			return (supply_car_point->get_damage_to_war_machine());
			break;
		default:
			break;
		}
	}

	int get_mobility(int new_index) {
		switch (new_index) {
		case 2:
			return (tank_point->get_mobility());
			break;
		case 3:
			return (anti_tank_point->get_mobility());
			break;
		case 4:
			return (infantry_point->get_mobility());
			break;
		case 5:
			return (motorised_infantry_point->get_mobility());
			break;
		case 6:
			return (supply_car_point->get_mobility());
			break;
		default:
			break;
		}
	}

	int get_supply(int new_index) {
		switch (new_index) {
		case 2:
			return (tank_point->get_supply());
			break;
		case 3:
			return (anti_tank_point->get_supply());
			break;
		case 4:
			return (infantry_point->get_supply());
			break;
		case 5:
			return (motorised_infantry_point->get_supply());
			break;
		case 6:
			return (supply_car_point->get_supply());
			break;
		default:
			break;
		}
	}

	int get_armor(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_armor());;
			break;
		case 2:
			return (tank_point->get_armor());
			break;
		case 3:
			return (anti_tank_point->get_armor());
			break;
		case 4:
			return (infantry_point->get_armor());
			break;
		case 5:
			return (motorised_infantry_point->get_armor());
			break;
		case 6:
			return (supply_car_point->get_armor());
			break;
		default:
			break;
		}
	}

	int get_ID(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_ID());;
			break;
		case 2:
			return (tank_point->get_ID());
			break;
		case 3:
			return (anti_tank_point->get_ID());
			break;
		case 4:
			return (infantry_point->get_ID());
			break;
		case 5:
			return (motorised_infantry_point->get_ID());
			break;
		case 6:
			return (supply_car_point->get_ID());
			break;
		default:
			break;
		}
	}

	void set_mobility(int new_index, int new_mobility) {
		switch (new_index) {
		case 2:
			tank_point->set_mobility(new_mobility);
			break;
		case 3:
			anti_tank_point->set_mobility(new_mobility);
			break;
		case 4:
			infantry_point->set_mobility(new_mobility);
			break;
		case 5:
			motorised_infantry_point->set_mobility(new_mobility);
			break;
		case 6:
			supply_car_point->set_mobility(new_mobility);
			break;
		default:
			break;
		}
	}

	void set_health(int new_index, int new_health) {
		switch (new_index) {
		case 1:
			construction_point->set_health(new_health);
			break;
		case 2:
			tank_point->set_health(new_health);
			break;
		case 3:
			anti_tank_point->set_health(new_health);
			break;
		case 4:
			infantry_point->set_health(new_health);
			break;
		case 5:
			motorised_infantry_point->set_health(new_health);
			break;
		case 6:
			supply_car_point->set_health(new_health);
			break;
		default:
			break;
		}
	}

	void set_supply(int new_index, int new_supply) {
		switch (new_index) {
		case 2:
			tank_point->set_supply(new_supply);
			break;
		case 3:
			anti_tank_point->set_supply(new_supply);
			break;
		case 4:
			infantry_point->set_supply(new_supply);
			break;
		case 5:
			motorised_infantry_point->set_supply(new_supply);
			break;
		case 6:
			supply_car_point->set_supply(new_supply);
			break;
		default:
			break;
		}
	}
};

buffer* matrix_units_points[size_field_x][size_field_y];//Массив юнитов

void print(int matrix[size_field_x][size_field_y]) {
	for (int j = 0; j < size_field_y; j++) {
		for (int i = 0; i < size_field_x; i++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void create_matrix_control() {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_control[i][j] = neutral;
		}
	}
	matrix_control[0][0] = red;
	matrix_control[1][0] = red;
	matrix_control[0][1] = red;
	matrix_control[1][1] = red;

	matrix_control[size_field_x - 1][size_field_y - 1] = blue;
	matrix_control[size_field_x - 2][size_field_y - 1] = blue;
	matrix_control[size_field_x - 1][size_field_y - 2] = blue;
	matrix_control[size_field_x - 2][size_field_y - 2] = blue;
}

void create_matrix_mode() {
	for (int i = 0; i < count_mode; i++) {
		matrix_mode[i] = 0;
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

void clear_resurce() {
	for (int i = 1; i < size_field_x - 1; i++) {
		for (int j = 1; j < size_field_y - 1; j++) {
			if (matrix_resources[i][j] != null) {
				if (matrix_resources[i - 1][j] == null and matrix_resources[i + 1][j] == null and matrix_resources[i][j - 1] == null and matrix_resources[i][j + 1] == null) {
					matrix_resources[i][j] = null;
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

void genetate_resource() {
	srand(time(0));
	int rand_element;
	int claster_size_spawn_rate = 5;
	int claster_spawn_rate = 2;
	int new_element;
	int new_res;
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (i == 0 or j == 0) {
				matrix_resources[i][j] = null;
			}
			else {
				new_element = rand() % 32;
				if (matrix_resources[i - 1][j] != null) {
					if (new_element <= claster_size_spawn_rate) {
						matrix_resources[i][j] = matrix_resources[i - 1][j];
					}
					else {
						matrix_resources[i][j] = null;
					}
				}
				else if (matrix_resources[i][j - 1] != null) {
					if (new_element <= claster_size_spawn_rate) {
						matrix_resources[i][j] = matrix_resources[i][j - 1];
					}
					else {
						matrix_resources[i][j] = null;
					}
				}
				else {
					if (new_element <= claster_spawn_rate) {
						new_res = rand() % null;
						if (new_res == oil) {
							matrix_resources[i][j] = oil;
						}
						else if (new_res == coal) {
							matrix_resources[i][j] = coal;
						}
						else {
							matrix_resources[i][j] = iron;
						}

					}
					else {
						matrix_resources[i][j] = null;
					}
				}
			}
		}
	}
	reflect_reliesf(matrix_resources);
	clear_resurce();
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
	Image image_oil;
	Texture oil_textures;
	image_oil.loadFromFile("oil.png");
	oil_textures.loadFromImage(image_oil);
	textures_resources.push_back(oil_textures);

	Image image_iron;
	Texture texture_iron;
	image_iron.loadFromFile("iron.png");
	texture_iron.loadFromImage(image_iron);
	textures_resources.push_back(texture_iron);

	Image image_coal;
	Texture texture_coal;
	image_coal.loadFromFile("coal.png");
	texture_coal.loadFromImage(image_coal);
	textures_resources.push_back(texture_coal);

	Image image_field;
	Texture texture_field;
	image_field.loadFromFile("field_30px.png");
	texture_field.loadFromImage(image_field);
	textures_relief.push_back(texture_field);

	Image image_forets;
	Texture texture_forets;
	image_forets.loadFromFile("forest_30px.png");
	texture_forets.loadFromImage(image_forets);
	textures_relief.push_back(texture_forets);

	Image image_mount;
	Texture texture_mount;
	image_mount.loadFromFile("mount_30px.png");
	texture_mount.loadFromImage(image_mount);
	textures_relief.push_back(texture_mount);

	Image image_infantry;
	Texture texture_infantry;
	image_infantry.loadFromFile("blue_infantry.png");
	texture_infantry.loadFromImage(image_infantry);
	textures_blue_units.push_back(texture_infantry);

	Image image_jaeger;
	Texture texture_jaeger;
	image_jaeger.loadFromFile("blue_jaeger.png");
	texture_jaeger.loadFromImage(image_jaeger);
	textures_blue_units.push_back(texture_jaeger);

	Image image_mount_infantry;
	Texture texture_mount_infantry;
	image_mount_infantry.loadFromFile("blue_mount_infantry.png");
	texture_mount_infantry.loadFromImage(image_mount_infantry);
	textures_blue_units.push_back(texture_mount_infantry);
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

	Vector2f scale = zoom_to_scale(zoom);

	Sprite sprite_field;
	Sprite sprite_forest;
	Sprite sprite_mount;

	sprite_field.setTexture(textures_relief[field]);
	sprite_field.setScale(scale);
	sprite_forest.setTexture(textures_relief[forest]);
	sprite_forest.setScale(scale);
	sprite_mount.setTexture(textures_relief[mount]);
	sprite_mount.setScale(scale);

	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
			rectangle.setFillColor(get_color(matrix_relief[i][j]));
			window.draw(rectangle);
			if (matrix_relief[i][j] == field) {
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

void paint_resource(int x_camera, int y_camera, int zoom) {
	Vector2f scale = zoom_to_scale(zoom);

	Sprite sprite_oil;
	Sprite sprite_iron;
	Sprite sprite_coal;

	sprite_oil.setTexture(textures_resources[oil]);
	sprite_oil.setScale(scale);
	sprite_iron.setTexture(textures_resources[iron]);
	sprite_iron.setScale(scale);
	sprite_coal.setTexture(textures_resources[coal]);
	sprite_coal.setScale(scale);

	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_resources[i][j] == oil) {
				sprite_oil.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_oil);

			}
			else if (matrix_resources[i][j] == iron) {
				sprite_iron.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_iron);

			}
			else if (matrix_resources[i][j] == coal) {
				sprite_coal.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_coal);
			}


		}
	}
}

void paint_units(int x_camera, int y_camera, int zoom) {//Допилить под новые реалии, но потом
	int type_units;
	Vector2f scale = zoom_to_scale(zoom);
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	Sprite test;
	test.setTexture(textures_blue_units[mount_infantry]);
	test.setScale(scale);
	test.setPosition(0, 0);

	window.draw(test);
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

void paint_control(int x_camera, int y_camera, int zoom) {
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_control[i][j] == red) {
				rectangle.setFillColor(red_color);
				rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(rectangle);

			}
			else if (matrix_control[i][j] == blue) {
				rectangle.setFillColor(blue_color);
				rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(rectangle);

			}


		}
	}
}

void paint_grid(int x_camera, int y_camera, int zoom) {
	VertexArray line(Lines, 2);
	line[0].color = Color::Black;
	line[1].color = Color::Black;
	for (int i = 0; i < size_field_x; i++) {
		line[0].position = sf::Vector2f(i * size_cell * zoom + x_camera, 0);
		line[1].position = sf::Vector2f(i * size_cell * zoom + x_camera, size_window_y);
		window.draw(line);
		line[0].position = sf::Vector2f(0, i * size_cell * zoom + y_camera);
		line[1].position = sf::Vector2f(size_window_x, i * size_cell * zoom + y_camera);
		window.draw(line);
	}
}

void paint_map_mode() {
	RectangleShape rectangle(Vector2f(size_window_x, player_bar_size_y));
	rectangle.setFillColor({ 100, 100 ,100 });
	rectangle.setPosition(0, size_window_y - player_bar_size_y);
	window.draw(rectangle);
}

void paint_player_bar() {
	RectangleShape rectangle2(Vector2f(player_bar_size_x, size_window_y));
	rectangle2.setFillColor({ 100, 100 ,100 });
	rectangle2.setPosition(size_window_x - player_bar_size_x, 0);
	window.draw(rectangle2);
}

void paint_game(int x_camera, int y_camera, int zoom) {
	paint_relief(x_camera, y_camera, zoom);
	if (matrix_mode[control_mode]) {
		paint_control(x_camera, y_camera, zoom);
	}
	if (matrix_mode[grid_mode]) {
		paint_grid(x_camera, y_camera, zoom);
	}
	if (matrix_mode[resources_mode]) {
		paint_resource(x_camera, y_camera, zoom);
	}
	if (matrix_mode[unit_mode]) {
		paint_units(x_camera, y_camera, zoom);
	}
	paint_map_mode();
	paint_player_bar();

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
	if (x_camera < -(size_cell * size_field_x * zoom - size_window_x + player_bar_size_x)) {
		x_camera = -(size_cell * size_field_x * zoom - size_window_x + player_bar_size_x);
	}
	if (y_camera > 0) {
		y_camera = 0;
	}
	if (y_camera < -(size_cell * size_field_y * zoom - size_window_y + player_bar_size_y)) {
		y_camera = -(size_cell * size_field_y * zoom - size_window_y + player_bar_size_y);
	}
}

void change_zoom(Event event, int& zoom, int& x_camera, int& y_camera) {
	if (event.mouseWheelScroll.delta == 1 and zoom < max_zoom) {
		Vector2i mousePos;
		mousePos = Mouse::getPosition(window);
		x_camera -= mousePos.x;
		y_camera -= mousePos.y;
		zoom++;
	}
	if (event.mouseWheelScroll.delta == -1 and zoom > min_zoom) {
		Vector2i mousePos;
		mousePos = Mouse::getPosition(window);
		x_camera += mousePos.x;
		y_camera += mousePos.y;
		zoom--;
	}
	if (x_camera < -(size_cell * size_field_x * zoom - size_window_x + player_bar_size_x)) {
		x_camera = -(size_cell * size_field_x * zoom - size_window_x + player_bar_size_x);
	}
	if (y_camera < -(size_cell * size_field_y * zoom - size_window_y + player_bar_size_y)) {
		y_camera = -(size_cell * size_field_y * zoom - size_window_y + player_bar_size_y);
	}
	if (y_camera > 0) {
		y_camera = 0;
	}
	if (x_camera > 0) {

		x_camera = 0;
	}
}

vector<int> select_element(Event event, int& zoom, int& x_camera, int& y_camera) {//Костыль
	vector<int> coord;
	Vector2i mousePos;
	mousePos = Mouse::getPosition(window);
	coord.push_back((mousePos.x - x_camera) / (size_cell * zoom));
	coord.push_back((mousePos.y - y_camera) / (size_cell * zoom));
	return coord;
}

void game() {

	string last_bind = "none";
	load_texture();
	generate_relief();
	int x_camera = 0;
	int y_camera = 0;
	int zoom = 4;
	Vector2i old_mousePos;
	Vector2i step;
	Event event;
	window.setKeyRepeatEnabled(false);
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and last_bind != "left") {//Костыль
				select_element(event, zoom, x_camera, y_camera);
				last_bind = "left";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) and last_bind != "control_mode")
			{
				matrix_mode[control_mode] = not matrix_mode[control_mode];
				last_bind = "control_mode";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) and last_bind != "grid_mode")
			{
				matrix_mode[grid_mode] = not matrix_mode[grid_mode];
				last_bind = "grid_mode";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) and last_bind != "resources_mode")
			{
				matrix_mode[resources_mode] = not matrix_mode[resources_mode];
				last_bind = "resources_mode";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) and last_bind != "unit_mode")
			{
				matrix_mode[unit_mode] = not matrix_mode[unit_mode];
				last_bind = "unit_mode";
			}
			if (event.type == Event::Closed)
				window.close();

			old_mousePos = Mouse::getPosition(window);

		}
		paint_game(x_camera, y_camera, zoom);
		window.display();
		last_bind = "none";
	}
}

int main()
{
	genetate_resource();
	create_matrix_control();
	create_matrix_mode();
	matrix_unit_to_zero();

	game();
	return 0;
}