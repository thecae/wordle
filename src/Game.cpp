/**
 *  @author Cole Ellis
 */

#include "../include/Game.h"
#include "../include/Guess.h"

Game::Game(const size_t &gameNum) : wordleNumber(gameNum) { fetchAnswer(); }

std::string Game::getAnswer() const { return wordleAnswer; }

std::string Game::firstGuess() const {
  // initiate Guess object and find max pair
  Guess firstGuess;
  std::pair<std::string, double> guessWord = firstGuess.findMaxWord();

  // compact pair to proper format for output
  std::ostringstream out;
  out << guessWord.first << " (" << guessWord.second << ")";
  return out.str();
}

void Game::fetchAnswer() {
  std::map<size_t, std::string> wordMap;

  // open file with words
  const std::string filename = "../textfiles/possibleWords.txt";
  std::ifstream file(filename);
  if (!file) {
    exit(-1);
  }

  // fill array
  std::string str;
  size_t index = 0;
  while (file >> str) {
    wordMap.emplace(index++, str);
  }

  // store answer
  try {
    wordleAnswer = wordMap[wordleNumber];
  } catch (...) {
    std::cout << "Wordle entry not found.";
    exit(-2);
  }
}

std::string Game::makeGuess(const std::string &guess,
                            const std::string &result) const {
  // initiate object and find best match
  Guess newGuess(guess, result);
  std::pair<std::string, double> nextGuess = newGuess.nextGuess();

  // compact pair into proper string format and output
  std::ostringstream out;
  out << nextGuess.first << " (" << nextGuess.second << ")";
  return out.str();
}
