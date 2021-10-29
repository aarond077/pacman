//
// Created by Aaron Diether on 09.07.2021.
//

#include "pacman.h"
pacman::pacman(position p) {
   pos = p;
   last = {};
   this->set_health(3);
}

pacman::pacman() {
    pos = position(0, 0);
    last = {};
    this->set_health(3);
}

position pacman::get_pos() {
    return this->pos;
}

void pacman::set_pos(const position &other) {
    pos = other;
}

std::vector<position> pacman::get_last() const {return this->last;}

int pacman::get_health() const {return this->health;}

void pacman::set_health(const int &other) {this->health = other;}

void pacman::got_hit() {
    (this->health) += -(1);
}

void pacman::clear_vec() {this->last.clear();}

void pacman::move(const position &p) {
    position temp;
    temp.set_x(this->pos.get_x());
    temp.set_y(this->pos.get_y());
    last.push_back(temp);
    this->set_pos(p);
}

bool pacman::get_power_up() const {
    return power_up;
}

void pacman::set_power_up(const bool &set) {
    power_up = set;
}