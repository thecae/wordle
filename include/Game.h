/**
 *  @author Cole Ellis
 */

#ifndef WORDLE_GAME_H
#define WORDLE_GAME_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

class Game {
public:
  explicit Game(const size_t &gameNum);

  std::string getAnswer() const;

  std::string firstGuess() const;

  std::string makeGuess(const std::string &guess,
                        const std::string &result) const;

private:
  const size_t wordleNumber;
  std::string wordleAnswer;

  void fetchAnswer();
};

#endif /* WORDLE_GAME_H */
