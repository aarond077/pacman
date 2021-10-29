//
// Created by Aaron Diether on 09.07.2021.
//

#include "tile.h"



void tile::set_sym(const char &other) {sym = other;}

void tile::set_pos(const position &other) {pos = other;}

position tile::get_pos() const {return pos;}

char tile::get_sym() const {return sym;}

moveable::moveable(position &p) {this->set_pos(p);}

bool moveable::is_collected() const {
    if(coin){return false;}
    else return true;
}


void moveable::collect() {this->coin = false;}

void moveable::set_sym(const char &other) {
    if(!coin){
        this->sym = ' ';
    }
}