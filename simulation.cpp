//
// Created by Aaron Diether on 09.07.2021.
//

#include "simulation.h"
#include "fstream"
#include "iostream"
#include <random>

int mind_index(std::vector<int> v) {
    int res = 0;
    int compare = v[0];

    for (int i = 1; i < v.size(); ++i) {
        if (compare >= v[i]) {
            compare = v[i];
            res = i;
        }
    }
    return res;
}

int find_if(std::vector<int> &v, std::function<bool(int)> f) {
    for (int i = 0; i < v.size(); ++i) {
        if (f(v[i])) return v[i];
    }
}

std::vector<std::vector<char>> readfile(const std::string &filename) {
    std::vector<std::vector<char>> streetmap;

    std::ifstream file(filename);
    if (!file.is_open())
        std::cout << "FILE OPENING ERROR!!" << std::endl;
    else {

        std::ifstream myfile(filename);
        if (myfile.is_open()) {
            std::string s;
            std::getline(myfile, s);
            do {
                std::vector<char> line(s.begin(), s.end());
                streetmap.push_back(line);

            } while ((std::getline(myfile, s)));
        }
        file.close();
    }
    return streetmap;
}

simulation::simulation() {
    power_up = {};
    stop = false;
    map = readfile("C:\\Users\\Aaron Diether\\Documents\\pacman_menu.txt");
    for (int j = 0; j < map.size(); ++j) {
        draw_menu(j);
    }
    map.clear();


}


void simulation::draw_line(const int &a) { //a is set x variable, while i changes the index of the ath array
    for (int i = 0; i < map[a].size(); ++i) {
        position temp(i, a);
        setCharacter(i, a, map[a][i]);
        if ((map[a][i] == '|') || (map[a][i] == '-') || (map[a][i] == '+')) { //obstacle object (cannot reach)
            obstacles.push_back(temp);
        } else if (map[a][i] == 'g') {
            enemies.push_back(new ghost_lvl1(temp));
            moveable xtile = moveable(temp);
            xtile.collect();
            moveable_tiles.push_back(xtile);


        } else if (map[a][i] == 'o') {
            power_up.push_back(temp);
            moveable xtile = moveable(temp);
            xtile.collect();
            moveable_tiles.push_back(xtile);

        } else if (map[a][i] == 'G') { //ghost level 2
            enemies2.push_back(new ghost_lvl2(temp));
            moveable xtile = moveable(temp);
            xtile.collect();
            moveable_tiles.push_back(xtile);
        } else if (map[a][i] == '.') { //coin object
            moveable_tiles.push_back(moveable(temp));
        } else if (map[a][i] == '*') {
            player.set_pos(temp);
            moveable xtile = moveable(temp); //moveable tile which isnt a coin
            xtile.collect();
            moveable_tiles.push_back(xtile);
        } //pacman
    }
}

bool simulation::valid_pos(const position &p) {
    for (int i = 0; i < moveable_tiles.size(); ++i) {
        if (moveable_tiles[i].get_pos() == p) { return true; }

    }
    for (int j = 0; j < obstacles.size(); ++j) {
        if (obstacles[j] == p) { return false; }
    }
    return false;
}

bool simulation::check_hitbox() {
    if (enemies.size() != 0) {
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i]->get_pos() == player.get_pos()) {
                return true;
            }
        }
    }
    if (enemies2.size() != 0) {
        for (int i = 0; i < enemies2.size(); ++i) {
            if (enemies2[i]->get_pos() == player.get_pos()) {
                return true;
            }
        }
    }
    return false;
}

void simulation::update_hitbox() {
    if (check_hitbox()) { player.got_hit(); }
}

bool simulation::check_tile(position &p) { //bool func gives true if pacman was already at tile with position p
    for (int i = 0; i < moveable_tiles.size(); ++i) {
        if (moveable_tiles[i].get_pos() == p) {
            if (moveable_tiles[i].is_collected()) { return true; } //pacman was already there -> char = ' '
        }
    }
    return false; //pacman wasnt there yet -> char = '.'

}

void simulation::collect_coin(const position &p) {
    for (int i = 0; i < moveable_tiles.size(); ++i) {
        if (moveable_tiles[i].get_pos() == p) {
            if (!moveable_tiles[i].is_collected()) {
                moveable_tiles[i].collect();
                collected_coins.push_back(p);
            }
        }
    }
}

bool simulation::set_enemy_speed(const unsigned int n) {
    if (n % 3 == 0) { return true; }
    else { return false; }

}

void simulation::update_timer() {

    if (pac_time.second_right == 0) {
        if (pac_time.second_left != 0) {
            pac_time.second_right = 9;
            pac_time.second_left -= 1;
        } else {
            if (pac_time.minute != 0) {
                pac_time.second_left = 5;
                pac_time.second_right = 9;
                pac_time.minute -= 1;
            } else { std::cout << "GAME ENDS"; }
        }
    }

}

unsigned simulation::calc_score() {
    unsigned score = 0;
    if (pac_time.minute == 2) {
        if (pac_time.second_left == 5) { score = 100; }
        else if (pac_time.second_left == 4) { score = 100; }
        else if (pac_time.second_left == 3) { score = 100; }
        else if (pac_time.second_left == 2) { score = 95; }
        else if (pac_time.second_left == 1) { score = 90; }
        else if (pac_time.second_left == 0) { score = 85; }

    } else if (pac_time.minute == 1) {
        if (pac_time.second_left == 5) { score = 80; }
        else if (pac_time.second_left == 4) { score = 75; }
        else if (pac_time.second_left == 3) { score = 70; }
        else if (pac_time.second_left == 2) { score = 65; }
        else if (pac_time.second_left == 1) { score = 60; }
        else if (pac_time.second_left == 0) { score = 55; }


    } else if (pac_time.minute == 0) {
        if (pac_time.second_left == 5) { score = 50; }
        else if (pac_time.second_left == 4) { score = 45; }
        else if (pac_time.second_left == 3) { score = 40; }
        else if (pac_time.second_left == 2) { score = 30; }
        else if (pac_time.second_left == 1) { score = 20; }
        else if (pac_time.second_left == 0) { score = 10; }

    }
    return score;
}

void simulation::draw_menu(const unsigned &a) {
    for (int i = 0; i < map[a].size(); ++i) {
        setCharacter(i, a, map[a][i]);
    }
}

void simulation::draw_after_finished() {
    if (win) {
        map.clear();
        map = readfile("C:\\Users\\Aaron Diether\\Documents\\pacman_win.txt");
        for (int i = 0; i < map.size(); ++i) {
            draw_menu(i);
        }

    } else {
        map.clear();
        map = readfile("C:\\Users\\Aaron Diether\\Documents\\pacman_defeat.txt");
        for (int i = 0; i < map.size(); ++i) {
            draw_menu(i);
        }
    }
}

void simulation::reset() {
    enemies.clear();
    enemies2.clear();
    obstacles.clear();
    moveable_tiles.clear();
    power_up.clear();
    collected_coins.clear();
    ticker = 0;
    player.set_health(3);
}

bool simulation::check_power_up(const position &p) {
    for (int i = 0; i < power_up.size(); ++i) {
        if (power_up[i] == p) { return 1; }
    }
    return 0;
}


void simulation::onRefresh() {
    if (finished) {
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                setCharacter(j, i, ' ');
            }
        }
        menu = true;
        menu2 = true;
        finished = false;

        draw_after_finished();
        if(win){writeString(0, 16, "YOUR SCORE: " + std::to_string(calc_score()));}

    }
    if (start_game) {
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                setCharacter(j, i, ' ');
            }
        }
        reset();
        console_timer ctimer();


        for (int j = 0; j < map.size(); ++j) {
            draw_line(j);
        }
        for (unsigned s = 0; s < map[0].size(); ++s) {
            setCharacter(s, 0, ' ');
        }
        start_game = !start_game;
        stop = false;
    }
    if (!menu) {
        if (getPressedKey() == 'p') { stop = !stop; }
        if (stop) { return; }
        ++ticker;
        writeString(0, 0, "Timer:");
        writeString(6, 0, std::to_string(pac_time.minute) + ":" + std::to_string(pac_time.second_left) +
                          std::to_string(pac_time.second_right));
        writeString(12, 0, "Health: " + std::to_string(player.get_health()));
        if (set_enemy_speed(ticker)) {
            move_lvl2();
        }
        move_enemies_lvl1();

        clear_last();
        update_hitbox();
        if (player.get_health() != 0) {

            if (collected_coins.size() == (moveable_tiles.size() - enemies.size() - enemies2.size()) - 1) {
                running = false;
                win = true;
                finished = true;
                return;
            }
            if (ticker >= 10) {
                if (pac_time.second_right == 0 || pac_time.second_left == 0) { update_timer(); }
                else { pac_time.second_right -= 1; }


                ticker = 0;
            }
        } else {
            stop = true;
            running = false;
            win = false;
            finished = true;
            menu = false;
        }

    } else { return; }
}

void simulation::onKeyPress() {
    if (menu2) {
        if (getPressedKey() == 'j' || getPressedKey() == 'y') {
            clear();
            map = readfile("C:\\Users\\Aaron Diether\\Documents\\pacman_menu.txt");
            for (int j = 0; j < map.size(); ++j) {
                draw_menu(j);
            }
            map.clear();
            running = false;
            menu = true;
            finished = false;
            start_game = true;
        } else if (getPressedKey() == 'q') { clear(); }
    }
    if (!running && menu && !finished) {
        if (getPressedKey() == '1') {
            map.clear();
            map = readfile("C:\\Users\\Aaron Diether\\Documents\\level1.txt");
        } else if (getPressedKey() == '2') {
            map.clear();
            map = readfile("C:\\Users\\Aaron Diether\\Documents\\level2.txt");
        } else if (getPressedKey() == '3') {
            map.clear();
            map = readfile("C:\\Users\\Aaron Diether\\Documents\\level3.txt");
        } else if (getPressedKey() == 's') {
            if (map.size() == 0) { map = readfile("C:\\Users\\Aaron Diether\\Documents\\level1.txt"); }

            menu = false;
            running = true;
            start_game = true;
            onRefresh();
        }

    }
    if (!stop && running) { //cant move while game is paused
        position temp(0, 0);
        if (player.get_power_up()) {
            if (getPressedKey() == 3) {
                temp.set_x(player.get_pos().get_x());
                temp.set_y(player.get_pos().get_y() - 2);
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
                else if (valid_pos(position(temp.get_x(), temp.get_y() + 1))) {
                    temp.set_y(temp.get_y() + 1);
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
            } else if (getPressedKey() == 1) {
                temp.set_x(player.get_pos().get_x() - 2);
                temp.set_y(player.get_pos().get_y());
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
                else if (valid_pos(position(temp.get_x() + 1, temp.get_y()))) {
                    temp.set_x(temp.get_x() + 1);
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
            } else if (getPressedKey() == 4) {
                temp.set_x(player.get_pos().get_x());
                temp.set_y(player.get_pos().get_y() + 2);
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
                else if (valid_pos(position(temp.get_x(), temp.get_y() - 1))) {
                    temp.set_y(temp.get_y() - 1);
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
            } else if (getPressedKey() == 2) {
                temp.set_x(player.get_pos().get_x() + 2);
                temp.set_y(player.get_pos().get_y());
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                } else if (valid_pos(position(temp.get_x() - 1, temp.get_y()))) {
                    temp.set_x(temp.get_x() - 1);
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                }
            }
        } else { //case no power up
            if (getPressedKey() == 3) {
                temp.set_x(player.get_pos().get_x());
                temp.set_y(player.get_pos().get_y() - 1);
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                    if (check_power_up(temp)) {
                        player.set_power_up(1);
                    }
                }
            } else if (getPressedKey() == 1) {
                temp.set_x(player.get_pos().get_x() - 1);
                temp.set_y(player.get_pos().get_y());
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                    if (check_power_up(temp)) {
                        player.set_power_up(1);
                    }
                }
            } else if (getPressedKey() == 4) {
                temp.set_x(player.get_pos().get_x());
                temp.set_y(player.get_pos().get_y() + 1);
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                    if (check_power_up(temp)) {
                        player.set_power_up(1);
                    }
                }
            } else if (getPressedKey() == 2) {
                temp.set_x(player.get_pos().get_x() + 1);
                temp.set_y(player.get_pos().get_y());
                if (valid_pos(temp)) {
                    player.move(temp);
                    collect_coin(temp);
                    setCharacter(temp.get_x(), temp.get_y(), '*');
                    player_clear_last();
                    if (check_power_up(temp)) {
                        player.set_power_up(1);
                    }
                }
            }
        }
    }
}

void simulation::player_clear_last() {
    if (player.get_last().size() != 0) {  //clear player
        position player_last = player.get_last()[0];

        setCharacter(player_last.get_x(), player_last.get_y(), ' ');
        player.clear_vec();
    }
}

void simulation::clear_last() {

    for (int i = 0; i < enemies.size(); ++i) { //clear enemies
        if ((enemies[i]->get_last().size()) == 1) {
            position enemy_last = enemies[i]->get_last()[0];

            if (check_tile(enemy_last)) {
                setCharacter(enemy_last.get_x(), enemy_last.get_y(), ' ');
                enemies[i]->clear_vec();
            } else {
                setCharacter(enemy_last.get_x(), enemy_last.get_y(), '.');
                enemies[i]->clear_vec();
            }
        }
    }
    for (int i = 0; i < enemies2.size(); ++i) { //clear enemies 2
        if ((enemies2[i]->get_last().size()) == 1) {
            position enemy_last = enemies2[i]->get_last()[0];

            if (check_tile(enemy_last)) {
                setCharacter(enemy_last.get_x(), enemy_last.get_y(), ' ');
                enemies2[i]->clear_vec();
            } else {
                setCharacter(enemy_last.get_x(), enemy_last.get_y(), '.');
                enemies2[i]->clear_vec();
            }
        }
    }
}

void simulation::move_enemies_lvl1() {
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->get_lvl() == 1) {
            position temp(enemies[i]->get_pos().get_x(), enemies[i]->get_pos().get_y());


            srand((unsigned) time(0));
            int j = 1 + (rand() % 4);

            switch (j) {
                case 1: {
                    if (valid_pos(position(temp.get_x(), temp.get_y() - 1))) {
                        enemies[i]->move_enemy(position(temp.get_x(), temp.get_y() - 1));
                        setCharacter(temp.get_x(), temp.get_y() - 1, 'g');
                        break;
                    } else break;
                }
                case 2: {
                    if (valid_pos(position(temp.get_x(), temp.get_y() + 1))) {
                        enemies[i]->move_enemy(position(temp.get_x(), temp.get_y() + 1));
                        setCharacter(temp.get_x(), temp.get_y() + 1, 'g');
                        break;
                    } else break;
                }
                case 3: {
                    if (valid_pos(position(temp.get_x() - 1, temp.get_y()))) {
                        enemies[i]->move_enemy(position(temp.get_x() - 1, temp.get_y()));
                        setCharacter(temp.get_x() - 1, temp.get_y(), 'g');
                        break;
                    } else break;
                }
                case 4: {
                    if (valid_pos(position(temp.get_x() + 1, temp.get_y()))) {
                        enemies[i]->move_enemy(position(temp.get_x() + 1, temp.get_y()));
                        setCharacter(temp.get_x() + 1, temp.get_y(), 'g');
                        break;
                    } else break;
                }


            };
        }
    }
}


void simulation::move_lvl2() {
    for (unsigned i = 0; i < enemies2.size(); ++i) {
        if (enemies2[i]->get_lvl() == 2) {
            if (enemies2[i]->get_pos() == player.get_pos()) { return; }
            position temp0(enemies2[i]->get_pos().get_x(), enemies2[i]->get_pos().get_y() - 1);
            position temp1(enemies2[i]->get_pos().get_x(), enemies2[i]->get_pos().get_y() + 1);
            position temp2(enemies2[i]->get_pos().get_x() - 1, enemies2[i]->get_pos().get_y());
            position temp3(enemies2[i]->get_pos().get_x() + 1, enemies2[i]->get_pos().get_y());

            std::vector<int> temps_size = {};
            std::vector<position> valid_temps = {};
            if (valid_pos(temp0)) {
                valid_temps.push_back(temp0);
                temps_size.push_back(temp0.calc_vec(player.get_pos()).length());
            }
            if (valid_pos(temp1)) {
                valid_temps.push_back(temp1);
                temps_size.push_back(temp1.calc_vec(player.get_pos()).length());
            }
            if (valid_pos(temp2)) {
                valid_temps.push_back(temp2);
                temps_size.push_back(temp2.calc_vec(player.get_pos()).length());
            }
            if (valid_pos(temp3)) {
                valid_temps.push_back(temp3);
                temps_size.push_back(temp3.calc_vec(player.get_pos()).length());
            }

            for (int j = 0; j < temps_size.size(); ++j) {
                if (j == mind_index(temps_size)) {
                    if (temp0.calc_vec(player.get_pos()).length() == temps_size[j]) {
                        if (valid_pos(temp0)) {
                            enemies2[i]->move_enemy(temp0);
                            setCharacter(temp0.get_x(), temp0.get_y(), 'G');
                        } else continue;
                    } else if (temp1.calc_vec(player.get_pos()).length() == temps_size[j]) {
                        if (valid_pos(temp1)) {
                            enemies2[i]->move_enemy(temp1);
                            setCharacter(temp1.get_x(), temp1.get_y(), 'G');
                        } else continue;
                    } else if (temp2.calc_vec(player.get_pos()).length() == temps_size[j]) {
                        if (valid_pos(temp2)) {
                            enemies2[i]->move_enemy(temp2);
                            setCharacter(temp2.get_x(), temp2.get_y(), 'G');
                        } else continue;
                    } else if (temp3.calc_vec(player.get_pos()).length() == temps_size[j]) {
                        if (valid_pos(temp3)) {
                            enemies2[i]->move_enemy(temp3);
                            setCharacter(temp3.get_x(), temp3.get_y(), 'G');
                        } else continue;
                    }
                }
            }
        }


    }
}


