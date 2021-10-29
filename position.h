//
// Created by Aaron Diether on 08.07.2021.
//

#ifndef EISBLATT7_CAR_SIM_POSITION_H
#define EISBLATT7_CAR_SIM_POSITION_H

#include <cstdint>


class position {
    int x;
    int y;
public:
    position();
    position(int x, int y);

    int get_x() const;
    int get_y() const;
    void set_x(const int &x);
    void set_y(const int &y);

    void swap(const position &other);

    const void operator=(const position &other);
    const bool operator==(const position &other);
    position calc_vec(const position &b);
    uint64_t length();

};

class vec : public position{};


#endif //EISBLATT7_CAR_SIM_POSITION_H
