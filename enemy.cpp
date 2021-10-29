//
// Created by Aaron Diether on 09.07.2021.
//

#include "enemy.h"
#include "simulation.h"


ghost_lvl1::ghost_lvl1(position &p) {
    this->set_pos(p);
    lvl = 1;
    last = {};
}
ghost_lvl2::ghost_lvl2(position &p) {
    this->set_pos(p);
    lvl = 2;
    last = {};
}
void enemy::set_pos(const position &p) {
    this->pos = p;
}

position enemy::get_pos() const {return pos;}

std::vector<position> enemy::get_last() const {return last;}

int enemy::get_lvl() const {
    return lvl;
}


void enemy::move_enemy(const position &p) {
    position temp(this->get_pos());
    this->last.push_back(temp);
    this->pos = p;
}


void ghost_lvl2::chase(const position &p) {
    int res = 0;
    position temp = this->pos.calc_vec(p);
    res = temp.length();
}

void enemy::clear_vec() {
    this->last.clear();
}