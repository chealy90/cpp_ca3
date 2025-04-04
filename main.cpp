#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

void displayMenu() {
    cout << "\n--------------------------------------------------\n";
    cout << " ============ A Bug's Life Menu =============\n";
    cout << "--------------------------------------------------\n";
    cout << "1. Display All Bugs____." << endl;
    cout << "2. Find Bug by ID____." << endl;
    cout << "3. Tap Board____." << endl;
    cout << "4. Display Life History Of All Bugs____." << endl;
    cout << "5. Write Life History of All Bug to File____." << endl;
    cout << "6. Display All Cells____." << endl;
    cout << "7. Run Simulation____." << endl;
    cout << "8. Exit." << endl;
    cout << "--------------------------------------------------\n";
    cout << " ============ SELECT AN OPTION =============\n";
}

int main() {
    Board board;
    bool initialise = false;
    int choice;

    cout << "WELCOME TO 'A Bug's Life' !" << endl;
    // cout << "\nInitialising board..." << endl;
    initialise = board.initialiseBoard("crawler-bugs.txt");
    if (!initialise) {
        cout << "Failed to initialize the board. Exiting program..." << endl;
        return 1;
    }
    // cout << "Board initialise successfully !\n" << endl;

    while (choice != 8) {
        displayMenu();

        if (!(cin >> choice)) { // https://cplusplus.com/forum/beginner/142433/
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "INVALID OPTION - Try again ><" << endl;
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                // display all bugs
                cout << "[ ..DISPLAYING ALL BUGS ]" << endl;
                board.displayAllBugs();
                break;
            }
            case 2: {
                // find buig
                cout << "[ ..SEARCH BUG BY ID ]" << endl;
                int id;
                cout << "Enter bug ID : ";
                cin >> id;
                cin.ignore(1000, '\n');
                board.findBug(id);
                break;
            }
            case 3: {
                // tap  board once
                cout << "[ ..TAPPING THE BOARD ]" << endl;
                board.tapBoard();
                cout << "Board tapped successful !" << endl;
                break;
            }
            case 4: {
                // display life history of bugs
                cout << "[ ..DISPLAYING LIFE HISTORY OF ALL BUGS ]" << endl;
                board.displayLifeHistoryAllBugs();
                break;
            }
            case 5: {
                // write life history to file
                cout << "[ ..WRITING BUG LIFE HISTORY TO FILE ]" << endl;
                board.writeLifeHistoryToFile();
                cout << "Bug life history successfully written to file !" << endl;
                break;
            }
            case 6: {
                //display all cells
                cout << "[ ..DISPLAYING ALL CELLS ]" << endl;
                board.displayAllCells();
                break;
            }
            case 7: {
                cout << "[ ..RUNNING SIMULATION ]" << endl;
                board.runSimulation();
                break;
            }
            case 8: {
                board.writeLifeHistoryToFile();
                cout << "[ ..NOW EXITING ] Thank you for using this program~" << endl;
                break;
            }
            default: {
                cout << "INVALID OPTION - Please enter a valid option :1" << endl;
                break;
            }
        }
    }

    return 0;
}
