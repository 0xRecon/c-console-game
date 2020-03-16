#include <iomanip>
#include <iostream>
#include <string>
#include <random>

struct Treasure{            // Structure for the chests and their locations.
    std::string chestName; 
    int chestRow;
    int chestColumn;
    double chestPoints;
    bool chestAvailable;
};


const int COLS = 10; 
const int ROWS = 10; // Not necessary but it is better for redability.

void randomizeTreasure(Treasure[], const int);
void treasureArrays (Treasure[]);
void fillGrid(char[][COLS], char);
void printGrid(const char[][COLS]);
void introMessage();
int validateInput (int );
double checkTreasure(Treasure tr[], const int r, const int c, int S, char SYM, char g[][COLS],
                     const char, const char);
void finalMessage (char [] [COLS], double, const int, const Treasure[], const char);


int main() {
    const char LEGEND_SYM = '-';      // Grid Symbol
    const char TREASURE_SYM = 'T';   // Treasure Symbol
    const char UNKNOWN_SYM = 'E';     // Empty Symbol
    const int TREASURE_AMOUNT = 5;
    const int USER_GUESSES = 5;
    char grid[ROWS][COLS];          
    Treasure tr[TREASURE_AMOUNT];    // Treasure Structure
    int userRow = 0;
    int userColumn = 0;
    double totalCounter = 0.00;
    int attemptCounter = 0;
    char userChoice = ' ';

    // Introduction
    introMessage();
    
    // Treasure Array
    treasureArrays (tr);

    // RandomizeTreasure
    randomizeTreasure(tr, TREASURE_AMOUNT);

    // Fill the 2D Grid with the Symbol
    fillGrid(grid, LEGEND_SYM);


    // OUTPUT 2D Grid
    printGrid(grid);


    //User Input
    do {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Enter the row #: \n";
        std::cin >> userRow;
        userRow = validateInput(userRow);
        std::cout << "Enter the column #: \n";
        std::cin >> userColumn;
        userColumn = validateInput(userColumn);
        totalCounter += checkTreasure(tr, userRow, userColumn, TREASURE_AMOUNT, LEGEND_SYM, grid, TREASURE_SYM, UNKNOWN_SYM );
        std::cout << std::endl;
        std::cout << "Would you like to play again (Y or N)? \n";
        std::cin >> userChoice;
        std::cout << std::endl;
        ++attemptCounter;
        // This to not print the grid when the user types 'N' to finish
        if (attemptCounter <= USER_GUESSES - 1 && toupper(userChoice) == 'Y') {
            printGrid(grid);
        } 
    } while (attemptCounter < USER_GUESSES && toupper(userChoice) == 'Y');

    // Printing Final Message to User
    finalMessage(grid, totalCounter, TREASURE_AMOUNT, tr, TREASURE_SYM);


    
    return 0;
}


void randomizeTreasure(Treasure tr [], const int SIZE){
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0,9);
 
    /* generate ten random numbers in [1,10] */
    for (size_t i = 0; i < SIZE ; i++)
    {
      tr[i].chestRow = distribution(generator) ;
    }
    for (size_t i = 0; i < SIZE; i++){
      tr[i].chestColumn = distribution(generator);
    }
    

 
}




void treasureArrays (Treasure tr []){
    tr[0] = {"Pirate's Chest", 0, 0, 145.90, true};
    tr[1] = {"Dragon's Chest", 0, 0, 258.24, true};
    tr[2] = {"Troll's Chest", 0, 0, 203.71, true};
    tr[3] = {"Queen's Chest", 0, 0, 190.15, true};
    tr[4] = {"Thief's Chest", 0, 0, 98.95, true};
}


void fillGrid(char arr [][COLS], const char SYM){
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            arr[r][c] = SYM;
        }
    }
}
              /*Not modifying the grid Array
              so it is used as a constant */
void printGrid(const char arr[][COLS]) {
    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    int temp = 0;
    for (int r = 0; r < ROWS; r++) {
        std::cout << temp++ << ' ';
        for (int c = 0; c < COLS; c++) {
            std::cout << arr[r][c] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Legend: - (Unknown); E (Empty); T (Treasure)\n";
    std::cout << std::endl;
}

void introMessage(){
    std::cout << "This is a treasure hunt game.\n""You have 3 attempts to find the 5 treasure chests hidden in the grid below.\n";
    std::cout << std::endl;
}
int validateInput (int a) {
    while (a < 0 || a > 9 || std::cin.fail()){
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(20, '\n');
        }

        std::cout << "That entry is invalid. Please enter a valid integer based on the grid size:";
        std::cin >> a;
        std::cout << std::endl;
    }
    return a;
}
double checkTreasure(Treasure tr[], const int r, const int c, int S, char SYM, char g[][COLS], const char TREASURE_SYM, const char UNKOWN_SYM) {
    double moneyLooted = 0.0;
    for (int i = 0; i < S; i++) {
        if (r == tr[i].chestRow && c == tr[i].chestColumn && tr[i].chestAvailable == true) {
            std::cout << "You have found the " << tr[i].chestName << "!\n"
                      << "Inside you find $" << tr[i].chestPoints << " worth of valuables.\n";
            g[r][c] = TREASURE_SYM;
            moneyLooted += tr[i].chestPoints;
            tr[i].chestAvailable = false;
            return moneyLooted;
        } else if (g[r][c] != SYM && tr[i].chestAvailable == false) {
            std::cout << "You already found the treasure at this location. "
                      << "Your stupidity has cost you a guess.\n" ;
            return moneyLooted;
        }
    }
    g[r][c] = UNKOWN_SYM;
    std::cout << "Sorry, there is no treasure at those coordinates." ;
    return moneyLooted;

}



                                                              /* Not modifying the Treasure Structure so it 
                                                               is put as a constant.*/
void finalMessage (char g [] [COLS] ,double a, const int SIZE, const Treasure tr[], const char TREASURE_SYM) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "The game is now over. You looted $" << a << " worth of valuables from chests.\n"
                 "The grid below shows the position of all treasure chests:\n";
    std::cout << std::endl;

    for(int i =0; i < SIZE; i++){
        g[tr[i].chestRow][tr[i].chestColumn] = TREASURE_SYM;
    }



    printGrid (g);
}






