#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;

#include "Action.h"
#include "Coordinate.h"
#include "GameOver.h"
#include "Minefield.h"

static void printMinefield(Minefield const & minefield, bool gameOver)
{
    cout << minefield.toString(gameOver);
}

static void printMinefield(Minefield const & minefield)
{
    printMinefield(minefield, false);
}

static Action readAction(Minefield const & minefield, string const & prompt)
{
    cout << prompt;
    string action;
    unsigned short x;
    unsigned short y;
    cin >> action >> x >> y;
    return {action, Coordinate(x, y)};
}

static Action readAction(Minefield const & minefield)
{
    return readAction(minefield, "Enter action and coordinate: ");
}

static void visit(Minefield & minefield, Coordinate const & position)
{
    minefield.visit(position);

    if (minefield.sweepCompleted())
        throw GameOver("All mines cleared. Great job.", 0);
}

static void playRound(Minefield & minefield, unsigned short mines)
{
    printMinefield(minefield);

    auto const & action = readAction(minefield);

    if (action.action == "mark")
        return minefield.toggleMarked(action.position);

    if (!minefield.isInitialized())
        minefield.initialize(action.position, mines);

    visit(minefield, action.position);
}

int main()
{
    Minefield minefield(8, 8);

    while (true) {
        try {
            playRound(minefield, 8);
        } catch (GameOver const & gameOver) {
            printMinefield(minefield, true);
            cout << gameOver.what() << "\n";
            return gameOver.getReturnCode();
        }
    }
}
