//
//  Grid.cpp
//  SFML
//
//  Created by Derek Olson on 9/17/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


sf::RectangleShape cell(sf::Vector2f(40, 40));
sf::RenderWindow window(sf::VideoMode(400, 800), "Tetris");

// method to draw the world
void Grid::draw_world(){
    for (int y = 0; y < h_cnt; y++){
        for (int x = 0; x < w_cnt; x++){
            if (world[y][x]){
                cell.setFillColor(color_map[world[y][x] - 1]);
                cell.setPosition(sf::Vector2f(x*cell_size, y*cell_size));
                window.draw(cell);
            }
        }
    }
};

// method to get the fill color and draw the tet
void Grid::draw_block(){
    cell.setFillColor(color_map[tet_type]);
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            if (tet[tet_type][y*4+x] != '.'){
                cell.setPosition(sf::Vector2f((cx + x)*cell_size, (cy + y)*cell_size));
                window.draw(cell);
            }
        }
    }
};

// function to render the window and play the game
void playGame(){
    Grid grid = Grid();
    sf::Clock clock;
    while (window.isOpen()){
        static float prev = clock.getElapsedTime().asSeconds();
        if (clock.getElapsedTime().asSeconds() - prev >= 0.5){
            prev = clock.getElapsedTime().asSeconds();
            grid.go_down();
        }
        sf::Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed) window.close();
                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::Left)
                    {
                        grid.cx--;
                        if (grid.tet.doesTetFit(grid.tet_type, grid.tet.numRotations, grid.cx, grid.cy) == false) grid.cx++;
                    }
                    else if (e.key.code == sf::Keyboard::Right)
                    {
                        grid.cx++;
                        if (grid.tet.doesTetFit(grid.tet_type, grid.tet.numRotations, grid.cx, grid.cy) == false) grid.cx--;
                    }
                    else if (e.key.code == sf::Keyboard::Down)
                    {
                        grid.go_down();
                    }
                    else if (e.key.code == sf::Keyboard::Up)
                    {
                        grid.tet.numRotations++;
                        if (grid.tet.doesTetFit(grid.tet_type, grid.tet.numRotations , grid.cx, grid.cy) == false) { grid.tet.numRotations++; grid.tet.numRotations++;grid.tet.numRotations++;}
                    }
                    else if (e.key.code == sf::Keyboard::Space)
                    {
                        while (grid.go_down() == true);
                    }
                }
        }
        window.clear();
        
        grid.draw_world();
        grid.draw_block();
        window.display();
    }
}

