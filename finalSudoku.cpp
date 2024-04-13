#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <windows.h> 
using namespace std;

const int N = 9; 


void printBoard(int board[N][N], bool highlight[N][N] = nullptr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 19); 

    std::cout << "\x1b[48;2;0;0;0m"; 
    std::cout << "+---------+---------+---------+\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "| ";
        for (int j = 0; j < N; ++j) {
            if (highlight && highlight[i][j]) {
                SetConsoleTextAttribute(hConsole, 12); 
                std::cout << board[i][j];
            } else {
                if (board[i][j] == 0) {
                    std::cout << ".";
                } else {
                    std::cout << board[i][j];
                }
            }
            std::cout << " ";
            if ((j + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
        std::cout << "\n";
        if ((i + 1) % 3 == 0 && i != N - 1) {
            std::cout << "|---------+---------+---------|\n";
        }
    }
    std::cout << "+---------+---------+---------+\n";
    system("color 03");

    SetConsoleTextAttribute(hConsole, 15); 
}


void generateRandomSolvedSudokuBoard(int board[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
        }
    }
}


void generateRandomUnsolvedSudokuBoard(int board[N][N]) {
    
    std::srand(std::time(nullptr));

    
    int solvedBoard[N][N];
    generateRandomSolvedSudokuBoard(solvedBoard);

    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = solvedBoard[i][j];
        }
    }

    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (std::rand() % 2 == 0) { 
                board[i][j] = 0; 
            }
        }
    }
}


void playSudoku() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); 

    std::cout << "\t\t\t<===============================================================================================>" << endl;
    std::cout << "\t\t\t|                              WELCOME TO SUDOKU Game!                                          |" << endl;
    std::cout << "\t\t\t|         Fill in the missing numbers(represented by dot(.)) to solve the puzzle.               |" << endl;
    std::cout << "\t\t\t|              To play, enter the numbers 1-9 to fill in the empty cells.                       |" << endl;
    std::cout << "\t\t\t|                    You can't change the pre-filled numbers.                                   |" << endl;
    std::cout << "\t\t\t|    Try to fill each row, column, and 3x3 subgrid with the numbers 1-9 without repetition.     |" << endl;
    std::cout << "\t\t\t|                           Enter '0' for an empty cell.                                        |" << endl;
    std::cout << "\t\t\t|                                    Good luck!                                                 |"<< endl;
    std::cout << "\t\t\t<===============================================================================================>" << endl;

    SetConsoleTextAttribute(hConsole, 10); 
}


bool checkSolution(int board[N][N], int solution[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] != solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}


void playSudokuGame(int board[N][N], int solution[N][N]) {
    playSudoku();
    std::cout << " Here's the Sudoku board. Enter the numbers for each cell:\n";
    printBoard(board);

    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 0) {
                int value;
                std::cout << " Enter the number for cell (" << i << ", " << j << "): ";
                std::cin >> value;
                board[i][j] = value;
            }
        }
    }

    
    if (checkSolution(board, solution)) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10); 
        std::cout << "\n Congratulations! You've solved the Sudoku puzzle!\n";
        SetConsoleTextAttribute(hConsole, 15); 
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); 
        std::cout << "\n Sorry, the solution is incorrect. Better luck next time!\n";
        SetConsoleTextAttribute(hConsole, 15); 
    }
}


void printSolution() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); 

    int solvedBoard[N][N];
    generateRandomSolvedSudokuBoard(solvedBoard);
    std::cout << "\n Here's the correct solution:\n";
    printBoard(solvedBoard);

    SetConsoleTextAttribute(hConsole, 12); 
}

int main() {
    int sudokuBoard[N][N];
    int sudokuSolution[N][N];

    
    generateRandomUnsolvedSudokuBoard(sudokuBoard);

    
    generateRandomSolvedSudokuBoard(sudokuSolution);

   
    // std::cout << "\033[31;1;4m"; 

    
    playSudokuGame(sudokuBoard, sudokuSolution);

    
    printSolution();

    return 0;
}
