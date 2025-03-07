#include <string>
#include <filesystem>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <yaml-cpp/yaml.h>

#include "../inc/Game.h"

struct Config {
    int width;
    int height;
    int initialAlive;
    float cellSize;
    float updateDelay;

    sf::Color backgroundColor;
    sf::Color aliveColor;
    sf::Color deadColor;

    std::string title;
    sf::Vector2u window_size;
    unsigned int framerate_limit;
};


Config loadConfig(const std::string& filename) {
    YAML::Node config = YAML::LoadFile(filename);

    Config cfg;
    cfg.width = config["game_settings"]["width"].as<int>();
    cfg.height = config["game_settings"]["height"].as<int>();
    cfg.initialAlive = config["game_settings"]["initial_alive"].as<int>();
    cfg.cellSize = config["game_settings"]["cell_size"].as<float>();
    cfg.updateDelay = config["game_settings"]["update_delay"].as<float>();

    auto bg = config["colors"]["background"].as<std::vector<int>>();
    auto alive = config["colors"]["alive_cell"].as<std::vector<int>>();
    auto dead = config["colors"]["dead_cell"].as<std::vector<int>>();

    cfg.backgroundColor = sf::Color(bg[0], bg[1], bg[2]);
    cfg.aliveColor = sf::Color(alive[0], alive[1], alive[2]);
    cfg.deadColor = sf::Color(dead[0], dead[1], dead[2]);

    cfg.title = config["window"]["title"].as<std::string>();
    auto mode_size = config["window"]["window_size"].as<std::vector<int>>();
    cfg.window_size = sf::Vector2u(mode_size[0], mode_size[1]);
    cfg.framerate_limit = config["window"]["framerate_limit"].as<unsigned int>();

    return cfg;
}


int main()
{
    std::string configFilePath = "../../config.yaml";

    if (!std::filesystem::exists(configFilePath)) {
        std::cerr << "Error: file config.yaml does not exist!" << std::endl;
        return 1;
    }

    Config config = loadConfig(configFilePath);

    sf::RenderWindow window(sf::VideoMode(config.window_size), config.title, sf::Style::Default);
    window.setFramerateLimit(config.framerate_limit);// call it once after creating the window

    Game game(config.height, config.width, config.initialAlive, config.cellSize,
        config.aliveColor, config.deadColor);
    game.updateMap();

    sf::Clock clock;
    float updateInterval = config.updateDelay;


    bool new_update = true;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= updateInterval && new_update) {
            bool is_continue = game.update();
            if (!is_continue)
                new_update = false;

            game.updateMap();

            clock.restart();
        }


        window.clear(config.backgroundColor);

        window.draw(game.getMap());

        // end the current frame
        window.display();
    }

    return 0;
}
