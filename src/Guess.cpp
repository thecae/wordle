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
      if (guess == it->first) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }
      if (result[i] == 'B' && it->first.find(guess[i]) != std::string::npos) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }
      if (result[i] == 'Y' && (it->first.find(guess[i]) == std::string::npos ||
                               it->first[i] == guess[i])) {
        wordList.erase(it++);
        wasRemoved = true;
        break;
      }
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
  while (file >> str) {
    wordList.emplace(str, initiateExpectedValue(str));
  }
  std::cout << std::endl;

  file.close();
}

double Guess::initiateExpectedValue(const std::string &word) const {
  double expectedValue = 0;

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

  for (const std::string &permutation : permutations) {
    double countPossibilities = 0;
    double countTotal = 0;
    for (auto compare : wordList) {
      bool wasRemoved = false;
      for (size_t i = 0; i < 5; ++i) {
        if (word == compare.first) {
          // std::cout << "X :: " << permutation << " :: " << word << " :: " <<
          // compare.first << std::endl;
          wasRemoved = true;
          break;
        }
        if (permutation[i] == 'B' &&
            compare.first.find(word[i]) != std::string::npos) {
          // std::cout << "X :: " << permutation << " :: " << word << " :: " <<
          // compare.first << std::endl;
          wasRemoved = true;
          break;
        }
        if (permutation[i] == 'Y' &&
            (compare.first.find(word[i]) == std::string::npos ||
             compare.first[i] == word[i])) {
          // std::cout << "X :: " << permutation << " :: " << word << " :: " <<
          // compare.first << std::endl;
          wasRemoved = true;
          break;
        }
        if (permutation[i] == 'G' && compare.first[i] != word[i]) {
          // std::cout << "X :: " << permutation << " :: " << word << " :: " <<
          // compare.first << std::endl;
          wasRemoved = true;
          break;
        }
      }
      if (!wasRemoved) {
        // std::cout << "O :: " << permutation << " :: " << word << " :: " <<
        // compare.first << std::endl;
        ++countPossibilities;
      }
      ++countTotal;
    }
    double probability = countPossibilities / countTotal;
    if (probability != 0) {
      expectedValue += (probability * log2(1 / probability));
    }
  }
  std::cout << "." << std::endl;
  return expectedValue;
}

std::pair<std::string, double> Guess::findMaxWord() const {
  std::pair<std::string, double> maxEntry = *(wordList.begin());
  for (auto word : wordList) {
    if (word.second > maxEntry.second) {
      maxEntry = word;
    }
  }
  return maxEntry;
}