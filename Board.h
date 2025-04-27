//
// Created by favou on 02/04/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Crawler.h"
#include "Bug.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>


class Board {
private:
    std::vector<Bug*> bugs;
    std::vector<Bug*> cells[10][10];

    std::map<int, int> eatenBy;
public:
    Board();
    ~Board();
    void updateCell();
    void eatFightFunction();

    bool initialiseBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;
    void tapBoard();
    void displayLifeHistoryAllBugs() const;
    void displayAllCells() const;
    void runSimulation();
    void writeLifeHistoryToFile() const;
    bool isLastBugStanding();

    std::vector<Bug*> getAllBugs();
    std::vector<Bug*> getAllAliveBugs();


};



#endif //BOARD_H