#include <random>

#include "../inc/Cell.h"
#include "../inc/Field.h"

#include <iostream>
#include <ostream>


Field::Field(const int height, const int width, const int initial_alive) {
    this->initial_alive = initial_alive;
    this->height = height;
    this->width = width;

    arr = new Cell*[height];
    prev_arr = new Cell*[height];

    for (int y = 0; y < height; ++y) {
        arr[y] = new Cell[width];
        prev_arr[y] = new Cell[width];
    }
}

void Field::creatLive() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> byHeight(0, height-1);
    std::uniform_int_distribution<int> byWidth(0, width-1);

    int x = byHeight(gen);
    int y = byWidth(gen);

    arr[x][y].set_type(alive);

    int count = 0;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0)
                continue;

            int new_x = x+i;
            int new_y = y+j;
            if(new_x >= 0 && new_x < height && new_y >= 0 && new_y < width && !arr[new_x][new_y].isAlive()) {
                arr[new_x][new_y].set_type(alive);
                count++;
            }

            if(count == initial_alive)
                return;
        }

}

bool Field::update() {
    copyLastStride();

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            const int count = countNeighbours(i, j);

            if(count == countAliveCells && !prev_arr[i][j].isAlive()) {
                arr[i][j].set_type(alive);
            }

            else if(prev_arr[i][j].isAlive())
                if( count < countAliveCells-1 || count > countAliveCells+1)
                    arr[i][j].set_type(dead);
        }
    }

    return true;

};

int Field::countNeighbours(int x, int y) const {
    int count = 0;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0)
                continue;

            const int new_x = x+i;
            const int new_y = y+j;
            if((new_x >= 0 && new_x < height) &&( new_y >= 0 && new_y < width))
                if(prev_arr[new_x][new_y].get_type() == alive)
                    ++count;
        }

    return count;
}

Field::~Field() {
    for(int i = 0; i < height; i++) {
        delete[] arr[i];
        delete[] prev_arr[i];
    }
    delete[] arr;
    delete[] prev_arr;
}

void Field::copyLastStride() {
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            prev_arr[i][j] = arr[i][j];
}

bool Field::checkForNonEqual() const {
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(arr[i][j] != prev_arr[i][j])
                return true;

    return false;
}
