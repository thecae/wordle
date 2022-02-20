# Wordle Solver
The aim of this project is to create a working Worldle solver that most accurately predicts the next best words to guess on the popular game.

Reading into the Javascript of the website, there is a list of allowed words that can be guessed (i.e. the game's dictionary), and a smaller list of words that contains all the possible words that could appear as the word of the day.  Both of these are placed under the [textfiles](https://github.com/thecae/wordle/tree/main/textfiles) folder of the project.

### How it Works
The program contains a list of all the possible words that can be used to make a guess.  The program then assesses each word's likelihood of being used based on its expected frequency; that is, by considering all possibilities of the outcome of entering the word at the current stage, we can assign it an "expected value" based on what might be the result of this word.

The *expected value* is computed as a function of each case's value and the probability of seeing that case.  The *value* of the case is how much information is offered to the user by achieving that case.  This is based on the amount of subsequent words are eliminated by seeing this case; one that eliminates more words is a more valuable case.

Nearly all the data in this project is stored in a hash map -- the primary piece of the data is the map that connects each word to its expected value, declared as:
```c++
std::map<std::string, double> expectedList; // example entry: {weary: 4.90}
```

By computing the maximum `double` value in `expectedList`, this determines the best word to use as it will provide the most amount of information to the user.  Of course, the user is at liberty to enter whatever word they choose.  The user then reports the word they enter and the subsequent outcome (the color line) to the program to then remove the invalid words, re-evaluate each word's expected value, then determine the next best word.

### Current Version
The current version of this project is **Version 1.0**.  The current average number of guesses for this code is around **3.4**.

The project runs rather slow and is rather inefficient at determining the next best words to be chosen.  Information is passed poorly and the program is rather exception-prone.  There is a lot of room for improvement in making this a safer, faster program.

The program currently implements an object-oriented style using two main classes, a *Game* class and a *Guess* class.  The Game class is responsible for being the backbone of the game running and keeping track of the overall progress.  The Guess class, a friend of the Game class, is initiated every time the user makes a new guess and takes care of the calculations in predicting the next best guess.

### Future Versions
I would like to see for future versions of this program to look further ahead and use a better predictive algorithm to determine the best words to choose.  Right now, the algorithm is lazy and slow and only looks one step into the future; I want future versions to look further ahead into determining the best words possible.

I also want the code to be more smartly laid out so that data transfer is more intelligent and code flows more smoothly.  I also want to better the code style to improvde readability.  I also want to find ways to further modularize the code to make it better.

