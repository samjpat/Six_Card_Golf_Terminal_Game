# Six Card Golf Terminal Game

This C++ program simulates a 2-person game of the card game Six Card Golf. You play against a computer player instead of another human. 

## Six Card Golf Rules

The objective is for players to have the lowest value of the cards in front of them by either swapping them for cards of lesser value or by pairing them up with cards of equal rank.
Players take turns drawing single cards from either the stock or discard piles. The drawn card may either be swapped for one of that player's 6 cards or discarded. 
If the card is swapped for one of the face-down cards, the card swapped in remains face up—the round ends when all of a player's cards are face-up.
Each round of the game is called a hole. This program allows you to specify the number of holes you want to play in the command line.

### Scoring:
Each ace counts 1 point.  
Each numeral card from 3 to 10 scores face value.  
Each jack or queen scores 10 points.  
Each king scores zero points.  
A pair of equal cards in the same column scores zero points for the column.  

The player with the lowest score after the agreed-upon number of holes is the winner.

## Running the program
1. Compile golf.cpp using
```
make
```

2. Run game
```
./golf_debug -h <num_holes>
```
Make sure to replace <num_holes> with an integer corresponding to the number of holes you want to play.

3. Follow terminal prompts to complete actions on your turn
