/**
 *  @author Cole Ellis
 */

#ifndef WORDLE_GUESS_H
#define WORDLE_GUESS_H

#include "Game.h"
#include <map>
#include <vector>

class Guess {
public:
  friend class Game;

  explicit Guess(const std::string &word = "", const std::string &result = "");

  std::pair<std::string, double> nextGuess();

  double initiateExpectedValue(const std::string &word) const;

private:
  const std::string guess;
  const std::string result;

  std::map<std::string, double> wordList;

  void initiateList();

  void removeInvalidWords();

  std::pair<std::string, double> findMaxWord() const;
};

#endif /* WORDLE_GUESS_H */
