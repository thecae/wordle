/**
 *  @author Cole Ellis
 */

#ifndef WORDLE_GUESS_H
#define WORDLE_GUESS_H

#include "Game.h"
#include <map>
#include <vector>

/**
 *  @brief   Class for making guesses
 *  @details The Guess class is responsible for managing what happens once
 *           the user makes a guess.  The Guess class processes the removal
 *           of now-invalid words and then determines what words is the next
 *           best option.  This is a friend of the Game class.
 */
class Guess {
public:
  /* Declare the Game class as a friend */
  friend class Game;

  /**
   * @brief   Default constructor for the Guess class
   * @details This explicit default constructor for this class requires
   *          a guessed word and the associated result.  These parameters
   *          contain defaults to support use of the first guess in the Game
   *          class.
   * @param   word The word guessed by the user
   * @param   result The color line associated with the guessed word
   */
  explicit Guess(const std::string &word = "", const std::string &result = "");

  /**
   * @brief   Determines the best next guess for the user
   * @details This function determines the next best guess based on the guess
   *          that was just entered.  It does this by re-evaluating the expected values
   *          of each word and returning the maximum entry.
   * @return  The best next guess for the user
   */
  std::pair<std::string, double> nextGuess();

  /**
   * @brief   Finds the expected value of the word
   * @details This function finds the expected value of a word by considering
   *          all the combinations of what may happen if that word is entered,
   *          counting the number of words that would be remaining if that were
   *          to happen.  It then computes the probability this occurs,
   *          multiplying it by the amount of information that was just collected, to
   *          yield the expected value.
   * @param   word The word to find the expected value
   * @return  The expected value for the word
   */
  double initiateExpectedValue(const std::string &word) const;

private:
  /* The string that contains the guess */
  const std::string guess;

  /* THe string that contains the color line result */
  const std::string result;

  /* The map that contains the words and their expected values */
  std::map<std::string, double> wordList;

  /**
   *  @brief   Initiates the list of words
   *  @details This function reads all the words from a file
   *           and adds them to a hash map, associating the word
   *           with the expected value computed using the
   *           initiateExpectedValue() function.
   */
  void initiateList();

  /**
   *  @brief   Removes all invalid words
   *  @details This function considers all the words that are
   *           now invalid based on the provided color line and
   *           guess parameters.  It then removes the invalid
   *           words from the wordList.
   */
  void removeInvalidWords();

  /**
   * @brief   Finds the max entry
   * @details This function finds the max-valued entry in the list
   *          of words by iterating through the list and recording
   *          which entry has the highest expected value.
   * @return  The max entry in the list
   */
  std::pair<std::string, double> findMaxWord() const;
};

#endif /* WORDLE_GUESS_H */
