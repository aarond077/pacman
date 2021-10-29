//
// Created by Aaron Diether on 09.07.2021.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "position.h"
#include <vector>
#include "tile.h"

class pacman {
    int health;
    position pos;
    std::vector<position> last;
    bool power_up = false;
public:
    pacman();
    pacman(position p);

    position get_pos();
    std::vector<position> get_last() const ;
    int get_health() const;
    void set_pos(const position &other);
    void set_health(const int &other);
    bool get_power_up() const ;
    void set_power_up(const bool &set);

    void got_hit();

    void clear_vec();
    void move(const position &p);


};


#endif //PACMAN_PACMAN_H
