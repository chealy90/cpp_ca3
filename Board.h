//
// Created by favou on 02/04/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Crawler.h"
#include <vector>
#include <string>

class Board {
private:
    std:: vector<Crawler*> crawlers;
    std:: vector<Crawler*> cells[10][10];

public:
    Board();
    ~Board();

    bool initialiseBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;
    void tapBoard(); // this is menu 4 but menu 7 expands this
    void displayLifeHistoryAllBugs() const;
    void displayAllCells() const;
    void runSimulation();
    void writeLifeHistoryToFile() const;

    void updateCell();
    void fightInCell();
    bool isLastBugStanding();
};



#endif //BOARD_H
