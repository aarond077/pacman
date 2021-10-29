//
// Created by Aaron Diether on 09.07.2021.
//

#ifndef PACMAN_ENEMY_H
#define PACMAN_ENEMY_H
#include "position.h"
#include <vector>

class enemy {
protected:
    int lvl;
    position pos;
    bool afraid;
    std::vector<position> last;
    std::vector<position> possible;
    int vec_2_pac; //vector to calculate the distance between pacman and the enemy
public:
    enemy() = default;
    virtual ~enemy(){};

    virtual position get_pos() const;
    virtual void set_pos(const position &p);
    virtual void set_afraid(){};
    std::vector<position> get_last() const;
    int get_lvl() const;

    virtual void move_enemy(const position &p);
    virtual void run_away(){};
    virtual void clear_vec();

};

class ghost_lvl1 : public enemy {
public:
    ghost_lvl1(position &p);
};

class ghost_lvl2 : public enemy {
public:

    ghost_lvl2(position &p);
    virtual void chase(const position &p); //gets pacmans pos and creates vector
};



#endif //PACMAN_ENEMY_H
