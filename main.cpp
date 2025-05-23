#include <iostream>
#include <string>
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "SuperBug.h"

using namespace std;
using namespace sf;

// Function to display menu options
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
    cout << "8. Run Visual Simulation" << endl;
    cout << "9. Exit." << endl;
    cout << "--------------------------------------------------\n";
    cout << " ============ SELECT AN OPTION =============\n";
}


void recalculateSpritesVectors(vector<Sprite> &sprites, vector<Text> &numbers, Board &board, const Font &font, const Texture &hopperTexture, const Texture &crawlerTexture, const Texture &superBugTexture) {
    //remake sprites
    sprites.clear();
    numbers.clear();
    for (Bug* bug: board.getAllAliveBugs()) {
        Sprite sprite;
        if (bug->isHopper()) {
            sprite.setTexture(hopperTexture);
        }
        else if (bug->isSuperBug()) {
            sprite.setTexture(superBugTexture);
        }
        else {
            sprite.setTexture(crawlerTexture);
        }

        sprite.setScale(Vector2f(60.0f / sprite.getLocalBounds().width, 60.0f / sprite.getLocalBounds().height));
        sprite.setPosition(Vector2f(static_cast<float>(bug->getPosition().x)*60, static_cast<float>(bug->getPosition().y)*60));
        sprites.push_back(sprite);

        Text text(to_string(bug->getId())+ "\n" + to_string(bug->getSize()), font, 15);
        text.setPosition(Vector2f(static_cast<float>(bug->getPosition().x)*60 + 15, static_cast<float>(bug->getPosition().y)*60 + 15));
        numbers.push_back(text);
    }
}

void runVisualSimulation() {
    bool initialise;
    Board board;
    initialise = board.initialiseBoard("bugs.txt");
    if (!initialise) {
        cout << "Failed to initialize the board. Exiting program..." << endl;
        return;
    }

    RenderWindow window(VideoMode(600, 700), "CA3");
    vector<RectangleShape> squares;
    RectangleShape infoBox;

    vector<Sprite> sprites;
    vector<Text> numbers;
    bool colourWhite=true;

    Texture hopperTexture, crawlerTexture, superBugTexture;
    if (!hopperTexture.loadFromFile("hopper.png") || !crawlerTexture.loadFromFile("crawler.png") || !superBugTexture.loadFromFile("superbug.png")) {
        cout << "Failed to load bug textures. Exiting program..." << endl;
        return;
    }

    SuperBug* superBug = nullptr;
    for (Bug* bug : board.getAllBugs()) {
        if (bug->isSuperBug()) {
            superBug = static_cast<SuperBug*>(bug);
            break;
        }
    }

    //https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
    sf::Font font;
    if (!font.loadFromFile("C:\\WINDOWS\\FONTS\\ARIAL.TTF"))
    {
        return;
    }

    for (int row = 0; row < 10;row++) {
        for (int col = 0; col < 10; col++) {
            RectangleShape square(Vector2f(60, 60));
            square.setFillColor( colourWhite?Color::White:Color::Black ); // squares alternate between white and black
            colourWhite=!colourWhite;
            square.setPosition(Vector2f(static_cast<float>(row)*60, static_cast<float>(col)*60 ));
            squares.push_back(square);
        }
        colourWhite = ! colourWhite;
    }

    for (Bug* bug: board.getAllAliveBugs()) {
        Sprite sprite;
        // texture based on bug type
        if (bug->isHopper()) {
            sprite.setTexture(hopperTexture);
        }
        else if (bug->isSuperBug()) {
            sprite.setTexture(superBugTexture);
        }
        else {
            sprite.setTexture(crawlerTexture);
        }

        sprite.setScale(Vector2f(60.0f / sprite.getLocalBounds().width, 60.0f / sprite.getLocalBounds().height));
        sprite.setPosition(Vector2f(static_cast<float>(bug->getPosition().x)*60, static_cast<float>(bug->getPosition().y)*60 ));
        sprites.push_back(sprite);

        Text text(to_string(bug->getId())+ "\n" + to_string(bug->getSize()), font, 15);
        text.setPosition(Vector2f(static_cast<float>(bug->getPosition().x)*60 + 15, static_cast<float>(bug->getPosition().y)*60 + 15));
        numbers.push_back(text);
    }

    infoBox.setSize(Vector2f(600, 100));
    infoBox.setFillColor(Color::White);
    infoBox.setPosition(0, 600);

    Text infoText("Crawlers(Ladybugs), Hoppers(Block bug) and SuperBug(original centred bug) shown using images\nTO USE: Press space to tap the board one move at a time, or 'p' to toggle the play through.", font, 12);
    infoText.setPosition(50, 630);
    infoText.setFillColor(Color::Black);


    window.setFramerateLimit(30);  // 30 redraws per second
    bool reactToMouseClicks=false;
    int shape_x;
    int shape_y;
    //board.runSimulation();
    bool runningSimulation = false;



    while (window.isOpen())
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                // controlling supervbug
                if (superBug != nullptr && superBug->isAlive()) {
                    bool superMoved = false;

                    if (event.key.code == Keyboard::Up) {
                        superBug->move(Direction::NORTH);
                        superMoved = true;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        superBug->move(Direction::SOUTH);
                        superMoved = true;
                    }
                    else if (event.key.code == Keyboard::Left) {
                        superBug->move(Direction::WEST);
                        superMoved = true;
                    }
                    else if (event.key.code == Keyboard::Right) {
                        superBug->move(Direction::EAST);
                        superMoved = true;
                    }

                    if (superMoved) {
                        // only superbug moves
                        recalculateSpritesVectors(sprites, numbers, board, font, hopperTexture, crawlerTexture, superBugTexture);

                        // check for fight/eat
                        board.updateCell();
                        board.eatFightFunction();
                    }
                }

                if (event.key.code == Keyboard::Key::Space) {
                    board.tapBoard();

                    //only remake sprites after changes to stop unncessesary calcs.
                    recalculateSpritesVectors(sprites, numbers, board, font, hopperTexture, crawlerTexture, superBugTexture);
                }
                else if (event.key.code == Keyboard::Key::P){
                    runningSimulation = !runningSimulation;
                }
            }

        }

        // tap is every 1 second until game over  https://www.geeksforgeeks.org/sleep-function-in-cpp/?ref=header_outind
        if (runningSimulation) {
            this_thread::sleep_for(chrono::milliseconds(1000));
            board.tapBoard();
            recalculateSpritesVectors(sprites, numbers, board, font, hopperTexture, crawlerTexture, superBugTexture);
        }


        window.clear();

        for (RectangleShape &square: squares) {
            window.draw(square);
        }

        for (Sprite &sprite: sprites) {
            window.draw(sprite);
        }

        for (Text &text: numbers) {
            window.draw(text);
        }
        window.draw(infoBox);
        window.draw(infoText);
        window.display();
    }
}

int main() {
    Board board;
    bool initialise = false;
    int choice;

    initialise = board.initialiseBoard("bugs.txt");
    if (!initialise) {
        cout << "Failed to initialize the board. Exiting program..." << endl;
        return 1;
    }

    cout << "WELCOME TO 'A Bug's Life' !" << endl;
    // cout << "\nInitialising board..." << endl;

    // cout << "Board initialise successfully !\n" << endl;

    while (choice != 9) {
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
                cout << "[ ..RUNNING VISUAL SIMULATION ]" << endl;
                runVisualSimulation();
                break;

            }
            case 9: {
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