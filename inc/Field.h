#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"

class Field {
public:
	Field(int height, int width, int initial_alive);

    void creatLive();

    bool update();

    [[nodiscard]] CellType getCell(int x, int y) const {
        return arr[x][y].get_type();
    };

    [[nodiscard]] int get_height() const {
        return height;
    }

    [[nodiscard]] int get_width() const {
        return width;
    }

    ~Field();

private:
    Cell** arr = nullptr;
    Cell** prev_arr = nullptr;
    int height;
    int width;
    int countAliveCells = 4;
    int initial_alive;

    [[nodiscard]] int countNeighbours(int x, int y) const;

    void copyLastStride();

    [[nodiscard]] bool checkForNonEqual() const;

};

#endif //FIELD_H
