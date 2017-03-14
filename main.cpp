#include <iostream>
#include <time.h> // time
#include <cstdlib> // rand
#include <fstream> // scoreboard file io

void loadScoreboard();
void updateScoreboard(int gameResult);
void printScoreboard();

int scoreboardWins = 0;
int scoreboardLosses = 0;

using namespace std;

int main()
{

    // rng seed and variables
    srand(time(0));
    int min = 1,
        max = 10,
        difficultyInput;

    int gameRunning = 1,
        genNum,     // generated number
        guessInput,
        guessDifference,    // keeps track of difference for (genNum - guessInput) for hint messages
        guessCount,
        guessMax = 3;
    string guessGrammar = "s";
    string playAgain;
    locale loc;

    loadScoreboard();

    cout << "\t## ### ## ### ## ### ## ### ## ### ## ### ## ### ##\n"
            "\t\tWelcome to the Number Guessing Game. \n" << endl;
    cout << "\tWhat difficulty would you like to play? \n"
            "\t1: Easy (1-10)    2: Medium (1-20)   3: Hard (1-30)" << endl;

    while (true) {
        cout << ">> ";
        cin >> difficultyInput;
        if (!cin.good() || difficultyInput < 1 || difficultyInput > 3) {
            cout << "Invalid input! Choices are 1, 2 or 3." << endl;
            cin.clear();
            cin.ignore(128, '\n');
        } else {
            break;
        }
    }

    if (difficultyInput == 2) {
        max = 20;
    } else if (difficultyInput == 3) {
        max = 30;
    }

    while (gameRunning) {
        // generate number BEFORE loop so that it stays constant.
        genNum = rand() % (max - min + 1) + min;

        cout << "         ----------------------------------------------\n"
                "You have 3 chances to guess a random number from " << min << " to " << max << ". \n"
                "Take your first guess! \n" << endl;

        for (guessCount = 0; guessCount < guessMax; guessCount++) {

            // check to make sure guessInput is valid
            for (;;) {
                cin >> guessInput;
                if (!cin.good() || guessInput < min || guessInput > max) {
                    cout << "Invalid number! Guess must be from " << min << " and " << max << "." << endl;
                    cin.clear();
                    cin.ignore
                    (128, '\n');
                } else {
                    break;
                }
            }
            // end guessInput check

            cout << endl;

            if (guessInput == genNum) {
                cout << "Congratulations, you win! " << genNum << " was the correct answer!" << endl;
                guessCount = guessMax;
                updateScoreboard(1);
                printScoreboard();
            } else {
                    // BEGIN event if used up all chances
                if (guessCount == (guessMax - 1)) {
                    cout << "Sorry, that's not correct. You've used up all your chances! \n"
                            "The correct answer was " << genNum << "." << endl;
                    guessCount = guessMax;
                    updateScoreboard(2);
                    printScoreboard();
                }

                    // END event if used up all chances

                    // BEGIN event if answer is incorrect
                if (guessCount < (guessMax - 1)) {
                    // plural check for chances left message
                    if (guessMax - guessCount <= 1) {
                        guessGrammar = "";
                    } else {
                        guessGrammar = "s";
                    }

                    cout << "Sorry, that's not correct. Please try again. You have " << ((guessMax - guessCount) - 1) << " chance" << guessGrammar << " left." << endl;

                    // if the user is within 1-5 numbers of the answer, a hint will be given
                    guessDifference = abs(genNum - guessInput);
                    switch (guessDifference) {
                case 1: case 2:
                        cout << "Your guess is extremely close!" << endl;
                        break;
                    case 3: case 4:
                        cout << "The answer is on the tip of your tongue." << endl;
                        break;
                    case 5: case 6:
                        cout << "Your guess isn't quite there yet." << endl;
                        break;
                    case 7: case 8:
                        cout << "Getting colder." << endl;
                        break;
                    default:
                        cout << "Ice cold." << endl;
                        break;
                    }
                }
                // END event if answer is incorrect
            }

            //cout << genNum << " ";
        // end of guessing loop
        }

        // ask to restart game
        cout << "\nWould you like to play again? (Y/N)" << endl;

        for (;;) {
        cin >> playAgain;

        // convert answer to lower case
        for (string::size_type i=0; i < playAgain.length(); i++)
            playAgain[i] = tolower(playAgain[i],loc);

            if (!cin.good() || (playAgain != "y" && playAgain != "n")) {
                cout << "\nThat is not a valid option. Y or N?" << endl;
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                if (playAgain == "n") {
                    gameRunning = 0;
                    cout << "\n############\n"
                            "Thanks for playing." << endl;
                } else {
                    gameRunning = 1;
                    cout << endl;
                }
                break;
            }
        }
    }

    // make while

    return 0;
}

void loadScoreboard() {
    try
        {
            ifstream inFile;
            inFile.open("./doc/scoreboard.txt",ios::in);

            inFile >> scoreboardWins;
            inFile >> scoreboardLosses;

            inFile.close();

        } catch (exception X)
        { cout << "File Error! Could not LOAD SCOREBOARD." << endl; }
}

void updateScoreboard(int gameResult)
{
    try
    {
        switch (gameResult) {
        case 1:
            scoreboardWins++;
            break;
        case 2:
            scoreboardLosses++;
            break;
        }

        ofstream outFile;
        outFile.open("./doc/scoreboard.txt",ios::out);

        // endl is delimiter
        outFile << scoreboardWins << endl;
        outFile << scoreboardLosses << endl;

        outFile.close();
    } catch (exception X)
    { cerr << "File Error! Could not UPDATE SCOREBOARD." << endl; }

}

void printScoreboard()
{
    try
    {
        cout << "=============== \n" <<
                "SCOREBOARD" << endl;
        cout << "Wins: " << scoreboardWins << endl;
        cout << "Losses: " << scoreboardLosses << endl;
        cout << "===============" << endl;
    }
    catch (exception X)
    { cerr << "File Error! Could not PRINT SCOREBOARD." << endl; }
}
