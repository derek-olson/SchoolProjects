//
//  Grid.hpp
//  SFML
//
//  Created by Derek Olson on 9/17/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp
#include "tetrominoes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <stdio.h>
#include <SFML/Window.hpp>
using namespace std;

class Grid : public sf::Drawable
{

public:
    // current position of block
    int cx;
    int cy;
    int cr;
    
    // initialize a tetrominoe
    Tetrominoes tet;
    
    //index of the tet type
    int tet_type;
    
    // params for window and cell size
    const int cell_size = 40;
    const int w_cnt = 10;
    const int h_cnt = 20;
    int world[20][10] = {0};
    
    const sf::Color color_map[7] = {
        sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Yellow,
        sf::Color::White, sf::Color::Magenta, sf::Color::Cyan
    };
    
    // methods
    auto new_block();
    auto clear_lines();
    auto go_down();
    void draw_world();
    void draw_block();
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
    }

    
};

auto Grid::new_block(){
    tet_type = rand() % 7;
    cx = w_cnt / 2;
    cy = 0;
    
};

auto Grid::clear_lines(){
    int to = h_cnt - 1;
    //from bottom line to top line...
    for (int from = h_cnt - 1; from >= 0; from--)
    {
        int cnt = 0;
        for (int x = 0; x < w_cnt; x++)if (world[from][x])cnt++;
        //if current line is not full, copy it(survived line)
        if (cnt < w_cnt)
        {
            for (int x = 0; x < w_cnt; x++)world[to][x] = world[from][x];
            to--;
        }
        //otherwise it will be deleted(clear the line)
    }
};

auto Grid::go_down(){
    cy++;
    if (tet.doesTetFit(tet_type, cr, cx, cy) == false) // hit bottom
    {
        cy--;
        for (int y = 0; y < 4; y++){
            for (int x = 0; x < 4; x++){
                if (tet[tet_type][tet.checkTetOrientation(x,y,cr)] != '.'){
                    world[cy + y][cx + x] = tet_type + 1;
                }
            }
        }
        clear_lines();
        //start next block
        new_block();
        return false;
    }
    return true;
};

void playGame();
    





#endif /* Grid_hpp */
