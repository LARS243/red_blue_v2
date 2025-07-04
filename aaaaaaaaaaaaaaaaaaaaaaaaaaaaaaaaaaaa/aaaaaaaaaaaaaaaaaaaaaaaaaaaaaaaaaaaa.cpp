﻿#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;
using namespace sf;

const int ID_no_select = -1;
const int ID_black_hole = 0;
const int ID_construction = 1;
const int ID_tank = 2;
const int ID_anti_tank = 3;
const int ID_infantry = 4;
const int ID_motorised_infantry = 5;
const int ID_supply_car = 6;
const int ID_mount_infantry = 7;
const int ID_forest_infantry = 8;

const int supply_step = 5;
const int max_supply_tank = 10;
const int max_supply_supply_car = 20;
const int max_supply_infantry = 10;
const int max_supply_mount_infantry = 10;
const int max_supply_forest_infantry = 10;
const int max_supply_anti_tank = 10;
const int max_supply_motorised_infantry = 10;

const int health_step = 5;
const int max_health_tank = 40;
const int max_health_supply_car = 5;
const int max_health_infantry = 15;
const int max_health_mount_infantry = 30;
const int max_health_forest_infantry = 20;
const int max_health_anti_tank = 20;
const int max_health_motorised_infantry = 20;

//const int mobility_step = 1000;
const int max_mobility_tank = 10;
const int max_mobility_supply_car = 15;
const int max_mobility_infantry = 5;
const int max_mobility_mount_infantry = 5;
const int max_mobility_forest_infantry = 5;
const int max_mobility_anti_tank = 5;
const int max_mobility_motorised_infantry = 15;

const int supply_for_techicals_to_attack_on_mount = 8;
const int supply_for_mount_infantry_to_attack_on_mount = 2;
const int supply_for_other_to_attack_on_mount = 5;
const int supply_for_techicals_to_attack_in_forest = 5;
const int supply_for_forest_infantry_to_attack_in_forest = 2;
const int supply_for_other_to_attack_in_forest = 3;
const int supply_for_techicals_to_attack_on_field = 2;
const int supply_for_other_to_attack_on_field = 2;

const int size_window_x = 2000;
const int size_window_y = 1000;

const int player_bar_size_y = 200;
const int player_bar_size_x = 300;

float window_zoom_x = 1;
float window_zoom_y = 1;

const int size_field_x = 57;
const int size_field_y = 28;
const int max_zoom = 4;
const int min_zoom = 1;
const int size_cell = 30;

const int count_mode = 6;
const int count_player_bar = 4;

const int control_mode = 0;
const int supply_mode = 1;
const int grid_mode = 2;
const int resources_mode = 3;
const int builds_mode = 4;
const int unit_mode = 5;
const int size_step_mode = 300;

const int field = 0;
const int forest = 1;
const int mount = 2;

const int oil = 0;
const int iron = 1;
const int coal = 2;
const int null_res = 3;
const int steel = 4;
const int fuel = 5;

const int sup_steel = 0;
const int sup_iron = 1;
const int sup_coal = 2;
const int sup_oil = 3;
const int sup_fuel = 4;

const int null = -1;
const int town = 0;
const int blue_base = 1;
const int factory_car = 2;
const int factory_dop = 3;
const int factory_fuel = 4;
const int factory_rifle = 5;
const int factory_steel = 6;
const int factory_tank = 7;
const int millitary_storage = 8;
const int mine = 9;
const int oil_tower = 10;
const int red_base = 11;
const int storage = 12;
const int supply_center = 13;

const int cost_factory_car = 0;
const int cost_factory_dop = 1;
const int cost_factory_fuel = 2;
const int cost_factory_rifle = 3;
const int cost_factory_tank = 4;
const int cost_millitary_storage = 5;
const int cost_factory_steel = 6;
const int cost_mine = 7;
const int cost_oil_tower = 8;
const int cost_storage = 9;
const int cost_supply_center = 10;
const int cost_rail_road = 11;

const int build_menu = 0;
const int res_menu = 1;
const int weap_menu = 2;
const int unit_build_menu = 3;

const int rail_road = 0;
const int rail_town = 1;
const int rail_supply_center = 2;
const int rail_base = 3;

const int neutral = 0;
const int red = 1;
const int blue = 2;

const int blue_jaeger = 0;
const int red_jaeger = 1;
const int blue_mount_infantry = 2;
const int red_mount_infantry = 3;
const int blue_infantry = 4;
const int red_infantry = 5;
const int blue_moto = 6;
const int red_moto = 7;
const int blue_PTO = 8;
const int red_PTO = 9;
const int blue_sup = 10;
const int red_sup = 11;
const int blue_tank = 12;
const int red_tank = 13;

const int infantry_ = 0;
const int jager_ = 1;
const int mount_infantry_ = 2;
const int moto_ = 3;
const int PTO_ = 4;
const int sup_ = 5;
const int tank_ = 6;

const int stat_hp = 0;
const int stat_eq = 1;
const int stat_mobility = 2;
const int stat_soft = 3;
const int stat_hard = 4;

const Color field_color = { 40, 100, 0 };
const Color forest_color = { 0,69,36 };
const Color mount_color = { 150, 150, 150 };
const Color black_for_Oleg = { 0, 0, 0 };
const Color red_color = { 255,0,0, 100 };
const Color blue_color = { 0, 0, 255 , 100 };
const Color green_color = { 0,169,36 };
const Color choose_color = { 115, 200, 55, 200 };
const Color orange_color = { 255, 165, 0, 100 };

RenderWindow window(VideoMode(size_window_x, size_window_y), "shiiit");

vector<Texture> textures_relief;
vector<Texture> textures_resources;
vector<Texture> textures_units;
vector<Texture> textures_modes;
vector<Texture> textures_builds;
vector<Texture> textures_roads;
vector<Texture> textures_player_bar;
vector<Texture> textures_sup_res;
vector<Texture> textures_sup_mil;
vector<Texture> textures_stats;


int matrix_relief[size_field_x][size_field_y];
int matrix_units_id[size_field_x][size_field_y];
int matrix_resources[size_field_x][size_field_y];
int matrix_control[size_field_x][size_field_y];
int matrix_builds[size_field_x][size_field_y];
int matrix_roads[size_field_x][size_field_y];
int matrix_rail_web[size_field_x][size_field_y];
int matrix_supply_zone[size_field_x][size_field_y];

int matrix_build_zone[size_field_x][size_field_y];

int matrix_unit_mobility[size_field_x][size_field_y];


int zone_building_red[size_field_x][size_field_y];
int zone_building_blue[size_field_x][size_field_y];

int cost_buildings[cost_rail_road + 1];
int cost_units[7] = {10, 20, 20, 10, 20, 10, 10 };

bool matrix_mode[count_mode];
bool matrix_player_bar[count_player_bar];
bool choose_build = false;

const int red_player = 1;
const int blue_player = 2;
int player = red_player;
int unit_x = -1;
int unit_y = -1;

class Player_res {
private:
	int steel_;
	int iron_;
	int coal_;
	int oil_;
	int fuel_;

	int rifle_;
	int dop_;
	int car_;
	int tank_;

	int max_res;
	int max_eq;

public:
	Player_res() {
		steel_ = 20;
		iron_ = 0;
		coal_ = 0;
		oil_ = 0;
		fuel_ = 100;
		rifle_ = 0;
		dop_ = 0;
		car_ = 0;
		tank_ = 0;
		max_res = 20;
		max_eq = 20;
	}
	int get_steel() {
		return steel_;
	}
	int get_iron() {
		return iron_;
	}
	int get_coal() {
		return coal_;
	}
	int get_oil() {
		return oil_;
	}
	int get_fuel() {
		return fuel_;
	}

	int get_rifle() {
		return rifle_;
	}
	int get_dop() {
		return dop_;
	}
	int get_car() {
		return car_;
	}
	int get_tank() {
		return tank_;
	}

	int get_max_res() {
		return max_res;
	}
	int get_max_eq() {
		return max_eq;
	}

	void set_steel(int new_steel_) {
		steel_ = new_steel_;
		if (steel_ > max_res) {
			steel_ = max_res;
		}
	}
	void set_iron(int new_iron_) {
		iron_ = new_iron_;
		if (iron_ > max_res) {
			iron_ = max_res;
		}
	}
	void set_coal(int new_coal_) {
		coal_ = new_coal_;
		if (coal_ > max_res) {
			coal_ = max_res;
		}
	}
	void set_oil(int new_oil_) {
		oil_ = new_oil_;
		if (oil_ > max_res) {
			oil_ = max_res;
		}
	}
	void set_fuel(int new_fuel_) {
		fuel_ = new_fuel_;
		if (fuel_ > max_res) {
			fuel_ = max_res;
		}
	}

	void set_rifle(int new_rifle_) {
		rifle_ = new_rifle_;
		if (rifle_ > max_eq) {
			rifle_ = max_eq;
		}
	}
	void set_dop(int new_dop_) {
		dop_ = new_dop_;
		if (dop_ > max_eq) {
			dop_ = max_eq;
		}
	}
	void set_car(int new_car_) {
		car_ = new_car_;
		if (car_ > max_eq) {
			car_ = max_eq;
		}
	}
	void set_tank(int new_tank_) {
		tank_ = new_tank_;
		if (tank_ > max_eq) {
			tank_ = max_eq;
		}
	}

	void set_max_res(int new_max_res) {
		max_res = new_max_res;
	}
	void set_max_eq(int new_max_eq) {
		max_eq = new_max_eq;
	}
};

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
	int player;
	int damage_to_living_force = 0;
	int damage_to_war_machine = 0;
	int mobility = 0;
	int supply = 0;
public:
	construction(int new_player) {
		health = 200;
		armor = 50;
		ID = ID_construction;
		player = new_player;
		damage_to_living_force = 0;
		damage_to_war_machine = 0;
		mobility = 0;
		supply = 0;
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
	int get_player() {
		return(player);
	}
	void set_health(int new_health) {
		health = new_health;
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
	int player;
public:
	tank(int new_player) {
		health = max_health_tank;
		damage_to_living_force = 10;
		damage_to_war_machine = 10;
		mobility = max_mobility_tank;
		supply = max_supply_tank;
		armor = 50;
		ID = ID_tank;
		player = new_player;
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
	int get_player() {
		return(player);
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
	int player;

public:
	anti_tank(int new_player) {
		health = max_health_anti_tank;
		damage_to_living_force = 2;
		damage_to_war_machine = 15;
		mobility = max_mobility_anti_tank;
		supply = max_supply_anti_tank;
		armor = 50;
		ID = ID_anti_tank;
		player = new_player;
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
	int get_player() {
		return(player);
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
	int player;

public:
	infantry(int new_player) {
		health = max_health_infantry;
		damage_to_living_force = 4;
		damage_to_war_machine = 4;
		mobility = max_mobility_infantry;
		supply = max_supply_infantry;
		armor = 50;
		ID_infantry;
		player = new_player;
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
	int get_player() {
		return(player);
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
	int player;

public:
	motorised_infantry(int new_player) {
		health = max_health_motorised_infantry;
		damage_to_living_force = 5;
		damage_to_war_machine = 4;
		mobility = max_mobility_motorised_infantry;
		supply = max_supply_motorised_infantry;
		armor = 50;
		ID = ID_motorised_infantry;
		player = new_player;
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
	int get_player() {
		return(player);
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
	int player;

public:
	supply_car(int new_player) {
		health = max_health_supply_car;
		damage_to_living_force = 0;
		damage_to_war_machine = 0;
		mobility = max_mobility_supply_car;
		supply_for_supply = max_supply_supply_car;
		armor = 50;
		ID = ID_supply_car;
		player = new_player;
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
	int get_player() {
		return (player);
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

class mount_infantry {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;
	int armor;
	int ID;
	int player;

public:
	mount_infantry(int new_player) {
		health = max_health_mount_infantry;
		damage_to_living_force = 10;
		damage_to_war_machine = 6;
		mobility = max_mobility_mount_infantry;
		supply = max_supply_mount_infantry;
		armor = 50;
		ID = ID_motorised_infantry;
		player = new_player;
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
	int get_player() {
		return(player);
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

class forest_infantry {
private:
	int health;
	int damage_to_living_force;
	int damage_to_war_machine;
	int mobility;
	int supply;
	int armor;
	int ID;
	int player;

public:
	forest_infantry(int new_player) {
		health = max_health_forest_infantry;
		damage_to_living_force = 10;
		damage_to_war_machine = 4;
		mobility = max_mobility_forest_infantry;
		supply = max_supply_forest_infantry;
		armor = 50;
		ID = ID_motorised_infantry;
		player = new_player;
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
	int get_player() {
		return(player);
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

class buffer {
private:
	int index;
	construction* construction_point = nullptr;
	tank* tank_point = nullptr;
	anti_tank* anti_tank_point = nullptr;
	infantry* infantry_point = nullptr;
	motorised_infantry* motorised_infantry_point = nullptr;
	supply_car* supply_car_point = nullptr;
	mount_infantry* mount_infantry_point = nullptr;
	forest_infantry* forest_infantry_point = nullptr;

public:
	buffer(int new_index, int player) {
		switch (new_index) {
		case 1:
			construction_point = new construction(player);
			index = new_index;
			break;
		case 2:
			tank_point = new tank(player);
			index = new_index;
			break;
		case 3:
			anti_tank_point = new anti_tank(player);
			index = new_index;
			break;
		case 4:
			infantry_point = new infantry(player);
			index = new_index;
			break;
		case 5:
			motorised_infantry_point = new motorised_infantry(player);
			index = new_index;
			break;
		case 6:
			supply_car_point = new supply_car(player);
			index = new_index;
			break;
		case 7:
			mount_infantry_point = new mount_infantry(player);
			index = new_index;
		case 8:
			forest_infantry_point = new forest_infantry(player);
			index = new_index;
		default:
			break;
		}
	}

	int get_player(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_player());
			break;
		case 2:
			return (tank_point->get_player());
			break;
		case 3:
			return (anti_tank_point->get_player());
			break;
		case 4:
			return (infantry_point->get_player());
			break;
		case 5:
			return (motorised_infantry_point->get_player());
			break;
		case 6:
			return (supply_car_point->get_player());
			break;
		case 7:
			return (mount_infantry_point->get_player());
			break;
		case 8:
			return (forest_infantry_point->get_player());
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
		case 7:
			return (mount_infantry_point->get_health());
			break;
		case 8:
			return (forest_infantry_point->get_health());
			break;
		default:
			break;
		}
	}

	int get_damage_to_living_force(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_damage_to_living_force());
			break;
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
		case 7:
			return (mount_infantry_point->get_damage_to_living_force());
			break;
		case 8:
			return (forest_infantry_point->get_damage_to_living_force());
			break;
		default:
			break;
		}
	}

	int get_damage_to_war_machine(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_damage_to_war_machine());
			break;
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
		case 7:
			return (mount_infantry_point->get_damage_to_war_machine());
			break;
		case 8:
			return (forest_infantry_point->get_damage_to_war_machine());
			break;
		default:
			break;
		}
	}

	int get_mobility(int new_index) {
		
		switch (new_index) {
		case 1:
			return (construction_point->get_mobility());
			break;
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
		case 7:
			return (mount_infantry_point->get_mobility());
			break;
		case 8:
			return (forest_infantry_point->get_mobility());
			break;
		default:
			break;
		}
	}

	int get_supply(int new_index) {
		switch (new_index) {
		case 1:
			return (construction_point->get_supply());
			break;
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
		case 7:
			return (mount_infantry_point->get_supply());
			break;
		case 8:
			return (forest_infantry_point->get_supply());
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
		case 7:
			return (mount_infantry_point->get_armor());
			break;
		case 8:
			return (forest_infantry_point->get_armor());
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
		case 7:
			return (mount_infantry_point->get_ID());
			break;
		case 8:
			return (forest_infantry_point->get_ID());
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
		case 7:
			mount_infantry_point->set_mobility(new_mobility);
			break;
		case 8:
			forest_infantry_point->set_mobility(new_mobility);
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
		case 7:
			mount_infantry_point->set_health(new_health);
			break;
		case 8:
			forest_infantry_point->set_health(new_health);
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
		case 7:
			mount_infantry_point->set_supply(new_supply);
			break;
		case 8:
			forest_infantry_point->set_supply(new_supply);
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


int max_supply(int& x, int& y) {
	if (matrix_units_id[x][y] == ID_tank) {
		return(max_supply_tank);
	}
	if (matrix_units_id[x][y] == ID_anti_tank) {
		return(max_supply_anti_tank);
	}
	if (matrix_units_id[x][y] == ID_infantry) {
		return(max_supply_infantry);
	}
	if (matrix_units_id[x][y] == ID_motorised_infantry) {
		return(max_supply_motorised_infantry);
	}
	if (matrix_units_id[x][y] == ID_forest_infantry) {
		return(max_supply_forest_infantry);
	}
	if (matrix_units_id[x][y] == ID_mount_infantry) {
		return(max_supply_mount_infantry);
	}
	if (matrix_units_id[x][y] == ID_supply_car) {
		return(max_supply_supply_car);
	}
}

int max_health(int& x, int& y) {
	if (matrix_units_id[x][y] == ID_tank) {
		return(max_health_tank);
	}
	if (matrix_units_id[x][y] == ID_anti_tank) {
		return(max_health_anti_tank);
	}
	if (matrix_units_id[x][y] == ID_infantry) {
		return(max_health_infantry);
	}
	if (matrix_units_id[x][y] == ID_motorised_infantry) {
		return(max_health_motorised_infantry);
	}
	if (matrix_units_id[x][y] == ID_forest_infantry) {
		return(max_health_forest_infantry);
	}
	if (matrix_units_id[x][y] == ID_mount_infantry) {
		return(max_health_mount_infantry);
	}
	if (matrix_units_id[x][y] == ID_supply_car) {
		return(max_health_supply_car);
	}
}

int max_mobility(int& x, int& y) {
	if (matrix_units_id[x][y] == ID_tank) {
		return(max_mobility_tank);
	}
	if (matrix_units_id[x][y] == ID_anti_tank) {
		return(max_mobility_anti_tank);
	}
	if (matrix_units_id[x][y] == ID_infantry) {
		return(max_mobility_infantry);
	}
	if (matrix_units_id[x][y] == ID_motorised_infantry) {
		return(max_mobility_motorised_infantry);
	}
	if (matrix_units_id[x][y] == ID_forest_infantry) {
		return(max_mobility_forest_infantry);
	}
	if (matrix_units_id[x][y] == ID_mount_infantry) {
		return(max_mobility_mount_infantry);
	}
	if (matrix_units_id[x][y] == ID_supply_car) {
		return(max_mobility_supply_car);
	}
}

void create_matrix_control() {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			/*if (i < size_field_x / 2) {
				matrix_control[i][j] = red;
			}
			else {
				matrix_control[i][j] = blue;
			}*/
			matrix_control[i][j] = neutral;
		}
	}
	matrix_control[0][0] = red;
	matrix_control[0][1] = red;
	matrix_control[0][2] = red;

	matrix_control[1][0] = red;
	matrix_control[1][1] = red;
	matrix_control[1][2] = red;

	matrix_control[2][2] = red;
	matrix_control[2][0] = red;
	matrix_control[2][1] = red;
	matrix_control[4][4] = blue;


	matrix_control[size_field_x - 3][size_field_y - 3] = blue;
	matrix_control[size_field_x - 2][size_field_y - 3] = blue;
	matrix_control[size_field_x - 3][size_field_y - 2] = blue;
	matrix_control[size_field_x - 1][size_field_y - 3] = blue;
	matrix_control[size_field_x - 3][size_field_y - 1] = blue;

	matrix_control[size_field_x - 2][size_field_y - 2] = blue;
	matrix_control[size_field_x - 2][size_field_y - 1] = blue;
	matrix_control[size_field_x - 1][size_field_y - 2] = blue;

	matrix_control[size_field_x - 1][size_field_y - 1] = blue;
}

void create_matrix_mode() {
	for (int i = 0; i < count_mode; i++) {
		matrix_mode[i] = 0;
	}
}

void create_matrix_roads() {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_builds[i][j] == town) {
				matrix_roads[i][j] = rail_town;
			}
			else {
				matrix_roads[i][j] = null;
			}
		}

	}
	matrix_roads[1][1] = rail_base;
	matrix_roads[size_field_x - 3][size_field_x - 3] = rail_base;
}

void create_cost_buildings() {
	cost_buildings[cost_factory_car] = 10;
	cost_buildings[cost_factory_dop] = 6;
	cost_buildings[cost_factory_fuel] = 4;
	cost_buildings[cost_factory_rifle] = 6;
	cost_buildings[cost_factory_steel] = 4;
	cost_buildings[cost_factory_tank] = 10;
	cost_buildings[cost_millitary_storage] = 4;
	cost_buildings[cost_mine] = 4;
	cost_buildings[cost_oil_tower] = 4;
	cost_buildings[cost_rail_road] = 2;
	cost_buildings[cost_storage] = 4;
	cost_buildings[cost_supply_center] = 6;
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
			if (matrix_resources[i][j] != null_res) {
				if (matrix_resources[i - 1][j] == null_res and matrix_resources[i + 1][j] == null_res and matrix_resources[i][j - 1] == null_res and matrix_resources[i][j + 1] == null_res) {
					matrix_resources[i][j] = null_res;
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

void read_relief() {
	std::string line;

	std::ifstream in("generated_map.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		string g = "G";
		string m = "M";
		string w = "W";
		int y = 0;
		system("MapGenerator.exe");
		while (std::getline(in, line))
		{
			for (int x = 0; x < line.size(); x++) {
				if (line[x] == g) {
					matrix_relief[x][y] = field;
				}
				if (line[x] == m) {
					matrix_relief[x][y] = mount;
				}
				if (line[x] == w) {
					matrix_relief[x][y] = forest;
				}

			}
			y++;
			cout << "\n";

		}
	}
	in.close();     // закрываем файл
	clear_field(matrix_relief);
	reflect_reliesf(matrix_relief);
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
				matrix_resources[i][j] = null_res;
			}
			else {
				new_element = rand() % 32;
				if (matrix_resources[i - 1][j] != null_res) {
					if (new_element <= claster_size_spawn_rate) {
						matrix_resources[i][j] = matrix_resources[i - 1][j];
					}
					else {
						matrix_resources[i][j] = null_res;
					}
				}
				else if (matrix_resources[i][j - 1] != null_res) {
					if (new_element <= claster_size_spawn_rate) {
						matrix_resources[i][j] = matrix_resources[i][j - 1];
					}
					else {
						matrix_resources[i][j] = null_res;
					}
				}
				else {
					if (new_element <= claster_spawn_rate) {
						new_res = rand() % null_res;
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
						matrix_resources[i][j] = null_res;
					}
				}
			}
		}
	}
	reflect_reliesf(matrix_resources);
	clear_resurce();
}

void generate_towns() {
	int rand_element;
	int spawn_rate = 128;
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (i > 1 and j > 1 and i < size_field_x - 2 and j < size_field_y - 2) {
				rand_element = rand() % spawn_rate;
				if (rand_element == town) {
					matrix_builds[i][j] = town;
				}
				else {
					matrix_builds[i][j] = null;
				}
			}
			else {
				matrix_builds[i][j] = null;
			}
		}
	}
	reflect_reliesf(matrix_builds);
	matrix_builds[1][1] = red_base;
	matrix_builds[size_field_x - 2][size_field_y - 2] = blue_base;

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
			matrix_units_id[i][j] = ID_black_hole;
			matrix_unit_mobility[i][j] = null;
		}
	}
	matrix_units_id[1][1] = ID_construction;
	matrix_units_points[1][1] = new buffer(ID_construction, red_player);
	matrix_units_id[1][2] = ID_motorised_infantry;
	matrix_units_points[1][2] = new buffer(ID_motorised_infantry, red_player);
	matrix_units_id[2][1] = ID_infantry;
	matrix_units_points[2][1] = new buffer(ID_infantry, red_player);
	matrix_units_id[2][2] = ID_infantry;
	matrix_units_points[2][2] = new buffer(ID_infantry, red_player);
	matrix_units_id[4][4] = ID_infantry;
	matrix_units_points[4][4] = new buffer(ID_infantry, blue_player);

	matrix_units_id[size_field_x - 3][size_field_x - 3] = ID_construction;
	matrix_units_points[size_field_x - 3][size_field_x - 3] = new buffer(ID_construction, blue_player);
	matrix_units_id[size_field_x - 3][size_field_x - 4] = ID_infantry;
	matrix_units_points[size_field_x - 3][size_field_x - 4] = new buffer(ID_infantry, blue_player);
	matrix_units_id[size_field_x - 4][size_field_x - 3] = ID_infantry;
	matrix_units_points[size_field_x - 4][size_field_x - 3] = new buffer(ID_infantry, blue_player);
	matrix_units_id[size_field_x - 4][size_field_x - 4] = ID_infantry;
	matrix_units_points[size_field_x - 4][size_field_x - 4] = new buffer(ID_infantry, blue_player);
}

void matrix_road_to_zero() {
	for (int i = 0; i < size_field_x; i++)
	{
		for (int j = 0; j < size_field_y; j++)
		{
			matrix_unit_mobility[i][j] = null;
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


	Image image_control_mode;
	Texture texture_control_mode;
	image_control_mode.loadFromFile("control_mode.png");
	texture_control_mode.loadFromImage(image_control_mode);
	textures_modes.push_back(texture_control_mode);

	Image image_supply_mode;
	Texture texture_supply_mode;
	image_supply_mode.loadFromFile("supply_mode.png");
	texture_supply_mode.loadFromImage(image_supply_mode);
	textures_modes.push_back(texture_supply_mode);

	Image image_grid_mode;
	Texture texture_grid_mode;
	image_grid_mode.loadFromFile("grid_mode.png");
	texture_grid_mode.loadFromImage(image_grid_mode);
	textures_modes.push_back(texture_grid_mode);

	Image image_resources_mode;
	Texture texture_resources_mode;
	image_resources_mode.loadFromFile("resources_mode.png");
	texture_resources_mode.loadFromImage(image_resources_mode);
	textures_modes.push_back(texture_resources_mode);

	Image image_builds_mode;
	Texture texture_builds_mode;
	image_builds_mode.loadFromFile("builds_mode.png");
	texture_builds_mode.loadFromImage(image_builds_mode);
	textures_modes.push_back(texture_builds_mode);

	Image image_unit_mode;
	Texture texture_unit_mode;
	image_unit_mode.loadFromFile("unit_mode.png");
	texture_unit_mode.loadFromImage(image_unit_mode);
	textures_modes.push_back(texture_unit_mode);

	Image image_town;
	Texture town_textures;
	image_town.loadFromFile("town.png");
	town_textures.loadFromImage(image_town);
	textures_builds.push_back(town_textures);

	Image image_road_1;
	Texture road_1_textures;
	image_road_1.loadFromFile("road_1.png");
	road_1_textures.loadFromImage(image_road_1);
	textures_roads.push_back(road_1_textures);

	Image image_road_2;
	Texture road_2_textures;
	image_road_2.loadFromFile("road_2.png");
	road_2_textures.loadFromImage(image_road_2);
	textures_roads.push_back(road_2_textures);

	Image image_road_3;
	Texture road_3_textures;
	image_road_3.loadFromFile("road_3.png");
	road_3_textures.loadFromImage(image_road_3);
	textures_roads.push_back(road_3_textures);

	Image image_road_4;
	Texture road_4_textures;
	image_road_4.loadFromFile("road_4.png");
	road_4_textures.loadFromImage(image_road_4);
	textures_roads.push_back(road_4_textures);

	Image image_blue_base;
	Texture blue_base_textures;
	image_blue_base.loadFromFile("blue_base.png");
	blue_base_textures.loadFromImage(image_blue_base);
	textures_builds.push_back(blue_base_textures);

	Image image_factory_car;
	Texture factory_car_textures;
	image_factory_car.loadFromFile("factory_car.png");
	factory_car_textures.loadFromImage(image_factory_car);
	textures_builds.push_back(factory_car_textures);

	Image image_factory_dop;
	Texture factory_dop_textures;
	image_factory_dop.loadFromFile("factory_dop.png");
	factory_dop_textures.loadFromImage(image_factory_dop);
	textures_builds.push_back(factory_dop_textures);

	Image image_factory_fuel;
	Texture factory_fuel_textures;
	image_factory_fuel.loadFromFile("factory_fuel.png");
	factory_fuel_textures.loadFromImage(image_factory_fuel);
	textures_builds.push_back(factory_fuel_textures);

	Image image_factory_rifle;
	Texture factory_rifle_textures;
	image_factory_rifle.loadFromFile("factory_rifle.png");
	factory_rifle_textures.loadFromImage(image_factory_rifle);
	textures_builds.push_back(factory_rifle_textures);

	Image image_factory_steel;
	Texture factory_steel_textures;
	image_factory_steel.loadFromFile("factory_steel.png");
	factory_steel_textures.loadFromImage(image_factory_steel);
	textures_builds.push_back(factory_steel_textures);

	Image image_factory_tank;
	Texture factory_tank_textures;
	image_factory_tank.loadFromFile("factory_tank.png");
	factory_tank_textures.loadFromImage(image_factory_tank);
	textures_builds.push_back(factory_tank_textures);

	Image image_millitary_storage;
	Texture millitary_storage_textures;
	image_millitary_storage.loadFromFile("millitary_storage.png");
	millitary_storage_textures.loadFromImage(image_millitary_storage);
	textures_builds.push_back(millitary_storage_textures);

	Image image_mine;
	Texture mine_textures;
	image_mine.loadFromFile("mine.png");
	mine_textures.loadFromImage(image_mine);
	textures_builds.push_back(mine_textures);

	Image image_oil_tower;
	Texture oil_tower_textures;
	image_oil_tower.loadFromFile("oil_tower.png");
	oil_tower_textures.loadFromImage(image_oil_tower);
	textures_builds.push_back(oil_tower_textures);

	Image image_red_base;
	Texture red_base_textures;
	image_red_base.loadFromFile("red_base.png");
	red_base_textures.loadFromImage(image_red_base);
	textures_builds.push_back(red_base_textures);

	Image image_storage;
	Texture storage_textures;
	image_storage.loadFromFile("storage.png");
	storage_textures.loadFromImage(image_storage);
	textures_builds.push_back(storage_textures);

	Image image_supply_center;
	Texture supply_center_textures;
	image_supply_center.loadFromFile("supply_center.png");
	supply_center_textures.loadFromImage(image_supply_center);
	textures_builds.push_back(supply_center_textures);

	Image image_building;
	Texture building_textures;
	image_building.loadFromFile("building.png");
	building_textures.loadFromImage(image_building);
	textures_player_bar.push_back(building_textures);

	Image image_res_list;
	Texture res_list_textures;
	image_res_list.loadFromFile("res_list.png");
	res_list_textures.loadFromImage(image_res_list);
	textures_player_bar.push_back(res_list_textures);

	Image image_weap_list;
	Texture weap_list_textures;
	image_weap_list.loadFromFile("weap_res.png");
	weap_list_textures.loadFromImage(image_weap_list);
	textures_player_bar.push_back(weap_list_textures);

	Image image_unit_building;
	Texture unit_building_textures;
	image_unit_building.loadFromFile("unit_building.png");
	unit_building_textures.loadFromImage(image_unit_building);
	textures_player_bar.push_back(unit_building_textures);

	Image image_sup_steel;
	Texture sup_steel_textures;
	image_sup_steel.loadFromFile("sup_steel.png");
	sup_steel_textures.loadFromImage(image_sup_steel);
	textures_sup_res.push_back(sup_steel_textures);

	Image image_sup_iron;
	Texture sup_iron_textures;
	image_sup_iron.loadFromFile("sup_iron.png");
	sup_iron_textures.loadFromImage(image_sup_iron);
	textures_sup_res.push_back(sup_iron_textures);

	Image image_sup_coal;
	Texture sup_coal_textures;
	image_sup_coal.loadFromFile("sup_coal.png");
	sup_coal_textures.loadFromImage(image_sup_coal);
	textures_sup_res.push_back(sup_coal_textures);

	Image image_sup_oil;
	Texture sup_oil_textures;
	image_sup_oil.loadFromFile("sup_oil.png");
	sup_oil_textures.loadFromImage(image_sup_oil);
	textures_sup_res.push_back(sup_oil_textures);

	Image image_sup_fuel;
	Texture sup_fuel_textures;
	image_sup_fuel.loadFromFile("sup_fuel.png");
	sup_fuel_textures.loadFromImage(image_sup_fuel);
	textures_sup_res.push_back(sup_fuel_textures);


	Image image_sup_rifle;
	Texture sup_rifle_textures;
	image_sup_rifle.loadFromFile("sup_rifle.png");
	sup_rifle_textures.loadFromImage(image_sup_rifle);
	textures_sup_mil.push_back(sup_rifle_textures);

	Image image_sup_dop;
	Texture sup_dop_textures;
	image_sup_dop.loadFromFile("sup_eq.png");
	sup_dop_textures.loadFromImage(image_sup_dop);
	textures_sup_mil.push_back(sup_dop_textures);

	Image image_sup_car;
	Texture sup_car_textures;
	image_sup_car.loadFromFile("sup_car.png");
	sup_car_textures.loadFromImage(image_sup_car);
	textures_sup_mil.push_back(sup_car_textures);

	Image image_sup_tank;
	Texture sup_tank_textures;
	image_sup_tank.loadFromFile("sup_tank.png");
	sup_tank_textures.loadFromImage(image_sup_tank);
	textures_sup_mil.push_back(sup_tank_textures);



	Image image_jaeger;
	Texture texture_jaeger;
	image_jaeger.loadFromFile("blue_jaeger.png");
	texture_jaeger.loadFromImage(image_jaeger);
	textures_units.push_back(texture_jaeger);
	image_jaeger.loadFromFile("red_jaeger.png");
	texture_jaeger.loadFromImage(image_jaeger);
	textures_units.push_back(texture_jaeger);

	Image image_mount_infantry;
	Texture texture_mount_infantry;
	image_mount_infantry.loadFromFile("blue_mount_infantry.png");
	texture_mount_infantry.loadFromImage(image_mount_infantry);
	textures_units.push_back(texture_mount_infantry);
	image_mount_infantry.loadFromFile("red_mount_infantry.png");
	texture_mount_infantry.loadFromImage(image_mount_infantry);
	textures_units.push_back(texture_mount_infantry);

	Image image_infantry;
	Texture texture_infantry;
	image_infantry.loadFromFile("blue_infantry.png");
	texture_infantry.loadFromImage(image_infantry);
	textures_units.push_back(texture_infantry);
	image_infantry.loadFromFile("red_infantry.png");
	texture_infantry.loadFromImage(image_infantry);
	textures_units.push_back(texture_infantry);

	Image image_moto;
	Texture texture_moto;
	image_moto.loadFromFile("blue_moto.png");
	texture_moto.loadFromImage(image_moto);
	textures_units.push_back(texture_moto);
	image_moto.loadFromFile("red_moto.png");
	texture_moto.loadFromImage(image_moto);
	textures_units.push_back(texture_moto);

	Image image_PTO;
	Texture texture_PTO;
	image_PTO.loadFromFile("blue_PTO.png");
	texture_PTO.loadFromImage(image_PTO);
	textures_units.push_back(texture_PTO);
	image_PTO.loadFromFile("red_PTO.png");
	texture_PTO.loadFromImage(image_PTO);
	textures_units.push_back(texture_PTO);

	Image image_sup;
	Texture texture_sup;
	image_sup.loadFromFile("blue_sup.png");
	texture_sup.loadFromImage(image_sup);
	textures_units.push_back(texture_sup);
	image_sup.loadFromFile("red_sup.png");
	texture_sup.loadFromImage(image_sup);
	textures_units.push_back(texture_sup);

	Image image_tank;
	Texture texture_tank;
	image_tank.loadFromFile("blue_tank.png");
	texture_tank.loadFromImage(image_tank);
	textures_units.push_back(texture_tank);
	image_tank.loadFromFile("red_tank.png");
	texture_tank.loadFromImage(image_tank);
	textures_units.push_back(texture_tank);

	Image image_hp;
	Texture texture_hp;
	image_hp.loadFromFile("hp.png");
	texture_hp.loadFromImage(image_hp);
	textures_stats.push_back(texture_hp);

	Image image_eq;
	Texture texture_eq;
	image_eq.loadFromFile("eq.png");
	texture_eq.loadFromImage(image_eq);
	textures_stats.push_back(texture_eq);

	Image image_mobility;
	Texture texture_mobility;
	image_mobility.loadFromFile("mobility.png");
	texture_mobility.loadFromImage(image_mobility);
	textures_stats.push_back(texture_mobility);

	Image image_soft_attack;
	Texture texture_soft_attack;
	image_soft_attack.loadFromFile("soft_attack.png");
	texture_soft_attack.loadFromImage(image_soft_attack);
	textures_stats.push_back(texture_soft_attack);

	Image image_armor_attack;
	Texture texture_armor_attack;
	image_armor_attack.loadFromFile("armor_attack.png");
	texture_armor_attack.loadFromImage(image_armor_attack);
	textures_stats.push_back(texture_armor_attack);
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

int rail_objectrs(int x, int y) {
	if (matrix_roads[x][y] == rail_base or matrix_roads[x][y] == rail_road or matrix_roads[x][y] == rail_supply_center or matrix_roads[x][y] == rail_town) {
		return rail_road;
	}
	else {
		return null;
	}
}

void check_rail_web(int x, int y) {
	if (matrix_rail_web[x][y] == null and matrix_roads[x][y] != null and player == matrix_control[x][y]) {
		matrix_rail_web[x][y] = rail_road;
		if (x + 1 < size_field_x) {
			check_rail_web(x + 1, y);
		}
		if (y + 1 < size_field_y) {
			check_rail_web(x, y + 1);
		}
		if (x - 1 >= 0) {
			check_rail_web(x - 1, y);
		}
		if (y - 1 >= 0) {
			check_rail_web(x, y - 1);
		}
		
	}

}
void start_check_rail_web(int x, int y) {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_rail_web[i][j] = null;
		}
	}
	check_rail_web(x, y);
}

void check_supply_zones(int supply_range, int x, int y) {
	if (supply_range > 0 and matrix_control[x][y] == player) {
		matrix_supply_zone[x][y] = 1;

		if (matrix_relief[x][y] == mount) {
			supply_range -= 3;
		}
		else if (matrix_relief[x][y] == forest) {
			supply_range -= 2;
		}
		else {
			supply_range -= 1;
		}
		if (y - 1 >= 0) {
			check_supply_zones(supply_range, x, y - 1);
		}
		if (x - 1 >= x - 1) {
			check_supply_zones(supply_range, x - 1, y);
		}
		if (y + 1 <= size_field_y) {
			check_supply_zones(supply_range, x, y + 1);
		}
		if (x + 1 <= size_field_x) {
			check_supply_zones(supply_range, x + 1, y);
		}

	}

}
void start_check_supply_zones() {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_supply_zone[i][j] = 0;
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_rail_web[i][j] == rail_road and (matrix_roads[i][j] == rail_town or matrix_roads[i][j] == rail_base) and matrix_control[i][j] == player) {
				check_supply_zones(5, i, j);
			}
			else if (matrix_rail_web[i][j] == rail_road and (matrix_roads[i][j] == rail_supply_center) and matrix_control[i][j] == player) {
				check_supply_zones(4, i, j);
			}
		}
	}
}

void check_build_zones_supply_center(int supply_range, int x, int y) {
	if (supply_range > 0 and matrix_control[x][y] == player) {
		matrix_build_zone[x][y] = 2;
		if (matrix_relief[x][y] == mount) {
			supply_range -= 4;
		}
		else if (matrix_relief[x][y] == forest) {
			supply_range -= 2;
		}
		else {
			supply_range -= 2;
		}
		if (y - 1 >= 0) {

			check_build_zones_supply_center(supply_range, x, y - 1);
		}
		if (x - 1 >= x - 1) {
			check_build_zones_supply_center(supply_range, x - 1, y);
		}
		if (y + 1 <= size_field_y) {
			check_build_zones_supply_center(supply_range, x, y + 1);
		}
		if (x + 1 <= size_field_x) {
			check_build_zones_supply_center(supply_range, x + 1, y);
		}

	}
}

void check_build_zones_town(int supply_range, int x, int y) {
	if (supply_range > 0 and matrix_control[x][y] == player) {
		matrix_build_zone[x][y] = 1;
		if (matrix_relief[x][y] == mount) {
			supply_range -= 4;
		}
		else if (matrix_relief[x][y] == forest) {
			supply_range -= 2;
		}
		else {
			supply_range -= 2;
		}
		if (y - 1 >= 0) {
			check_build_zones_town(supply_range, x, y - 1);
		}
		if (x - 1 >= 0) {
			check_build_zones_town(supply_range, x - 1, y);
		}
		if (y + 1 < size_field_y) {
			check_build_zones_town(supply_range, x, y + 1);
		}
		if (x + 1 < size_field_x) {
			check_build_zones_town(supply_range, x + 1, y);
		}

	}
}
void start_check_build_zones() {
	if (red_player == player) {
		start_check_rail_web(1, 1);
	}
	else {
		start_check_rail_web(size_field_x - 2, size_field_y - 2);
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_build_zone[i][j] = 2000;
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_rail_web[i][j] == rail_road and (matrix_roads[i][j] == rail_supply_center) and matrix_control[i][j] == player) {
				check_build_zones_supply_center(5, i, j);
			}
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_rail_web[i][j] == rail_road and (matrix_roads[i][j] == rail_town or matrix_roads[i][j] == rail_base) and matrix_control[i][j] == player) {
				check_build_zones_town(6, i, j);
			}
		}
	}
}

void update_product(Player_res& player_color) {
	const int product_mine = 4;

	const int product_steel_factory_cost = 1;
	const int product_factory_steel = 3;

	const int product_cost = 1;// уголь

	const int product_factory_rifle_cost = 1;
	const int product_factory_rifle = 5;

	const int product_factory_dop_cost = 1;
	const int product_factory_dop = 3;

	const int product_factory_car_cost = 3;
	const int product_factory_car = 3;

	const int product_factory_tank_cost = 4;
	const int product_factory_tank = 2;

	const int product_factory_anti_tank_cost = 2;
	const int product_factory_anti_tank = 3;

	const int product_factory_fuel_cost = 2;
	const int product_factory_fuel = 1;

	player_color.set_max_eq(0);
	player_color.set_max_res(0);
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_control[i][j] == player) {
				if (matrix_builds[i][j] == storage) {
					player_color.set_max_res(player_color.get_max_res() + 10);
				}
				else if (matrix_builds[i][j] == millitary_storage) {
					player_color.set_max_eq(player_color.get_max_eq() + 10);
				}
				else if (matrix_builds[i][j] == red_base or matrix_builds[i][j] == blue_base) {
					player_color.set_max_res(player_color.get_max_res() + 20);
					player_color.set_max_eq(player_color.get_max_eq() + 20);
					player_color.set_steel(player_color.get_steel() + 2);
					player_color.set_coal(player_color.get_coal() + 2);
				}
			}
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_build_zone[i][j] != 2000 and matrix_control[i][j] == player) {
				if (matrix_builds[i][j] == mine) {
					if (matrix_resources[i][j] == coal) {

						player_color.set_coal(player_color.get_coal() + product_mine);
					}
					else {
						player_color.set_iron(player_color.get_iron() + product_mine);
					}
				}
				else if (matrix_builds[i][j] == oil_tower) {
					player_color.set_oil(player_color.get_oil() + product_mine);
				}
			}
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_build_zone[i][j] != 2000 and matrix_control[i][j] == player) {
				if (player_color.get_coal() >= product_cost) {
					int builds_ = matrix_builds[i][j];
					if (builds_ == factory_steel) {
						if (player_color.get_iron() >= product_steel_factory_cost) {
							player_color.set_coal(player_color.get_coal() - product_cost);
							player_color.set_iron(player_color.get_iron() - product_steel_factory_cost);
							player_color.set_steel(player_color.get_steel() + product_factory_steel);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_build_zone[i][j] != 2000 and matrix_control[i][j] == player) {
				if (player_color.get_coal() >= product_cost) {
					int builds_ = matrix_builds[i][j];
					if (builds_ == factory_rifle) {
						if (player_color.get_steel() >= product_factory_rifle_cost) {
							player_color.set_coal(player_color.get_coal() - product_cost);
							player_color.set_steel(player_color.get_steel() - product_factory_rifle_cost);
							player_color.set_rifle(player_color.get_rifle() + product_factory_rifle);
						}
					}
					if (builds_ == factory_tank) {
						if (player_color.get_steel() >= product_factory_tank_cost) {
							player_color.set_coal(player_color.get_coal() - product_cost);
							player_color.set_steel(player_color.get_steel() - product_factory_tank_cost);
							player_color.set_tank(player_color.get_tank() + product_factory_tank);
						}
					}
					if (builds_ == factory_dop) {
						if (player_color.get_steel() >= product_factory_dop_cost) {
							player_color.set_coal(player_color.get_coal() - product_cost);
							player_color.set_steel(player_color.get_steel() - product_factory_dop_cost);
							player_color.set_dop(player_color.get_dop() + product_factory_dop);
						}
					}
					if (builds_ == factory_car) {
						if (player_color.get_steel() >= product_factory_car_cost) {
							player_color.set_coal(player_color.get_coal() - product_cost);
							player_color.set_steel(player_color.get_steel() - product_factory_car_cost);
							player_color.set_car(player_color.get_car() + product_factory_car);
						}
					}
				}
			}
		}
	}
}

void paint_supply(int x_camera, int y_camera, int zoom) {
	if (player == red_player) {
		start_check_rail_web(1, 1);
	}
	else {
		start_check_rail_web(size_field_x - 2, size_field_y - 2);
	}
	start_check_supply_zones();
	const int road_1 = 0;
	const int road_2 = 1;
	const int road_3 = 2;
	const int road_4 = 3;
	const int angle = 90;
	const int zero_angle = 0;
	const int left = -1;
	const int right = 1;
	const int up = -1;
	const int down = 1;
	Vector2f scale = zoom_to_scale(zoom);

	Sprite sprite_road_1;
	Sprite sprite_road_2;
	Sprite sprite_road_3;
	Sprite sprite_road_4;
	Sprite sprite_town;
	Sprite sprite_blue_base;
	Sprite sprite_red_base;
	Sprite sprite_supply_center;

	sprite_road_1.setTexture(textures_roads[road_1]);
	sprite_road_1.setScale(scale);

	sprite_road_2.setTexture(textures_roads[road_2]);
	sprite_road_2.setScale(scale);

	sprite_road_3.setTexture(textures_roads[road_3]);
	sprite_road_3.setScale(scale);

	sprite_road_4.setTexture(textures_roads[road_4]);
	sprite_road_4.setScale(scale);

	sprite_town.setTexture(textures_builds[town]);
	sprite_town.setScale(scale);

	sprite_blue_base.setTexture(textures_builds[blue_base]);
	sprite_blue_base.setScale(scale);

	sprite_red_base.setTexture(textures_builds[red_base]);
	sprite_red_base.setScale(scale);

	sprite_supply_center.setTexture(textures_builds[supply_center]);
	sprite_supply_center.setScale(scale);

	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			int rail_object = rail_objectrs(i, j);
			int rail_object_up = rail_objectrs(i, j + up);
			int rail_object_down = rail_objectrs(i, j + down);
			int rail_object_left = rail_objectrs(i + left, j);
			int rail_object_right = rail_objectrs(i + right, j);
			// 1 слой
			if (matrix_roads[i][j] == rail_town) {
				sprite_town.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_town);
			}
			else if (matrix_roads[i][j] == rail_supply_center) {
				sprite_supply_center.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_supply_center);
			}
			else if (matrix_roads[i][j] == rail_base) {
				if (i == 1 and j == 1) {
					sprite_red_base.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_red_base);
				}
				else {
					sprite_blue_base.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_blue_base);
				}

			}
			else {
				if (rail_object == rail_road and rail_object_up == null and rail_object_down == null and
					rail_object_left == null and rail_object_right == null) {
					sprite_road_1.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}

				if (rail_object == rail_road and rail_object_down == rail_road and rail_object_up == rail_road) {
					sprite_road_1.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}
				if (rail_object == rail_road and rail_object_down == rail_road and rail_object_up == null and
					rail_object_right == null and matrix_roads[i + left][j] == null) {
					sprite_road_1.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}
				if (rail_object == rail_road and rail_object_up == rail_road and rail_object_down == null and
					rail_object_left == null and rail_object_right == null) {
					sprite_road_1.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}

				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_left == rail_road) {
					sprite_road_1.setRotation(angle);
					sprite_road_1.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and rail_object_up == null and
					rail_object_right == null and rail_object_down == null) {
					sprite_road_1.setRotation(angle);
					sprite_road_1.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}
				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_up == null and
					rail_object_left == null and rail_object_down == null) {
					sprite_road_1.setRotation(angle);
					sprite_road_1.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_1);
				}

				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_down == rail_road) {
					sprite_road_2.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_2);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and matrix_roads[i][j + down] == rail_road) {
					sprite_road_2.setRotation(angle);
					sprite_road_2.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_2);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and rail_object_up == rail_road) {
					sprite_road_2.setRotation(2 * angle);
					sprite_road_2.setPosition((i + 1) * size_cell * zoom + x_camera, (j + 1) * size_cell * zoom + y_camera);
					window.draw(sprite_road_2);
				}
				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_up == rail_road) {
					sprite_road_2.setRotation(3 * angle);
					sprite_road_2.setPosition((i)*size_cell * zoom + x_camera, (j + 1) * size_cell * zoom + y_camera);
					window.draw(sprite_road_2);
				}

				// 2 слой

				if (rail_object == rail_road and rail_object_down == rail_road and rail_object_up == rail_road) {
					sprite_road_3.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}
				if (rail_object == rail_road and rail_object_down == rail_road and rail_object_up == null and
					rail_object_right == null and rail_object_left == null) {
					sprite_road_3.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}
				if (rail_object == rail_road and rail_object_up == rail_road and rail_object_down == null and
					rail_object_left == null and rail_object_right == null) {
					sprite_road_3.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}

				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_left == rail_road) {
					sprite_road_3.setRotation(angle);
					sprite_road_3.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and rail_object_up == null and
					rail_object_right == null and rail_object_down == null) {
					sprite_road_3.setRotation(angle);
					sprite_road_3.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}
				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_up == null and
					rail_object_left == null and rail_object_down == null) {
					sprite_road_3.setRotation(angle);
					sprite_road_3.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_3);
				}

				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_down == rail_road) {
					sprite_road_4.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_4);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and rail_object_down == rail_road) {
					sprite_road_4.setRotation(angle);
					sprite_road_4.setPosition((i + 1) * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
					window.draw(sprite_road_4);
				}
				if (rail_object == rail_road and rail_object_left == rail_road and rail_object_up == rail_road) {
					sprite_road_4.setRotation(2 * angle);
					sprite_road_4.setPosition((i + 1) * size_cell * zoom + x_camera, (j + 1) * size_cell * zoom + y_camera);
					window.draw(sprite_road_4);
				}
				if (rail_object == rail_road and rail_object_right == rail_road and rail_object_up == rail_road) {
					sprite_road_4.setRotation(3 * angle);
					sprite_road_4.setPosition((i)*size_cell * zoom + x_camera, (j + 1) * size_cell * zoom + y_camera);
					window.draw(sprite_road_4);
				}

				sprite_road_1.setRotation(zero_angle);
				sprite_road_2.setRotation(zero_angle);
				sprite_road_3.setRotation(zero_angle);
				sprite_road_4.setRotation(zero_angle);
			}

		}
	}
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	rectangle.setFillColor(orange_color);
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_supply_zone[i][j] == 1) {
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

void paint_builds(int x_camera, int y_camera, int zoom) {
	Vector2f scale = zoom_to_scale(zoom);
	Sprite sprite_town;
	Sprite sprite_blue_base;
	Sprite sprite_factory_car;
	Sprite sprite_factory_dop;
	Sprite sprite_factory_fuel;
	Sprite sprite_factory_rifle;
	Sprite sprite_factory_steel;
	Sprite sprite_factory_tank;
	Sprite sprite_millitary_storage;
	Sprite sprite_mine;
	Sprite sprite_oil_tower;
	Sprite sprite_red_base;
	Sprite sprite_storage;
	Sprite sprite_supply_center;

	sprite_town.setTexture(textures_builds[town]);
	sprite_town.setScale(scale);
	sprite_blue_base.setTexture(textures_builds[blue_base]);
	sprite_blue_base.setScale(scale);
	sprite_factory_car.setTexture(textures_builds[factory_car]);
	sprite_factory_car.setScale(scale);
	sprite_factory_dop.setTexture(textures_builds[factory_dop]);
	sprite_factory_dop.setScale(scale);
	sprite_factory_fuel.setTexture(textures_builds[factory_fuel]);
	sprite_factory_fuel.setScale(scale);
	sprite_factory_rifle.setTexture(textures_builds[factory_rifle]);
	sprite_factory_rifle.setScale(scale);
	sprite_factory_steel.setTexture(textures_builds[factory_steel]);
	sprite_factory_steel.setScale(scale);
	sprite_factory_tank.setTexture(textures_builds[factory_tank]);
	sprite_factory_tank.setScale(scale);
	sprite_millitary_storage.setTexture(textures_builds[millitary_storage]);
	sprite_millitary_storage.setScale(scale);
	sprite_mine.setTexture(textures_builds[mine]);
	sprite_mine.setScale(scale);
	sprite_oil_tower.setTexture(textures_builds[oil_tower]);
	sprite_oil_tower.setScale(scale);
	sprite_red_base.setTexture(textures_builds[red_base]);
	sprite_red_base.setScale(scale);
	sprite_storage.setTexture(textures_builds[storage]);
	sprite_storage.setScale(scale);
	sprite_supply_center.setTexture(textures_builds[supply_center]);
	sprite_supply_center.setScale(scale);

	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_builds[i][j] == town) {
				sprite_town.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_town);
			}
			if (matrix_builds[i][j] == blue_base) {
				sprite_blue_base.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_blue_base);
			}
			if (matrix_builds[i][j] == factory_car) {
				sprite_factory_car.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_car);
			}
			if (matrix_builds[i][j] == factory_dop) {
				sprite_factory_dop.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_dop);
			}
			if (matrix_builds[i][j] == factory_fuel) {
				sprite_factory_fuel.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_fuel);
			}
			if (matrix_builds[i][j] == factory_rifle) {
				sprite_factory_rifle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_rifle);

			}
			if (matrix_builds[i][j] == factory_steel) {
				sprite_factory_steel.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_steel);
			}
			if (matrix_builds[i][j] == factory_tank) {
				sprite_factory_tank.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_factory_tank);
			}
			if (matrix_builds[i][j] == millitary_storage) {
				sprite_millitary_storage.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_millitary_storage);
			}
			if (matrix_builds[i][j] == mine) {
				sprite_mine.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_mine);
			}
			if (matrix_builds[i][j] == oil_tower) {
				sprite_oil_tower.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_oil_tower);
			}
			if (matrix_builds[i][j] == red_base) {
				sprite_red_base.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_red_base);
			}
			if (matrix_builds[i][j] == storage) {
				sprite_storage.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_storage);
			}
			if (matrix_builds[i][j] == supply_center) {
				sprite_supply_center.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(sprite_supply_center);
			}
		}
	}
}

void paint_units(int x_camera, int y_camera, int zoom) {//Допилить под новые реалии, но потом
	int type_units;
	Vector2f scale = zoom_to_scale(zoom);
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	Sprite unit_sprite;
	unit_sprite.setScale(scale);
	unit_sprite.setPosition(0, 0);

	RectangleShape rectangle_1(Vector2f(size_cell * zoom, size_cell * zoom));
	rectangle_1.setFillColor(orange_color);
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (matrix_unit_mobility[i][j] > null) {
				rectangle_1.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				window.draw(rectangle_1);
			}

		}
	}

	
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			type_units = matrix_units_id[i][j];
			if (type_units != 0) {
				unit_sprite.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
				switch (type_units) {
				case ID_construction:
					;
					break;
				case ID_tank:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_tank]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_tank]);
					}
					break;
				case ID_anti_tank:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_PTO]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_PTO]);
					}
					break;
				case ID_infantry:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_infantry]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_infantry]);
					}
					
					break;
				case ID_motorised_infantry:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_moto]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_moto]);
					}
					break;
				case ID_supply_car:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_sup]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_sup]);
					}
					break;
				case ID_mount_infantry:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_mount_infantry]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_mount_infantry]);
					}
					break;
				case ID_forest_infantry:
					if (matrix_control[i][j] == red_player) {
						unit_sprite.setTexture(textures_units[red_jaeger]);
					}
					else {
						unit_sprite.setTexture(textures_units[blue_jaeger]);
					}
					break;
				default:
					break;
				}
				window.draw(unit_sprite);
			}
		}

	}
}

void paint_map_mode() {
	const int size_rectangle_mode_on = 200;

	Sprite sprite_mode;

	RectangleShape rectangle(Vector2f(size_window_x, player_bar_size_y));
	rectangle.setFillColor({ 100, 100 ,100 });
	rectangle.setPosition(0, size_window_y - player_bar_size_y);
	window.draw(rectangle);

	RectangleShape rectangle_mode_on(Vector2f(size_rectangle_mode_on, size_rectangle_mode_on));
	rectangle_mode_on.setFillColor(green_color);

	for (int i = 0; i < count_mode; i++) {
		if (matrix_mode[i]) {
			rectangle_mode_on.setPosition((size_step_mode)*i, size_window_y - player_bar_size_y);
			window.draw(rectangle_mode_on);
		}
		sprite_mode.setTexture(textures_modes[i]);
		sprite_mode.setPosition(11 + (size_step_mode)*i, size_window_y - player_bar_size_y + 11);
		window.draw(sprite_mode);

	}


}

void paint_main_menu() {
	Sprite sprite_mode;
	for (int i = 0; i < count_player_bar; i++) {
		sprite_mode.setTexture(textures_player_bar[i]);
		sprite_mode.setScale({ 0.8, 0.8 });
		sprite_mode.setPosition(size_window_x - player_bar_size_x + 38, 250 * i + 15);
		window.draw(sprite_mode);

	}
}

void paint_res_menu(Player_res player_color) {
	Font font;
	font.loadFromFile("ofont.ru_Arial.ttf");
	Text text("", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setColor(Color::Black);
	int get_res;
	Sprite sprite_res;
	sprite_res.scale(3, 3);
	for (int i = 0; i < 5; i++) {
		if (i == sup_steel) {
			get_res = player_color.get_steel();
			
		}
		else if (i == sup_iron) {
			get_res = player_color.get_iron();
		}
		else if (i == sup_coal) {
			get_res = player_color.get_coal();
		}
		else if (i == sup_oil) {
			get_res = player_color.get_oil();
		}
		else {
			get_res = player_color.get_fuel();
		}
		sprite_res.setTexture(textures_sup_res[i]);
		ostringstream buffer;
		buffer << get_res;
		buffer << "/";
		buffer << player_color.get_max_res();
		text.setString(buffer.str());
		text.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3, size_window_y / 5 * i + 50);
		sprite_res.setPosition(size_window_x - player_bar_size_x, size_window_y / 5 * i + 35);

		window.draw(text);
		window.draw(sprite_res);
	}


}
void paint_unit_stat() {
	Font font;
	font.loadFromFile("ofont.ru_Arial.ttf");
	Text text("", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setColor(Color::Black);
	Sprite sprite_res;
	sprite_res.scale(3, 3);
	for (int i = 0; i <= stat_hard; i++) {
		ostringstream buffer_text;
		if (i == stat_hp) {
			sprite_res.setTexture(textures_stats[stat_hp]);
			buffer_text << matrix_units_points[unit_x][unit_y]->get_health(matrix_units_id[unit_x][unit_y]);
			buffer_text << "/";
			buffer_text << max_health(unit_x, unit_y);
		}
		if (i == stat_eq) {
			sprite_res.setTexture(textures_stats[stat_eq]);
			buffer_text << matrix_units_points[unit_x][unit_y]->get_supply(matrix_units_id[unit_x][unit_y]);
			buffer_text << "/";
			buffer_text << max_supply(unit_x, unit_y);
		}
		if (i == stat_mobility) {
			sprite_res.setTexture(textures_stats[stat_mobility]);
			buffer_text << matrix_units_points[unit_x][unit_y]->get_mobility(matrix_units_id[unit_x][unit_y]);
			buffer_text << "/";
			buffer_text << max_mobility(unit_x, unit_y);
		}
		if (i == stat_soft) {
			sprite_res.setTexture(textures_stats[stat_soft]);
			buffer_text << matrix_units_points[unit_x][unit_y]->get_damage_to_living_force(matrix_units_id[unit_x][unit_y]);
		}
		if (i == stat_hard) {
			sprite_res.setTexture(textures_stats[stat_hard]);
			buffer_text << matrix_units_points[unit_x][unit_y]->get_damage_to_war_machine(matrix_units_id[unit_x][unit_y]);
		}
		text.setString(buffer_text.str());
		text.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3, size_window_y / 5 * i + 50);
		sprite_res.setPosition(size_window_x - player_bar_size_x, size_window_y / 5 * i + 35);

		window.draw(text);
		window.draw(sprite_res);

	}
}
void paint_mil_res_menu(Player_res player_color) {
	const int sup_rifle = 0;
	const int sup_dop = 1;
	const int sup_car = 2;
	const int sup_tank = 3;
	Font font;
	font.loadFromFile("ofont.ru_Arial.ttf");
	Text text("", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setColor(Color::Black);
	int get_res;
	Sprite sprite_res;
	sprite_res.scale(3, 3);
	for (int i = 0; i < 4; i++) {
		if (i == sup_rifle) {
			get_res = player_color.get_rifle();
		}
		else if (i == sup_dop) {
			get_res = player_color.get_dop();
		}
		else if (i == sup_car) {
			get_res = player_color.get_car();
		}
		else if (i == sup_tank) {
			get_res = player_color.get_tank();
		}
		sprite_res.setTexture(textures_sup_mil[i]);
		ostringstream buffer;
		buffer << get_res;
		buffer << "/";
		buffer << player_color.get_max_eq();
		text.setString(buffer.str());
		text.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3, size_window_y / 5 * i + 50);
		sprite_res.setPosition(size_window_x - player_bar_size_x, size_window_y / 5 * i + 35);

		window.draw(text);
		window.draw(sprite_res);
	}

}
void paint_build_menu(Player_res player_color) {
	Sprite sprite_builds;
	sprite_builds.setScale(2, 2);
	char binds[cost_rail_road + 2] = "QWERTYUIOPAS";
	RectangleShape rectangle_cost(Vector2f(70, 70));
	RectangleShape rectangle_blank_line(Vector2f(60, 60));
	rectangle_blank_line.setFillColor(mount_color);
	Font font;
	font.loadFromFile("ofont.ru_Arial.ttf");
	Text text("", font, 40);
	Text text_2("", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setColor(Color::Black);
	text_2.setStyle(sf::Text::Bold);
	text_2.setColor(Color::Black);
	for (int i = 0; i <= cost_rail_road; i++) {
		if (i == cost_factory_car) {
			sprite_builds.setTexture(textures_builds[factory_car]);
		}
		if (i == cost_factory_dop) {
			sprite_builds.setTexture(textures_builds[factory_dop]);
		}
		if (i == cost_factory_fuel) {
			sprite_builds.setTexture(textures_builds[factory_fuel]);
		}
		if (i == cost_factory_rifle) {
			sprite_builds.setTexture(textures_builds[factory_rifle]);
		}
		if (i == cost_factory_steel) {
			sprite_builds.setTexture(textures_builds[factory_steel]);
		}
		if (i == cost_factory_tank) {
			sprite_builds.setTexture(textures_builds[factory_tank]);
		}
		if (i == cost_millitary_storage) {
			sprite_builds.setTexture(textures_builds[millitary_storage]);
		}
		if (i == cost_mine) {
			sprite_builds.setTexture(textures_builds[mine]);
		}
		if (i == cost_oil_tower) {
			sprite_builds.setTexture(textures_builds[oil_tower]);
		}
		if (i == cost_rail_road) {
			sprite_builds.setTexture(textures_roads[0]);
		}
		if (i == cost_storage) {
			sprite_builds.setTexture(textures_builds[storage]);
		}
		if (i == cost_supply_center) {
			sprite_builds.setTexture(textures_builds[supply_center]);
		}

		text_2.setString(binds[i]);
		ostringstream buffer;
		buffer << player_color.get_steel();
		buffer << "/";
		buffer << cost_buildings[i];
		text.setString(buffer.str());
		text.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3, 75 * i + 70);
		text_2.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 + 150, 75 * i + 70);
		sprite_builds.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80 + 5, 75 * i + 60 + 5);
		rectangle_blank_line.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80 + 5, 75 * i + 60 + 5);
		if (player_color.get_steel() >= cost_buildings[i]) {
			rectangle_cost.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80, 75 * i + 60);
			rectangle_cost.setFillColor(green_color);
			window.draw(rectangle_cost);
		}
		window.draw(rectangle_blank_line);
		window.draw(text_2);
		window.draw(text);
		window.draw(sprite_builds);


	}
}

void paint_unit_build_menu(Player_res player_color) {
	Sprite sprite_units;
	sprite_units.setScale(2, 2);
	char binds[cost_rail_road + 2] = "QWERTYU";
	RectangleShape rectangle_cost(Vector2f(70, 70));
	RectangleShape rectangle_blank_line(Vector2f(60, 60));
	rectangle_blank_line.setFillColor(mount_color);
	Font font;
	font.loadFromFile("ofont.ru_Arial.ttf");
	Text text("", font, 40);
	Text text_2("", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setColor(Color::Black);
	text_2.setStyle(sf::Text::Bold);
	text_2.setColor(Color::Black);

	for (int i = 0; i < 7; i++) {
		int res;
		if (i == infantry_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_infantry]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_infantry]);
			}
			res = player_color.get_rifle();
			
		}
		else if (i == jager_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_jaeger]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_jaeger]);
			}
			res = player_color.get_rifle();
		}
		else if (i == mount_infantry_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_mount_infantry]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_mount_infantry]);
			}
			res = player_color.get_dop();
		}
		else if (i == PTO_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_PTO]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_PTO]);
			}
			res = player_color.get_dop();
		}
		else if (i == moto_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_moto]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_moto]);
			}
			res = player_color.get_car();
		}
		else if (i == tank_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_tank]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_tank]);
			}
			res = player_color.get_tank();
		}
		else if (i == sup_) {
			if (player == red_player) {
				sprite_units.setTexture(textures_units[red_sup]);
			}
			else {
				sprite_units.setTexture(textures_units[blue_sup]);
			}
			res = player_color.get_car();
		}

		text_2.setString(binds[i]);
		ostringstream buffer;
		buffer << res;
		buffer << "/";
		buffer << cost_units[i];
		text.setString(buffer.str());
		text.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3, 75 * i + 70);
		text_2.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 + 150, 75 * i + 70);
		sprite_units.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80 + 5, 75 * i + 60 + 5);
		rectangle_blank_line.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80 + 5, 75 * i + 60 + 5);
		if (res >= cost_units[i]) {
			rectangle_cost.setPosition(size_window_x - player_bar_size_x + player_bar_size_x / 3 - 80, 75 * i + 60);
			rectangle_cost.setFillColor(green_color);
			window.draw(rectangle_cost);
		}
		window.draw(rectangle_blank_line);
		window.draw(text_2);
		window.draw(text);
		window.draw(sprite_units);


	}
}

void check_zone(int matrix[size_field_x][size_field_y]) {
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix[i][j] = 10000;
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_x; j++) {
			if (matrix_builds[i][j] == red_base or matrix_builds[i][j] == blue_base or matrix_builds[i][j] == town) {
				if (matrix_builds[i - 1][j] == null and matrix_control[i - 1][j] == player) {
					matrix[i - 1][j] = 1;
				}
				if (matrix_builds[i - 1][j - 1] == null and matrix_control[i - 1][j - 1] == player) {
					matrix[i - 1][j - 1] = 1;
				}
				if (matrix_builds[i][j - 1] == null and matrix_control[i][j - 1] == player) {
					matrix[i][j - 1] = 1;
				}
				if (matrix_builds[i + 1][j - 1] == null and matrix_control[i + 1][j - 1] == player) {
					matrix[i + 1][j - 1] = 1;
				}
				if (matrix_builds[i + 1][j] == null and matrix_control[i + 1][j] == player) {
					matrix[i + 1][j] = 1;
				}
				if (matrix_builds[i + 1][j + 1] == null and matrix_control[i + 1][j + 1] == player) {
					matrix[i + 1][j + 1] = 1;
				}
				if (matrix_builds[i][j + 1] == null and matrix_control[i][j + 1] == player) {
					matrix[i][j + 1] = 1;
				}
				if (matrix_builds[i - 1][j + 1] == null and matrix_control[i - 1][j + 1] == player) {
					matrix[i - 1][j + 1] = 1;
				}
			}
			if (matrix_builds[i][j] == supply_center) {
				if (matrix_builds[i - 1][j] == null and matrix_control[i - 1][j] == player) {
					matrix[i - 1][j] = 1;
				}
				if (matrix_builds[i][j - 1] == null and matrix_control[i][j - 1] == player) {
					matrix[i][j - 1] = 1;
				}
				if (matrix_builds[i + 1][j] == null and matrix_control[i + 1][j] == player) {
					matrix[i + 1][j] = 1;
				}
				if (matrix_builds[i][j + 1] == null and matrix_control[i][j + 1] == player) {
					matrix[i][j + 1] = 1;
				}
			}
		}
	}
}

int cost_to_build_convert(int constuction) {
	if (constuction == cost_factory_car) {
		return factory_car;
	}
	if (constuction == cost_factory_dop) {
		return factory_dop;
	}
	if (constuction == cost_factory_fuel) {
		return factory_fuel;
	}
	if (constuction == cost_factory_rifle) {
		return factory_rifle;
	}
	if (constuction == cost_factory_steel) {
		return factory_steel;
	}
	if (constuction == cost_factory_tank) {
		return factory_tank;
	}
	if (constuction == cost_millitary_storage) {
		return millitary_storage;
	}
	if (constuction == cost_mine) {
		return mine;
	}
	if (constuction == cost_oil_tower) {
		return oil_tower;
	}
	if (constuction == cost_storage) {
		return storage;
	}
	if (constuction == cost_supply_center) {
		return supply_center;
	}
}

void build(Player_res player_color, int constuction, int zoom, int x_camera, int y_camera) {
	int steel = player_color.get_steel();
	int cost_object = cost_buildings[constuction];
	float coefficient_field = 1;
	float coefficient_forest = 1.5;
	float coefficient_mount = 2;
	RectangleShape rectangle(Vector2f(size_cell * zoom, size_cell * zoom));
	rectangle.setFillColor(choose_color);

	start_check_build_zones();
	//print(matrix_build_zone);
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (constuction == cost_mine) {
				if (matrix_resources[i][j] == coal or matrix_resources[i][j] == iron) {
					if (steel >= cost_object * coefficient_field * matrix_build_zone[i][j]) {
						rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
						window.draw(rectangle);
					}
				}
			}
		}
	}
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			if (constuction == cost_mine) {
				if (matrix_resources[i][j] == coal or matrix_resources[i][j] == iron) {
					if (matrix_relief[i][j] == field) {
						if (steel >= cost_object * coefficient_field * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == forest) {
						if (steel >= cost_object * coefficient_forest * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == mount) {
						if (steel >= cost_object * coefficient_mount * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
				}

			}
			else if (constuction == cost_oil_tower) {
				if (matrix_resources[i][j] == oil) {
					if (matrix_relief[i][j] == field) {
						if (steel >= cost_object * coefficient_field * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == forest) {
						if (steel >= cost_object * coefficient_forest * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == mount) {
						if (steel >= cost_object * coefficient_mount * matrix_build_zone[i][j]) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
				}
			}
			else if (constuction != cost_rail_road and constuction != cost_supply_center) {
				if (matrix_relief[i][j] == field) {
					if (steel >= cost_object * coefficient_field * matrix_build_zone[i][j]) {
						rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
						window.draw(rectangle);
					}
				}
				else if (matrix_relief[i][j] == forest) {
					if (steel >= cost_object * coefficient_forest * matrix_build_zone[i][j]) {
						rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
						window.draw(rectangle);
					}
				}
				else if (matrix_relief[i][j] == mount) {
					if (steel >= cost_object * coefficient_mount * matrix_build_zone[i][j]) {
						rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
						window.draw(rectangle);
					}
				}
			}
			/*else{
				if (matrix_control[i][j] == player) {
					if (matrix_relief[i][j] == field) {
						if (steel >= cost_object * coefficient_field and matrix_builds[i][j] == null) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == forest) {
						if (steel >= cost_object * coefficient_forest and matrix_builds[i][j] == null) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
					else if (matrix_relief[i][j] == mount) {
						if (steel >= cost_object * coefficient_mount and matrix_builds[i][j] == null) {
							rectangle.setPosition(i * size_cell * zoom + x_camera, j * size_cell * zoom + y_camera);
							window.draw(rectangle);
						}
					}
				}
			}*/
		}
	}
}

void check_build(Player_res& player_color, int constuction, int x, int y) {
	int steel = player_color.get_steel();
	int cost_object = cost_buildings[constuction];
	float coefficient_field = 1;
	float coefficient_forest = 1.5;
	float coefficient_mount = 2;
	int balance;

	start_check_build_zones();
	if (constuction == cost_mine) {
		if (matrix_resources[x][y] == coal or matrix_resources[x][y] == iron) {
			if (matrix_relief[x][y] == field) {
				if (steel >= cost_object * coefficient_field * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_field * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == forest) {
				if (steel >= cost_object * coefficient_forest * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_forest * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == mount) {
				if (steel >= cost_object * coefficient_mount * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_mount * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
		}

	}
	else if (constuction == cost_oil_tower) {
		if (matrix_resources[x][y] == oil) {
			if (matrix_relief[x][y] == field) {
				if (steel >= cost_object * coefficient_field * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_field * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == forest) {
				if (steel >= cost_object * coefficient_forest * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_forest * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == mount) {
				if (steel >= cost_object * coefficient_mount * matrix_build_zone[x][y]) {
					matrix_builds[x][y] = cost_to_build_convert(constuction);
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_mount * matrix_build_zone[x][y];
					player_color.set_steel(balance);
				}
			}
		}
	}
	else if (constuction != cost_rail_road and constuction != cost_supply_center) {
		if (matrix_relief[x][y] == field) {
			if (steel >= cost_object * coefficient_field * matrix_build_zone[x][y]) {

				matrix_builds[x][y] = cost_to_build_convert(constuction);
				balance = player_color.get_steel();
				balance -= cost_object * coefficient_field * matrix_build_zone[x][y];
				player_color.set_steel(balance);
			}
		}
		else if (matrix_relief[x][y] == forest) {
			if (steel >= cost_object * coefficient_forest * matrix_build_zone[x][y]) {
				matrix_builds[x][y] = cost_to_build_convert(constuction);
				balance = player_color.get_steel();
				balance -= cost_object * coefficient_forest * matrix_build_zone[x][y];
				player_color.set_steel(balance);
			}
		}
		else if (matrix_relief[x][y] == mount) {
			if (steel >= cost_object * coefficient_mount * matrix_build_zone[x][y]) {
				matrix_builds[x][y] = cost_to_build_convert(constuction);
				balance = player_color.get_steel();
				balance -= cost_object * coefficient_mount * matrix_build_zone[x][y];
				player_color.set_steel(balance);
			}
		}
	}
	else {
		if (matrix_control[x][y] == player) {
			if (matrix_relief[x][y] == field) {
				if (steel >= cost_object * coefficient_field and matrix_builds[x][y] == null and matrix_roads[x][y] == null) {
					if (constuction == cost_rail_road) {
						matrix_roads[x][y] = rail_road;
					}
					else {
						matrix_builds[x][y] = cost_to_build_convert(constuction);
						matrix_roads[x][y] = rail_supply_center;
					}
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_field;
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == forest) {
				if (steel >= cost_object * coefficient_forest and matrix_builds[x][y] == null and matrix_roads[x][y] == null) {
					if (constuction == cost_rail_road) {
						matrix_roads[x][y] = rail_road;
					}
					else {
						matrix_builds[x][y] = cost_to_build_convert(constuction);
						matrix_roads[x][y] = rail_supply_center;
					}
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_field;
					player_color.set_steel(balance);
				}
			}
			else if (matrix_relief[x][y] == mount) {
				if (steel >= cost_object * coefficient_mount and matrix_builds[x][y] == null and matrix_roads[x][y] == null) {
					if (constuction == cost_rail_road) {
						matrix_roads[x][y] = rail_road;
					}
					else {
						matrix_builds[x][y] = cost_to_build_convert(constuction);
						matrix_roads[x][y] = rail_supply_center;
					}
					balance = player_color.get_steel();
					balance -= cost_object * coefficient_field;
					player_color.set_steel(balance);
				}
			}
		}
	}

}

void build_unit(Player_res& player_color, int create_unit, int x, int y) {
	start_check_supply_zones();
	if (create_unit == infantry_ and player_color.get_rifle() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_rifle(player_color.get_rifle() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_infantry;
		matrix_units_points[x][y] = new buffer(ID_infantry, player);
	}
	if (create_unit == jager_ and player_color.get_rifle() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_rifle(player_color.get_rifle() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_forest_infantry;
		matrix_units_points[x][y] = new buffer(ID_forest_infantry, player);
	}
	if (create_unit == mount_infantry_ and player_color.get_dop() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_dop(player_color.get_dop() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_mount_infantry;
		matrix_units_points[x][y] = new buffer(ID_mount_infantry, player);
	}
	if (create_unit == PTO_ and player_color.get_dop() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_dop(player_color.get_dop() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_anti_tank;
		matrix_units_points[x][y] = new buffer(ID_anti_tank, player);
	}
	if (create_unit == moto_ and player_color.get_car() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_car(player_color.get_car() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_motorised_infantry;
		matrix_units_points[x][y] = new buffer(ID_motorised_infantry, player);
	}
	if (create_unit == sup_ and player_color.get_car() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_car(player_color.get_car() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_supply_car;
		matrix_units_points[x][y] = new buffer(ID_supply_car, player);
	}
	if (create_unit == tank_ and player_color.get_tank() >= cost_units[create_unit] and matrix_supply_zone[x][y] == 1) {
		player_color.set_tank(player_color.get_tank() - cost_units[create_unit]);
		matrix_units_id[x][y] = ID_tank;
		matrix_units_points[x][y] = new buffer(ID_tank, player);
	}
}

void change_menu(Player_res& player_color, int constuction, int zoom, int x_camera, int y_camera, bool unit_choose) {
	if (matrix_player_bar[res_menu]) {
		paint_res_menu(player_color);
	}
	else if (matrix_player_bar[build_menu]) {
		paint_build_menu(player_color);
	}
	else if (matrix_player_bar[weap_menu]) {
		paint_mil_res_menu(player_color);
	}
	else if (matrix_player_bar[unit_build_menu]) {
		paint_unit_build_menu(player_color);
	}
	else if (unit_choose and matrix_units_id[unit_x][unit_y] != ID_black_hole) {
		paint_unit_stat();
	}
	else {
		paint_main_menu();
	}
}

void paint_player_bar(Player_res& player_color, int constuction, int zoom, int x_camera, int y_camera, bool unit_choose) {
	RectangleShape rectangle2(Vector2f(player_bar_size_x, size_window_y));
	rectangle2.setFillColor({ 100, 100 ,100 });
	rectangle2.setPosition(size_window_x - player_bar_size_x, 0);
	window.draw(rectangle2);

	if (player == red_player) {
		RectangleShape rectangle1(Vector2f(player_bar_size_x, size_window_y));
		rectangle1.setFillColor(red_color);
		rectangle1.setPosition(size_window_x - player_bar_size_x, 0);
		window.draw(rectangle1);
	}
	else {
		RectangleShape rectangle1(Vector2f(player_bar_size_x, size_window_y));
		rectangle1.setFillColor(blue_color);
		rectangle1.setPosition(size_window_x - player_bar_size_x, 0);
		window.draw(rectangle1);

	}
	change_menu(player_color, constuction, zoom, x_camera, y_camera, unit_choose);


}

void paint_game(int x_camera, int y_camera, int zoom, Player_res player_color, int constuction, bool unit_choose) {
	paint_relief(x_camera, y_camera, zoom);
	if (choose_build) {
		build(player_color, constuction, zoom, x_camera, y_camera);
	}
	if (matrix_mode[control_mode]) {
		paint_control(x_camera, y_camera, zoom);
	}
	if (matrix_mode[supply_mode]) {
		paint_supply(x_camera, y_camera, zoom);
	}
	if (matrix_mode[grid_mode]) {
		paint_grid(x_camera, y_camera, zoom);
	}
	if (matrix_mode[resources_mode]) {
		paint_resource(x_camera, y_camera, zoom);
	}
	if (matrix_mode[builds_mode]) {
		paint_builds(x_camera, y_camera, zoom);
	}
	if (matrix_mode[unit_mode]) {
		paint_units(x_camera, y_camera, zoom);
	}
	paint_map_mode();
	paint_player_bar(player_color, constuction, zoom, x_camera, y_camera, unit_choose);

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

vector<int> select_element(Event event, int& zoom, int& x_camera, int& y_camera, float window_zoom_x, float window_zoom_y) {
	vector<int> coord;
	Vector2i mousePos;
	mousePos = Mouse::getPosition(window);
	coord.push_back(((mousePos.x - x_camera * window_zoom_x) / (size_cell * zoom * window_zoom_x)));
	coord.push_back(((mousePos.y - y_camera * window_zoom_x) / (size_cell * zoom * window_zoom_y)));
	return coord;
}

void check_unit_road_machine(int x, int y, int new_mobility, int mobility, int& unit_id, Player_res& player_resources) {
	if (matrix_unit_mobility[x][y] == null and matrix_units_id[x][y] == ID_black_hole and new_mobility <= mobility and player_resources.get_fuel() >= new_mobility) {
		matrix_unit_mobility[x][y] = new_mobility;
	}
	else if (matrix_unit_mobility[x][y] != null and matrix_units_id[x][y] == ID_black_hole and new_mobility <= mobility and player_resources.get_fuel() >= new_mobility) {
		if (new_mobility < matrix_unit_mobility[x][y]) {
			matrix_unit_mobility[x][y] = new_mobility;
		}
	}
	if (new_mobility <= mobility and x >= 0 and y >= 0) {
		if (matrix_control[x][y] != player) {
			if (matrix_relief[x][y] == mount and unit_id == ID_tank) {
				matrix_unit_mobility[x][y] = null;
			}
			else {
				matrix_unit_mobility[x][y] = mobility / 2;
			}
		}
		else if (matrix_relief[x][y] == mount and unit_id == ID_tank) {
			matrix_unit_mobility[x][y] = null;
		}
		else if (matrix_relief[x][y] == field) {
			check_unit_road_machine(x + 1, y, new_mobility + 1, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y + 1, new_mobility + 1, mobility, unit_id, player_resources);
			check_unit_road_machine(x - 1, y, new_mobility + 1, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y - 1, new_mobility + 1, mobility, unit_id, player_resources);
		}
		else if (matrix_relief[x][y] == forest) {
			check_unit_road_machine(x + 1, y, new_mobility + 2, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y + 1, new_mobility + 2, mobility, unit_id, player_resources);
			check_unit_road_machine(x - 1, y, new_mobility + 2, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y - 1, new_mobility + 2, mobility, unit_id, player_resources);
		}
		else if (matrix_relief[x][y] == mount and unit_id != ID_tank) {
			check_unit_road_machine(x + 1, y, new_mobility + 3, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y + 1, new_mobility + 3, mobility, unit_id, player_resources);
			check_unit_road_machine(x - 1, y, new_mobility + 3, mobility, unit_id, player_resources);
			check_unit_road_machine(x, y - 1, new_mobility + 3, mobility, unit_id, player_resources);
		}
	}
}

void check_unit_road(int x, int y, int new_mobility, int mobility, int& unit_id) {
	/*if (matrix_control[x][y] != player) {
		new_mobility = mobility;
	}*/
	if (matrix_unit_mobility[x][y] == null and matrix_units_id[x][y] == ID_black_hole and new_mobility <= mobility) {
		matrix_unit_mobility[x][y] = new_mobility;
	}
	else if (matrix_unit_mobility[x][y] != null and matrix_units_id[x][y] == ID_black_hole and new_mobility <= mobility) {
		if (new_mobility < matrix_unit_mobility[x][y]) {
			matrix_unit_mobility[x][y] = new_mobility;
		}
	}
	if (new_mobility <= mobility and x >= 0 and y >= 0) {
		if (matrix_control[x][y] != player) {
			matrix_unit_mobility[x][y] = mobility / 2;
		}
		else if (matrix_relief[x][y] == field) {
			check_unit_road(x + 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y + 1, new_mobility + 1, mobility, unit_id);
			check_unit_road(x - 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y - 1, new_mobility + 1, mobility, unit_id);
		}
		else if (matrix_relief[x][y] == forest and unit_id == ID_forest_infantry) {
			check_unit_road(x + 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y + 1, new_mobility + 1, mobility, unit_id);
			check_unit_road(x - 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y - 1, new_mobility + 1, mobility, unit_id);
		}
		else if (matrix_relief[x][y] == mount and unit_id == ID_mount_infantry) {
			check_unit_road(x + 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y + 1, new_mobility + 1, mobility, unit_id);
			check_unit_road(x - 1, y, new_mobility + 1, mobility, unit_id);
			check_unit_road(x, y - 1, new_mobility + 1, mobility, unit_id);
		}
		else if (matrix_relief[x][y] == forest) {
			check_unit_road(x + 1, y, new_mobility + 2, mobility, unit_id);
			check_unit_road(x, y + 1, new_mobility + 2, mobility, unit_id);
			check_unit_road(x - 1, y, new_mobility + 2, mobility, unit_id);
			check_unit_road(x, y - 1, new_mobility + 2, mobility, unit_id);
		}
		else if (matrix_relief[x][y] == mount) {
			check_unit_road(x + 1, y, new_mobility + 3, mobility, unit_id);
			check_unit_road(x, y + 1, new_mobility + 3, mobility, unit_id);
			check_unit_road(x - 1, y, new_mobility + 3, mobility, unit_id);
			check_unit_road(x, y - 1, new_mobility + 3, mobility, unit_id);
		}
	}
}

void start_check_unit_road(int x, int y, int mobility, int unit_id, Player_res& player_resources) {
	int new_mobility = 0;
	
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_unit_mobility[i][j] = null;
		}
	}
	if (unit_id == ID_tank or unit_id == ID_motorised_infantry or unit_id == ID_supply_car) {
		check_unit_road_machine(x, y, new_mobility, mobility, unit_id, player_resources);
	}
	else {
		check_unit_road(x, y, new_mobility, mobility, unit_id);
	}
}

int supply_removed(vector <int>& coord, vector <int>& coord_saved_unit) {
	if ((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_tank or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_supply_car or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_motorised_infantry) and matrix_relief[coord[0]][coord[1]] == mount) {
		return(supply_for_techicals_to_attack_on_mount);
	}
	else if (matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_mount_infantry and matrix_relief[coord[0]][coord[1]] == mount) {
		return(supply_for_mount_infantry_to_attack_on_mount);
	}
	else if (matrix_relief[coord[0]][coord[1]] == mount){
		return(supply_for_other_to_attack_on_mount);
	}

	else if ((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_tank or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_supply_car or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_motorised_infantry) and matrix_relief[coord[0]][coord[1]] == forest) {
		return(supply_for_techicals_to_attack_in_forest);
	}
	else if (matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_forest_infantry and matrix_relief[coord[0]][coord[1]] == forest) {
		return(supply_for_forest_infantry_to_attack_in_forest);
	}
	else if (matrix_relief[coord[0]][coord[1]] == forest) {
		return(supply_for_other_to_attack_in_forest);
	}

	else if ((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_tank or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_supply_car or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_motorised_infantry) and matrix_relief[coord[0]][coord[1]] == field) {
		return(supply_for_techicals_to_attack_on_field);
	}
	else if (matrix_relief[coord[0]][coord[1]] == field) {
		return(supply_for_other_to_attack_on_field);
	}
}

void atack(vector <int>& coord, vector <int>& coord_saved_unit, Player_res& player_resources) {
	int supply_for_atack = supply_removed(coord, coord_saved_unit);
	int supply_for_defense = supply_for_atack / 2;
	bool cheking = false;
	if (matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_supply(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= supply_for_atack and ((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] != ID_tank and matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] != ID_motorised_infantry) or player_resources.get_fuel() >= supply_for_atack)) {

		if (matrix_relief[coord[0]][coord[1]] == mount and matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 4 and matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 4) {
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 3);
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 3);
			cheking = true;
		}

		else if (matrix_relief[coord[0]][coord[1]] == forest and matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 3 and matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 3) {
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 2);
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 2);
			cheking = true;
		}

		else if (matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 2 and matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= 2){
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 1);
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_health(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - 1);
			cheking = true;
		}

		if ((matrix_units_id[coord[0]][coord[1]] == ID_tank or matrix_units_id[coord[0]][coord[1]] == ID_construction) and cheking) {
			if (matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_damage_to_war_machine(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= matrix_units_points[coord[0]][coord[1]]->get_health(matrix_units_id[coord[0]][coord[1]]) or (matrix_units_points[coord[0]][coord[1]]->get_supply(matrix_units_id[coord[0]][coord[1]]) < supply_for_defense)) {
				matrix_units_points[coord[0]][coord[1]] = nullptr;
				matrix_units_id[coord[0]][coord[1]] = ID_black_hole;
				start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]), matrix_units_id[coord[0]][coord[1]], player_resources);
			}
			else{
				matrix_units_points[coord[0]][coord[1]]->set_health(matrix_units_id[coord[0]][coord[1]], matrix_units_points[coord[0]][coord[1]]->get_health(matrix_units_id[coord[0]][coord[1]]) - matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_damage_to_war_machine((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]])));
				matrix_units_points[coord[0]][coord[1]]->set_supply(matrix_units_id[coord[0]][coord[1]], matrix_units_points[coord[0]][coord[1]]->get_supply(matrix_units_id[coord[0]][coord[1]]) - supply_for_defense);
				start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]), matrix_units_id[coord[0]][coord[1]], player_resources);
			}
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_supply(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_supply(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - supply_for_atack);
			if (matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_tank or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_motorised_infantry) {
				player_resources.set_fuel(player_resources.get_fuel() - supply_for_atack);
			}
		}
		else if (cheking) {
			if (matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_damage_to_living_force(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) >= matrix_units_points[coord[0]][coord[1]]->get_health(matrix_units_id[coord[0]][coord[1]]) or (matrix_units_points[coord[0]][coord[1]]->get_supply(matrix_units_id[coord[0]][coord[1]]) < supply_for_defense)) {
				matrix_units_points[coord[0]][coord[1]] = nullptr;
				matrix_units_id[coord[0]][coord[1]] = ID_black_hole;
				start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]), matrix_units_id[coord[0]][coord[1]], player_resources);
			}
			else {
				matrix_units_points[coord[0]][coord[1]]->set_health(matrix_units_id[coord[0]][coord[1]], matrix_units_points[coord[0]][coord[1]]->get_health(matrix_units_id[coord[0]][coord[1]]) - matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_damage_to_living_force((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]])));
				matrix_units_points[coord[0]][coord[1]]->set_supply(matrix_units_id[coord[0]][coord[1]], matrix_units_points[coord[0]][coord[1]]->get_supply(matrix_units_id[coord[0]][coord[1]]) - supply_for_defense);
				start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]), matrix_units_id[coord[0]][coord[1]], player_resources);
			}
			matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->set_supply(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_supply(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]) - supply_for_atack);
			if (matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_tank or matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] == ID_motorised_infantry) {
				player_resources.set_fuel(player_resources.get_fuel() - supply_for_atack);
			}
		}
	}
}

void select_unit(vector <int>& coord, vector <int>& coord_saved_unit, Player_res& player_resources) {
	int stri = 0;
	
	if (coord_saved_unit[0] != ID_no_select and coord_saved_unit[1] != ID_no_select and matrix_unit_mobility[coord[0]][coord[1]] != null and ((matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] != ID_tank and matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] != ID_motorised_infantry) or player_resources.get_fuel() >= matrix_unit_mobility[coord[0]][coord[1]]) and matrix_units_id[coord[0]][coord[1]] == ID_black_hole) {
		matrix_units_id[coord[0]][coord[1]] = matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]];
		matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]] = ID_black_hole;
		matrix_units_points[coord[0]][coord[1]] = matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]];
		matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]] = nullptr;
		matrix_units_points[coord[0]][coord[1]]->set_mobility(matrix_units_id[coord[0]][coord[1]], matrix_units_points[coord[0]][coord[1]]->get_mobility(matrix_units_id[coord[0]][coord[1]]) - matrix_unit_mobility[coord[0]][coord[1]]);
		if (matrix_units_id[coord[0]][coord[1]] == ID_tank or matrix_units_id[coord[0]][coord[1]] == ID_motorised_infantry) {
			player_resources.set_fuel(player_resources.get_fuel() - matrix_unit_mobility[coord[0]][coord[1]]);
		}
		matrix_control[coord[0]][coord[1]] = player;
		coord_saved_unit[0] = coord[0];
		coord_saved_unit[1] = coord[1];
		start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], matrix_units_points[coord_saved_unit[0]][coord_saved_unit[1]]->get_mobility(matrix_units_id[coord_saved_unit[0]][coord_saved_unit[1]]), matrix_units_id[coord[0]][coord[1]], player_resources);
	}
	else if (coord_saved_unit[0] != ID_no_select and coord_saved_unit[1] != ID_no_select and matrix_units_id[coord[0]][coord[1]] != ID_black_hole and matrix_units_points[coord[0]][coord[1]]->get_player(matrix_units_id[coord[0]][coord[1]]) != player and (abs(coord[0] - coord_saved_unit[0]) <= 1) and (abs(coord[1] - coord_saved_unit[1]) <= 1)) {
		
		atack(coord, coord_saved_unit, player_resources);
	}
	else {
		
		if (matrix_units_id[coord[0]][coord[1]] != ID_black_hole and matrix_units_points[coord[0]][coord[1]]->get_player(matrix_units_id[coord[0]][coord[1]]) == player) {
			coord_saved_unit[0] = coord[0];
			coord_saved_unit[1] = coord[1];
			int id = matrix_units_points[coord[0]][coord[1]]->get_mobility(matrix_units_id[coord[0]][coord[1]]);
			
			start_check_unit_road(coord_saved_unit[0], coord_saved_unit[1], id, matrix_units_id[coord[0]][coord[1]], player_resources);
			
		}
	}
}
// обновление юнитов
void survivors_remember_the_fallen(Player_res& player_resources) {
	start_check_supply_zones();
	for (int i = 0; i < size_field_x; i++) {
		for (int j = 0; j < size_field_y; j++) {
			matrix_units_points[i][j]->set_mobility(matrix_units_id[i][j], max_mobility(i, j));
			if (matrix_units_id[i][j] != ID_black_hole and matrix_units_id[i][j] != ID_construction) {
				if (matrix_supply_zone[i][j] == 1) {
					if (matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]) + supply_step <= max_supply(i, j)) {
						int delta_supply = max_supply(i, j) - matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]);
						if (delta_supply > supply_step) {
							delta_supply = supply_step;
						}
						int id_unit = matrix_units_id[i][j];
						if (id_unit == ID_anti_tank) {
							if (delta_supply > player_resources.get_dop()) {
								delta_supply = player_resources.get_dop();
								player_resources.set_dop(player_resources.get_dop() - delta_supply);
							}
						}
						if (id_unit == ID_mount_infantry) {
							if (delta_supply > player_resources.get_dop()) {
								delta_supply = player_resources.get_dop();
								player_resources.set_dop(player_resources.get_dop() - delta_supply);
							}
						}
						if (id_unit == ID_infantry) {
							if (delta_supply > player_resources.get_rifle()) {
								delta_supply = player_resources.get_rifle();
								player_resources.set_rifle(player_resources.get_rifle() - delta_supply);
							}
						}
						if (id_unit == ID_forest_infantry) {
							if (delta_supply > player_resources.get_rifle()) {
								delta_supply = player_resources.get_rifle();
								player_resources.set_rifle(player_resources.get_rifle() - delta_supply);
							}
						}
						if (id_unit == ID_motorised_infantry) {
							if (delta_supply > player_resources.get_car()) {
								delta_supply = player_resources.get_car();
								player_resources.set_car(player_resources.get_car() - delta_supply);
							}
						}
						if (id_unit == ID_tank) {
							if (delta_supply > player_resources.get_tank()) {
								delta_supply = player_resources.get_tank();
								player_resources.set_tank(player_resources.get_tank() - delta_supply);
							}
						}
						matrix_units_points[i][j]->set_supply(matrix_units_id[i][j], matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]) + delta_supply);
					}
					else {
						matrix_units_points[i][j]->set_supply(matrix_units_id[i][j], max_supply(i, j));
					}
					if (matrix_units_points[i][j]->get_health(matrix_units_id[i][j]) + health_step <= max_health(i, j)) {
						matrix_units_points[i][j]->set_health(matrix_units_id[i][j], matrix_units_points[i][j]->get_health(matrix_units_id[i][j]) + health_step);
					}
					else {
						matrix_units_points[i][j]->set_health(matrix_units_id[i][j], max_health(i, j));
					}
				}
				
				
			}
			else if (matrix_units_id[i][j] != ID_black_hole and matrix_units_id[i][j] != ID_construction) {
				bool supply_car_mode = false;
				int coord_car_x = 0;
				int coord_car_y = 0;
				if (matrix_units_id[i - 1][j] == ID_supply_car and matrix_units_points[i-1][j]->get_supply(matrix_units_id[i - 1][j]) > 0) {
					supply_car_mode = true;
					coord_car_x = i - 1;
					coord_car_y = j;
				}
				else if (matrix_units_id[i][j - 1] == ID_supply_car and matrix_units_points[i][j - 1]->get_supply(matrix_units_id[i][j - 1]) > 0) {
					supply_car_mode = true;
					coord_car_x = i ;
					coord_car_y = j - 1;
				}
				else if (matrix_units_id[i + 1][j] == ID_supply_car and matrix_units_points[i+1][j]->get_supply(matrix_units_id[i+1][j]) > 0) {
					supply_car_mode = true;
					coord_car_x = i+1;
					coord_car_y = j;
				}
				else if (matrix_units_id[i][j + 1] == ID_supply_car and matrix_units_points[i][j + 1]->get_supply(matrix_units_id[i][j] + 1) > 0) {
					supply_car_mode = true;
					coord_car_x = i;
					coord_car_y = j + 1;
				}
				if (supply_car_mode) {
					if (matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]) + supply_step <= max_supply(i, j)) {
						int delta_supply = max_supply(i, j) - matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]);
						if (delta_supply > supply_step) {
							delta_supply = supply_step;
						}
						int id_unit = matrix_units_id[i][j];
						if (id_unit == ID_anti_tank) {
							if (delta_supply > player_resources.get_dop()) {
								delta_supply = player_resources.get_dop();
								player_resources.set_dop(player_resources.get_dop() - delta_supply);
							}
						}
						if (id_unit == ID_mount_infantry) {
							if (delta_supply > player_resources.get_dop()) {
								delta_supply = player_resources.get_dop();
								player_resources.set_dop(player_resources.get_dop() - delta_supply);
							}
						}
						if (id_unit == ID_infantry) {
							if (delta_supply > player_resources.get_rifle()) {
								delta_supply = player_resources.get_rifle();
								player_resources.set_rifle(player_resources.get_rifle() - delta_supply);
							}
						}
						if (id_unit == ID_forest_infantry) {
							if (delta_supply > player_resources.get_rifle()) {
								delta_supply = player_resources.get_rifle();
								player_resources.set_rifle(player_resources.get_rifle() - delta_supply);
							}
						}
						if (id_unit == ID_motorised_infantry) {
							if (delta_supply > player_resources.get_car()) {
								delta_supply = player_resources.get_car();
								player_resources.set_car(player_resources.get_car() - delta_supply);
							}
						}
						if (id_unit == ID_tank) {
							if (delta_supply > player_resources.get_tank()) {
								delta_supply = player_resources.get_tank();
								player_resources.set_tank(player_resources.get_tank() - delta_supply);
							}
						}
						matrix_units_points[i][j]->set_supply(matrix_units_id[i][j], matrix_units_points[i][j]->get_supply(matrix_units_id[i][j]) + delta_supply);
						matrix_units_points[i+ coord_car_x][j+ coord_car_y]->set_supply(matrix_units_id[i + coord_car_x][j + coord_car_y], matrix_units_points[i + coord_car_x][j + coord_car_y]->get_supply(matrix_units_id[i + coord_car_x][j + coord_car_y]) + delta_supply);
					}
				}
			}
		}
	}
}

void game() {
	Player_res Blue_player;
	Player_res Red_player;
	create_cost_buildings();
	vector <int> coord_units{ID_no_select, ID_no_select};

	genetate_resource();
	create_matrix_control();
	create_matrix_mode();
	matrix_unit_to_zero();
	load_texture();

	//generate_relief();
	read_relief();

	generate_towns();
	create_matrix_roads();
	check_zone(zone_building_red);
	check_zone(zone_building_blue);
	int x_camera = 0;
	int y_camera = 0;
	int zoom = 4;
	Vector2i old_mousePos;
	Vector2i step;
	Event event;
	window.setKeyRepeatEnabled(false);
	int constuction = -1;
	int create_unit = -1;
	bool unit_choose = false;
	while (window.isOpen())
	{
		window.clear();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				float new_window_zoom_x = event.size.width;
				float new_window_zoom_y = event.size.height;
				new_window_zoom_x = new_window_zoom_x / size_window_x;
				new_window_zoom_y = new_window_zoom_y / size_window_y;
				window_zoom_x = new_window_zoom_x;
				window_zoom_y = new_window_zoom_y;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					start_check_build_zones();
					if (player == red_player) {
						update_product(Red_player);
						player = blue_player;
					}
					else {
						update_product(Blue_player);
						player = red_player;
					}
					survivors_remember_the_fallen(Red_player);
					survivors_remember_the_fallen(Blue_player);
					
				}

				if (event.key.code == sf::Keyboard::Num1)
				{
					matrix_mode[control_mode] = not matrix_mode[control_mode];
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					matrix_mode[supply_mode] = not matrix_mode[supply_mode];
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					matrix_mode[grid_mode] = not matrix_mode[grid_mode];
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					matrix_mode[resources_mode] = not matrix_mode[resources_mode];
				}
				if (event.key.code == sf::Keyboard::Num5)
				{
					matrix_mode[builds_mode] = not matrix_mode[builds_mode];
				}
				if (event.key.code == sf::Keyboard::Num6)
				{
					matrix_mode[unit_mode] = not matrix_mode[unit_mode];
				}

				if (matrix_player_bar[build_menu] == false and matrix_player_bar[res_menu] == false and matrix_player_bar[weap_menu] == false and matrix_player_bar[unit_build_menu] == false) {
					if (event.key.code == sf::Keyboard::Q)
					{
						matrix_player_bar[build_menu] = true;
					}
					if (event.key.code == sf::Keyboard::W)
					{
						matrix_player_bar[res_menu] = true;
					}
					if (event.key.code == sf::Keyboard::E)
					{
						matrix_player_bar[weap_menu] = true;
					}
					if (event.key.code == sf::Keyboard::R)
					{
						matrix_player_bar[unit_build_menu] = true;
					}
				}

				else if (matrix_player_bar[build_menu] == true) {
					if (event.key.code == sf::Keyboard::Q)
					{
						constuction = cost_factory_car;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::W)
					{
						constuction = cost_factory_dop;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::E)
					{
						constuction = cost_factory_fuel;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::R)
					{
						constuction = cost_factory_rifle;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::T)
					{
						constuction = cost_factory_tank;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::Y)
					{
						constuction = cost_millitary_storage;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::U)
					{
						constuction = cost_factory_steel;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::I)
					{
						constuction = cost_mine;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::O)
					{
						constuction = cost_oil_tower;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::P)
					{
						constuction = cost_storage;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						constuction = cost_supply_center;
						choose_build = true;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						constuction = cost_rail_road;
						choose_build = true;
					}
				}

				else if (matrix_player_bar[unit_build_menu] == true) {
					if (event.key.code == sf::Keyboard::Q)
					{
						create_unit = infantry_;
					}
					if (event.key.code == sf::Keyboard::W)
					{
						create_unit = jager_;
					}
					if (event.key.code == sf::Keyboard::E)
					{
						create_unit = mount_infantry_;
					}
					if (event.key.code == sf::Keyboard::R)
					{
						create_unit = moto_;
					}
					if (event.key.code == sf::Keyboard::T)
					{
						create_unit = PTO_;
					}
					if (event.key.code == sf::Keyboard::Y)
					{
						create_unit = sup_;
					}
					if (event.key.code == sf::Keyboard::U)
					{
						create_unit = tank_;
					}
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					matrix_player_bar[build_menu] = false;
					matrix_player_bar[res_menu] = false;
					matrix_player_bar[weap_menu] = false;
					matrix_player_bar[unit_build_menu] = false;
					choose_build = false;
					unit_choose = false;
					constuction = -1;
					coord_units[0] = ID_no_select;
					coord_units[1] = ID_no_select;
					create_unit = -1;
					matrix_road_to_zero();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i mousePos = Mouse::getPosition(window);
					if (mousePos.y < (size_window_y - player_bar_size_y) * window_zoom_y and mousePos.x < (size_window_x - player_bar_size_x) * window_zoom_x and matrix_mode[unit_mode] == true and create_unit == -1) {
						vector<int> coord;
						coord = select_element(event, zoom, x_camera, y_camera, window_zoom_x, window_zoom_y);

						if (player == red) {
							select_unit(coord, coord_units, Red_player);
						}
						else {
							select_unit(coord, coord_units, Blue_player);
						}
						unit_choose = true;
						unit_x = coord[0];
						unit_y = coord[1];

					}
					else if (mousePos.y < (size_window_y - player_bar_size_y) * window_zoom_y and mousePos.x < (size_window_x - player_bar_size_x) * window_zoom_x and constuction != -1) {
						vector<int> coord;
						coord = select_element(event, zoom, x_camera, y_camera, window_zoom_x, window_zoom_y);

						if (player == red_player) {
							check_build(Red_player, constuction, coord[0], coord[1]);
						}
						else {
							check_build(Blue_player, constuction, coord[0], coord[1]);
						}
					}
					else if (mousePos.y < (size_window_y - player_bar_size_y) * window_zoom_y and mousePos.x < (size_window_x - player_bar_size_x) * window_zoom_x and create_unit != -1) {
						vector<int> coord;
						coord = select_element(event, zoom, x_camera, y_camera, window_zoom_x, window_zoom_y);

						if (player == red_player) {
							build_unit(Red_player, create_unit, coord[0], coord[1]);
						}
						else {
							build_unit(Blue_player, create_unit, coord[0], coord[1]);
						}
					}
					else if (mousePos.y < (size_window_y - player_bar_size_y) * window_zoom_y and mousePos.x < (size_window_x - player_bar_size_x) * window_zoom_x) {
						select_element(event, zoom, x_camera, y_camera, window_zoom_x, window_zoom_y);

					}
					else if (mousePos.x > (size_window_x - player_bar_size_x) * window_zoom_x) {
						int coords = (mousePos.y / (250 * window_zoom_y));
						matrix_player_bar[coords] = true;
					}
					else {
						int coords = ((mousePos.x - 11 * window_zoom_x) / (size_step_mode * window_zoom_x));
						matrix_mode[coords] = not matrix_mode[coords];
					}
				}
			}
			if (Mouse::isButtonPressed(Mouse::Middle)) {

				change_camera(event, old_mousePos, step, x_camera, y_camera, zoom);
			}
			if (sf::Event::MouseWheelScrolled) {

				change_zoom(event, zoom, x_camera, y_camera);
			}
			if (event.type == Event::Closed)
				window.close();
			old_mousePos = Mouse::getPosition(window);
			check_zone(zone_building_red);
			check_zone(zone_building_blue);
		}
		if (player == red_player) {
			paint_game(x_camera, y_camera, zoom, Red_player, constuction, unit_choose);
		}
		else {
			paint_game(x_camera, y_camera, zoom, Blue_player, constuction, unit_choose);
		}
		window.display();
	}
}

int main()
{
	game();
	return 0;
}