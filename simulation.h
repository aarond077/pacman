//
// Created by Aaron Diether on 09.07.2021.
//

#ifndef PACMAN_SIMULATION_H
#define PACMAN_SIMULATION_H
#include "ConsoleWindow.h"
#include "enemy.h"
#include "pacman.h"
#include "console_timer.h"


class simulation : public ConsoleWindow {
    std::vector<enemy*> enemies;
    std::vector<ghost_lvl2*> enemies2;
    std::vector<position> obstacles;
    std::vector<moveable> moveable_tiles;
    std::vector<position> power_up;
    pacman player;
    std::vector<position> collected_coins;
    std::vector<std::vector<char>> map;
    unsigned ticker;
    console_timer pac_time;
    bool stop = false;
    bool running = false;
    bool menu = true;
    bool menu2 = false;
    bool start_game = false;
    bool win;
    bool finished = false;
public:
    simulation();
    std::vector<enemy> get_enemies() const{}
    std::vector<tile> get_coins() const {}
    pacman get_player() const{}

    void onRefresh() override;
    void onKeyPress() override;

    void draw_line(const int &a); //converts line of .txt file into game map,
                                  // also fills the vectors enemies, obstacles, moveable_tiles with using ASCII to code the different objects
    bool valid_pos(const position &p); //returns true if new position is valid
    void clear_last(); //puffer for movement animation,
    void player_clear_last();  //also checks if coin is collected using check_tile() and replaces tiles char with either ' ' or '.'
    void move_enemies_lvl1(); //moves the ghosts lvl1
    bool check_tile(position &p); //checks if coin is collected at certain tile
    void collect_coin(const position &p); //sets bool coin on true for certain tile if pacman was at the tile
    bool check_hitbox(); //checks if pacman collided with an enemy
    void update_hitbox();
    bool set_enemy_speed(const unsigned n);
    void draw_timer() const;
    void move_lvl2();
    void update_timer();
    unsigned calc_score();
    void draw_menu(const unsigned &a);
    void draw_after_finished();
    void reset();
    bool check_power_up(const position &p);

};


#endif //PACMAN_SIMULATION_H
