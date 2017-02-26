#include <iostream>
#include <time.h> // time
#include <cstdlib> // rand


using namespace std;

int main()
{
    // rng seed and variables
    srand(time(0));
    int min = 1,
        max = 10;

    int gameRunning = 1,
        genNum,     // generated number
        guessInput,
        guessDifference,    // keeps track of difference for (genNum - guessInput) for hint messages
        guessCount,
        guessMax = 3;
    string guessGrammar = "s";
    string playAgain;
    locale loc;

    cout << "      ## ### ## ### ## ### ## ### ## ### ## ### ## ### ##\n"
            "              Welcome to the Number Guessing Game." << endl;

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
            } else {
                    // BEGIN event if used up all chances
                if (guessCount == (guessMax - 1)) {
                    cout << "Sorry, that's not correct. You've used up all your chances! \n"
                            "The correct answer was " << genNum << "." << endl;
                    guessCount = guessMax;
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
                    case 1:
                        cout << "Your guess is extremely close!" << endl;
                        break;
                    case 2:
                        cout << "The answer is on the tip of your tongue." << endl;
                        break;
                    case 3:
                        cout << "You're getting close to the answer." << endl;
                        break;
                    case 4:
                        cout << "Your guess isn't quite there yet." << endl;
                        break;
                    case 5:
                        cout << "Getting colder." << endl;
                        break;
                    default:
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
