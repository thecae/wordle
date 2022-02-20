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

/**
 *  @brief   Backbone of the game
 *  @details Sets up the game and allows for the user to enter guesses, retrieve
 *           the answer for the Wordle based on its game number, and determine
 * the next best guess
 */
class Game {
public:
  /**
   *  @brief   Default constructor for the Game class
   *  @details The explicit constructor takes in a game number and creates
   *           a Game object based on this number.  From here, the object is
   *           able to start making guesses based on their expected value, and
   *           see the answer for the day.
   *  @param gameNum The number of the game
   */
  explicit Game(const size_t &gameNum);

  /**
   *  @brief   Returns the answer for the Wordle
   *  @details The getter function for the Game class.  The function returns
   *           the answer to the puzzle as a string.
   *  @return  The answer for the Wordle
   */
  std::string getAnswer() const;

  /**
   * @brief   Determines the best first guess
   * @details This function determines the best first guess.  The
   *          function returns the same result for every run because
   *          it is based on no other parameters and thus will run
   *          the same results every time.
   * @return  The best first guess and its expected value
   */
  std::string firstGuess() const;

  /**
   * @brief   Takes a guess and determines the next best guess
   * @details The make guess function takes in the most recent
   *          guess made by the user; based on the colored line,
   *          the program then eliminates all the words from the
   *          map that no longer are valid.  It then re-evaluates
   *          the expected values and returns the highest word
   * @param   guess The guess made by the user
   * @param   result The color coded line by the user
   * @return  A string with the next guess to make
   */
  std::string makeGuess(const std::string &guess,
                        const std::string &result) const;

private:
  /* The game number of the Wordle */
  const size_t wordleNumber;

  /* The answer to the Wordle */
  std::string wordleAnswer;

  /**
   *  @brief   Determines the answer to the Wordle from the site code.
   *  @details The function takes the list of answers from the Javascript coding
   *           the website and determines the answer based on the day provided
   *           in the constructor.
   */
  void fetchAnswer();
};

#endif /* WORDLE_GAME_H */
