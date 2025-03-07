#ifndef GAME_H
#define GAME_H

#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Field.h"

class Game {
public:
    Game(int fieldHeight, int fieldWidth, int countAliveCells, float CELL_SIZE,
        const sf::Color& aliveCellColor, const sf::Color& deadCellColor);

    void updateMap();

    [[nodiscard]] const sf::VertexArray& getMap() const {return vertices;};

    [[nodiscard]]bool update() const {return field->update();};

    ~Game();

private:
    Field* field;
    sf::VertexArray vertices;
    float CELL_SIZE;
    sf::Color aliveCellColor;
    sf::Color deadCellColor;
};

#endif //GAME_H
