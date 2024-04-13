#include <iostream>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <windows.h> // for changing console colors

const int N = 9; // Size of the Sudoku board

// Function to print the Sudoku board
void printBoard(int board[N][N], bool highlight[N][N] = nullptr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15); // Set text color to white

    std::cout << "\x1b[48;2;0;0;0m"; // Set background color to black using ANSI escape code

    std::cout << "+---------+---------+---------+\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "| ";
        for (int j = 0; j < N; ++j) {
            if (highlight && highlight[i][j]) {
                SetConsoleTextAttribute(hConsole, 12); // Set text color to red for highlighted cells
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
    SetConsoleTextAttribute(hConsole, 15); // Reset text color to white
}

// Function to generate a random solved Sudoku board
void generateRandomSolvedSudokuBoard(int board[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
        }
    }
}

// Function to generate a random unsolved Sudoku board and modify it in place
void generateRandomUnsolvedSudokuBoard(int board[N][N]) {
    // Initialize the random number generator
    std::srand(std::time(nullptr));

    // Generate a random solved Sudoku board
    int solvedBoard[N][N];
    generateRandomSolvedSudokuBoard(solvedBoard);

    // Copy the solved board to the unsolved board
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = solvedBoard[i][j];
        }
    }

    // Remove some numbers from the unsolved board to make it unsolved
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (std::rand() % 2 == 0) { // Randomly remove some numbers
                board[i][j] = 0; // 0 represents an empty cell
            }
        }
    }
}

// Function to provide instructions for playing Sudoku
void playSudoku() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); // Set text color to yellow

    std::cout << " Welcome to Sudoku!\n";
    std::cout << " To play, enter the numbers 1-9 to fill in the empty cells.\n";
    std::cout << " You can't change the pre-filled numbers.\n";
    std::cout << " Try to fill each row, column, and 3x3 subgrid with the numbers 1-9 without repetition.\n";
    std::cout << " Enter '0' for an empty cell.\n";
    std::cout << " Good luck!\n\n";

    SetConsoleTextAttribute(hConsole, 15); // Reset text color to white
}

// Function to check the solution of the Sudoku board and return true if correct, false otherwise
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

// Function to let the user play Sudoku
void playSudokuGame(int board[N][N], int solution[N][N]) {
    playSudoku();
    std::cout << " Here's the Sudoku board. Enter the numbers for each cell:\n";
    printBoard(board);

    // User input for each cell
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

    // Check the solution
    if (checkSolution(board, solution)) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10); // Set text color to green
        std::cout << "\n Congratulations! You've solved the Sudoku puzzle!\n";
        SetConsoleTextAttribute(hConsole, 15); // Reset text color to white
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // Set text color to red
        std::cout << "\n Sorry, the solution is incorrect. Better luck next time!\n";
        SetConsoleTextAttribute(hConsole, 15); // Reset text color to white
    }
}

// Function to print the solution of the Sudoku board
void printSolution() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); // Set text color to yellow

    int solvedBoard[N][N];
    generateRandomSolvedSudokuBoard(solvedBoard);
    std::cout << "\n Here's the correct solution:\n";
    printBoard(solvedBoard);

    SetConsoleTextAttribute(hConsole, 15); // Reset text color to white
}

int main() {
    int sudokuBoard[N][N];
    int sudokuSolution[N][N];

    // Generate a random unsolved Sudoku board
    generateRandomUnsolvedSudokuBoard(sudokuBoard);

    // Generate the corresponding solved Sudoku board
    generateRandomSolvedSudokuBoard(sudokuSolution);

    // Change the background color of the terminal using ANSI escape codes
    std::cout << "\x1b[48;2;0;0;0m"; // Set background color to black

    // Provide instructions and let the user play Sudoku
    playSudokuGame(sudokuBoard, sudokuSolution);

    // Print the correct solution after the game ends
    printSolution();

    return 0;
}
