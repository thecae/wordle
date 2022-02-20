/**
 *  @author Cole Ellis
 */

#include "../include/Guess.h"

Guess::Guess(const std::string &word, const std::string &result)
    : guess(word), result(result) {
  initiateList();
}

std::pair<std::string, double> Guess::nextGuess() {
  removeInvalidWords();

  // re-evaluate expected values with words removed
  for (auto word : wordList) {
    wordList[word.first] = initiateExpectedValue(word.first);
  }
  return findMaxWord();
}

void Guess::removeInvalidWords() {
  auto it = wordList.begin();
  while (it != wordList.end()) {
    bool wasRemoved = false;
    for (size_t i = 0; i < 5; ++i) {
      // remove if identical
      if (guess == it->first) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }

      // remove if it contains black letter
      if (result[i] == 'B' && it->first.find(guess[i]) != std::string::npos) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }

      // remove if it doesn't contain yellow letter
      // or contains yellow letter in same position
      if (result[i] == 'Y' && (it->first.find(guess[i]) == std::string::npos ||
                               it->first[i] == guess[i])) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }
      // remove if does not contain green letter in correct position
      if (result[i] == 'G' && it->first[i] != guess[i]) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }
    }
    if (!wasRemoved) {
      ++it;
    }
  }
}

void Guess::initiateList() {
  std::string filename = "../textfiles/possibleWords.txt";
  std::ifstream file(filename.c_str());
  if (!file) {
    exit(-1);
  }

  std::string str;
  std::cout << "Loading" << std::endl;
  // for every word, map the word to its expected value
  while (file >> str) {
    wordList.emplace(str, initiateExpectedValue(str));
  }
  std::cout << std::endl;

  file.close();
}

double Guess::initiateExpectedValue(const std::string &word) const {
  double expectedValue = 0;

  // grab permutations list from file
  std::vector<std::string> permutations;

  std::string filename = "../textfiles/colorPermutations.txt";
  std::ifstream file(filename.c_str());
  if (!file) {
    exit(-1);
  }

  std::string str;
  while (file >> str) {
    permutations.push_back(str);
  }

  file.close();

  // iterate through the 243 permutations
  for (const std::string &permutation : permutations) {
    double countPossibilities = 0;
    double countTotal = 0;

    // iterate through all words
    for (auto compare : wordList) {
      bool wasRemoved = false;
      for (size_t i = 0; i < 5; ++i) {
        // ignore identical words
        if (word == compare.first) {
          wasRemoved = true;
          break;
        }

        // ignore if word contains black square letter
        if (permutation[i] == 'B' &&
            compare.first.find(word[i]) != std::string::npos) {
          wasRemoved = true;
          break;
        }

        // ignore if word has yellow letter in right spot
        // or does not have yellow letter
        if (permutation[i] == 'Y' &&
            (compare.first.find(word[i]) == std::string::npos ||
             compare.first[i] == word[i])) {
          wasRemoved = true;
          break;
        }

        // ignore if does not have green letter in right spot
        if (permutation[i] == 'G' && compare.first[i] != word[i]) {
          wasRemoved = true;
          break;
        }
      }
      if (!wasRemoved) {
        ++countPossibilities;
      }
      ++countTotal;
    }

    // calculate probability as number of viable words over all words
    double probability = countPossibilities / countTotal;

    // calculate expected value as p * log2(1/p)
    // log2(1/p) represents number of "bits" given by that information
    if (probability != 0) {
      expectedValue += (probability * log2(1 / probability));
    }
  }
  std::cout << "." << std::endl; /* loading progress bar */
  return expectedValue;
}

std::pair<std::string, double> Guess::findMaxWord() const {
  // pair object for the biggest entry
  std::pair<std::string, double> maxEntry = *(wordList.begin());

  // iterate through the list in search of the biggest value
  for (auto word : wordList) {
    if (word.second > maxEntry.second) {
      maxEntry = word;
    }
  }
  return maxEntry;
}