//
// Created by Aaron Diether on 09.07.2021.
//

#ifndef PACMAN_TILE_H
#define PACMAN_TILE_H
#include "position.h"


class tile {
protected:
    char sym;
    position pos;
public:
    tile() = default;
    virtual char get_sym() const;
    virtual void set_sym( const char &other);
    virtual position get_pos() const;
    virtual void set_pos(const position &other);

};

class moveable : public tile {
    bool coin = true;
public:
    explicit moveable(position &p);
    void collect();
    bool is_collected() const;
    virtual void set_sym(const char &other) override;

};



#endif //PACMAN_TILE_H
