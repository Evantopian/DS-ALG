#include <iostream>
#include "Labyrinth.h"
#include <vector>


bool isPathToFreedom(MazeCell* start, const std::string& moves) {
    bool book = 0, potion = 0, wand = 0;
    MazeCell * cell = start;

    for (char ch : moves){   
        if (cell == nullptr) return false;

        switch(ch){
            case 'N' : cell = cell->north; break;
            case 'S' : cell = cell->south; break;
            case 'E' : cell = cell->east; break;
            case 'W' : cell = cell->west; break; 
        }
       
        if (cell != nullptr){
            Item item = cell->whatsHere;
            switch(item){
                case Item::SPELLBOOK : book = true; break;
                case Item::POTION : potion = true; break;
                case Item::WAND : wand = true; break;
                case Item::NOTHING : break;
            }
        }
    }
    return (book && potion && wand); 
}



