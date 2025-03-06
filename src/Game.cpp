#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../inc/Game.h"
#include "../inc/Field.h"


Game::Game(int fieldHeight, int fieldWidth, int countAliveCells, float CELL_SIZE,
    const sf::Color& aliveCellColor, const sf::Color& deadCellColor) {
    field = new Field(fieldHeight, fieldWidth, countAliveCells);
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(fieldHeight * fieldWidth * 6);
    this->CELL_SIZE = CELL_SIZE;
    field->creatLive();
    this->aliveCellColor = aliveCellColor;
    this->deadCellColor = deadCellColor;
}

void Game::updateMap() {
    int n = field->get_height();
    int m = field->get_width();

    // Размер клетки

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            float x = j * CELL_SIZE;
            float y = i * CELL_SIZE;

            int index = (i * m + j) * 6; // 6 вершин на квадрат

            // Треугольник 1
            vertices[index + 0].position = sf::Vector2f(x, y);                  // Верхний левый
            vertices[index + 1].position = sf::Vector2f(x + CELL_SIZE, y);      // Верхний правый
            vertices[index + 2].position = sf::Vector2f(x + CELL_SIZE, y + CELL_SIZE); // Нижний правый

            // Треугольник 2
            vertices[index + 3].position = sf::Vector2f(x, y);                  // Верхний левый
            vertices[index + 4].position = sf::Vector2f(x + CELL_SIZE, y + CELL_SIZE); // Нижний правый
            vertices[index + 5].position = sf::Vector2f(x, y + CELL_SIZE);      // Нижний левый

            // Получаем тип клетки через метод getCell
            CellType cellType = field->getCell(i, j);
            sf::Color clr = (cellType == alive) ? aliveCellColor : deadCellColor;

            // Устанавливаем цвет всех вершин
            for (int k = 0; k < 6; k++) {
                vertices[index + k].color = clr;
            }
        }
    }
}

Game::~Game() {
    delete field;
}

