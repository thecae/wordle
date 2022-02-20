/**
 *  @author Cole Ellis
 */

#include "include/Game.h"

int main() {
    std::cout << "STARTING" << std::endl;
    Game game(241);
    std::cout << game.firstGuess() << std::endl;

    while (true) {
        std::string guess, result;
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        std::cout << "Enter your result: ";
        std::cin >> result;

        if (guess == "-1" || result == "GGGGG") {
            break;
        }
        std::string nextMove = game.makeGuess("cauls", "GGGGB");
        std::cout << nextMove << std::endl;
    }

    return 0;
}