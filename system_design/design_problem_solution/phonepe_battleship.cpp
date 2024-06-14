/*

--------------------------BattleShip Game-----------------------------------------------------------------
Design and implement a battleship game to be played between two players until one comes out as the winner.
Requirements:
    ● The game will be played in a square area of the sea with NxN grids which will be called a battlefield. “N” should be taken as input in your code.
    ● The battlefield will be divided in half between both the players. So in a NxN battlefield, NxN/2 grids will belong to PlayerA and the other NxN/2 grids will belong to playerB
    ● The size and location of each ship will be taken as input. Each ship will be assumed to be of Square shape. Both the players should be assigned equal fleet.
    ● The location of each ship in the NxN grids has to be taken as input (X, Y). X and Y should be integers. For eg. if a ship “SH1” is at (0, 0) and has the size of 4, its corners will be at (0, 0), (0, 4), (4, 0) and (4,4)
    ● Ships will remain stationary. No two ships should overlap with each other. However they can touch boundaries with each other.
    ● Each player will fire one missile towards the enemy field during his turn using the “random coordinate fire” strategy, which means the missile will hit at a random coordinate of the opponent’s field. It might hit or miss the opponent ship. In either case the turn is then transferred to the other player.
    ● In case of a hit, the opponent’s ship is destroyed.
    ● In case of a miss, nothing happens.
    ● No two missiles should ever be fired at the same coordinates throughout the course of the game.
    ● When all the ships of a particular player has been destroyed, he loses the game.

Implement the following functions:
    - initGame(N):
        - This will initialize the game with a battlefield of size NxN. Where the left half of N/2xN will be assigned to PlayerA and the right half will be assigned to PlayerB
    - addShip(//needed parameters):
        - This should add a ship of given size at the given coordinates in both the player’s fleet.
    - startGame():
        - This will begin the game, where PlayerA will always take the first turn. The output of each step should be printed clearly in the console.
          ● For eg.
              ○ PlayerA’s turn: Missile fired at (2, 4). “Hit”. PlayerB’s ship with id “SH1” destroyed.
              ○ PlayerB’s turn: Missile fired at (6, 1). “Miss”

    - viewBattleField():
       - This will display the battlefield as a NxN grid and all the ships along with the grids occupied by each ship. PlayerA’s ship with id SH1 will be marked as A-SH1, with id SH2 as A-SH2 and so on. Whereas PlayerB’s ships will be marked as B-SH1, B-SH2 and so on.
            ● Note: It should mark all the grids occupied by a ship and not just the center coordinate.


Guidelines:
    ● You should store the data in-memory using a language-specific data-structure.
    ● You can print the output in the console.
    ● Design your application in a way that a new fire strategy can be implemented and used
instead of the default one (random coordinate).
    ● Implement clear separation between your data layers and service layers.
Note: You can use multiple classes in the same coding environment
Expectations:
    ● Your code should cover all the mandatory functionalities explained above.
    ● Your code should be executable and clean.
    ● Your code should be properly refactored, and exceptions should be gracefully handled.
    ● Appropriate errors should be displayed on console when user input violates the rules of the
    game.
How will you be evaluated?
    ● Code Should be working, readable and testability
    ● Separation Of Concerns
    ● Object-Oriented concepts.
    ● Language proficiency.
    ● Scalability
    ● Test Coverage (Bonus Points)
*/

#include <bits/stdc++.h>
using namespace std;

const string EMPTY_SPACE = "empty";
const string PLAYER_A = "A";
const string PLAYER_B = "B";

// each cell in battlefield will tell which team and wether empty or have ship.
class Ship {
  public:
    string id;
    int size;
    pair<int, int> start_pos;
    string player; // check if its only player A OR B nothing else

    Ship(string i, int s, pair<int, int> sp, string p) {
      id = i;
      size = s;
      start_pos = sp;
      player = p;
    }

    void displayId() {
        cout << "The id from class is: " << id << endl;
    }
};

// shipMap stores the mapping of shipid to location(staring index)
map<string, Ship*> shipMap;

int random_num_gen(int start, int end) {
  return rand()%(end-start+1) + start;
}

pair<int,int> fire(string player, int N) {
  cout << "PLAYER : " << player << " fires!!! The target: ";
  pair<int, int> pos;
  if(player == PLAYER_A) {
    int x = random_num_gen(0, N-1);
    int y = random_num_gen(N/2, N-1);
    pos = {x,y};
    // return coordinates of missile in territory B
  } else {
    int x = random_num_gen(0, N-1);
    int y = random_num_gen(0, N/2-1);
    pos = {x,y};
    // return coordinates of missile in territory A
  }
  cout << pos.first << " " << pos.second << endl;
  return pos;
}

class BattleFieldGame {
  int N;
  vector<vector<pair<string, string>>> BattleField;
  public:
    BattleFieldGame(int n) {
      N = n;
      pair<string, string> dummy = {"some", "some"};
      vector<vector<pair<string, string>>> BF(n, vector<pair<string, string>>(n, dummy));
      BattleField = BF;
    }

    void initGame() {
      int half = N / 2;
      // player A Territory
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < half; j++) {
          BattleField[i][j] = make_pair(PLAYER_A, EMPTY_SPACE);
        }
      }

      for(int i = 0; i < N; i++) {
        for(int j = half; j < N; j++) {
           BattleField[i][j] = make_pair(PLAYER_B, EMPTY_SPACE);
        }
      }
    }

    void viewBattleField() {
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
          cout << BattleField[i][j].first << " " << BattleField[i][j].second << " ";
        }
        cout << endl;
      }
    }

    bool addShip(Ship *ship) {
      int size = ship->size;
      string player = ship->player;
      int x = ship->start_pos.first;
      int y = ship->start_pos.second;

      for(int i = x; i < x + size; i++) {
        for(int j = y; j < y + size; j++) {
          if (i >= N || j >= N) {
            cout << "Ship is out of BattleField" << endl;
            return false;
          }
          if(BattleField[i][j].first != player) {
            cout << "You cannot add ship in others persons territory";
            return false;
          }

          if(BattleField[i][j].second != EMPTY_SPACE) {
            cout << "Some other ship already present in the position";
            return false;
          }

          BattleField[i][j].second = ship->id;
        }
      }
      shipMap[ship->id] = ship;
      return true;
    }

    // startGame returns the winner
    string startGame(int &shipsA, int &shipsB) {
      string turn = PLAYER_A;
      while(true) {
        if(turn == PLAYER_A) {
          cout << "Player A attacks" << endl;
          pair<int, int> target = fire(PLAYER_A, N);
          bool hit = attack(target, PLAYER_A);
          if(hit) {
            shipsB--;
            if(shipsB == 0) return PLAYER_A;
          }
          turn = PLAYER_B;
        } else {
          cout << "Player B attacks" << endl;
          pair<int, int> target = fire(PLAYER_B, N);
          bool hit = attack(target, PLAYER_B);
          if(hit) {
            shipsA--;
          }
          if(shipsA == 0) return PLAYER_B;
          turn = PLAYER_A;
        }
      }

      return "";
    }

    bool attack(pair<int, int> target, string player) {
      if(BattleField[target.first][target.second].second == EMPTY_SPACE) {
        cout << "Target Missed" << endl;
        return false;
      }
      string id = (BattleField[target.first][target.second]).second;
      cout << "SHIP with ID"<<id<< "destroyed"<< endl;
      clearShip(id);
      return true;
    }

   void clearShip(string id) {
      Ship* shipHit = shipMap[id];
      int size = shipHit->size;
      int x = shipHit->start_pos.first;
      int y = shipHit->start_pos.second;
      for(int i = x; i < x + size; i++) {
        for(int j = y; j < y + size; j++) {
            BattleField[i][j].second = EMPTY_SPACE;
        }
      }
   }

};

void addShips(BattleFieldGame &bf, vector<Ship*> &ShipsA, vector<Ship*> &ShipsB) {
  Ship* ship1 = new Ship("SH1", 2, make_pair(0,0), PLAYER_A);
  bf.addShip(ship1);
  ShipsA.push_back(ship1);
  Ship* ship2 = new Ship("SH2", 3, make_pair(5,1), PLAYER_A);
  bf.addShip(ship2);
  ShipsA.push_back(ship2);
  Ship* ship3 = new Ship("SH3", 1, make_pair(9,3), PLAYER_A);
  bf.addShip(ship3);
  ShipsA.push_back(ship3);

  Ship* ship4 = new Ship("SH4", 2, make_pair(1,6), PLAYER_B);
  bf.addShip(ship4);
  ShipsB.push_back(ship4);
  Ship* ship5 = new Ship("SH5", 1, make_pair(5,7), PLAYER_B);
  bf.addShip(ship5);
  ShipsB.push_back(ship5);
  Ship* ship6 = new Ship("SH6", 3, make_pair(7, 6), PLAYER_B);
  bf.addShip(ship6);
  ShipsB.push_back(ship6);
}

int main() {
    BattleFieldGame bf(10);
    bf.initGame();
    vector<Ship*> shipsA, shipsB;
    addShips(bf, shipsA, shipsB);

    cout << "Battlefield before the match " <<endl;
    bf.viewBattleField();
    int noOfShipA = shipsA.size(), noOfShipB = shipsB.size();
    string winner = bf.startGame(noOfShipA, noOfShipB);

    cout << "Battlefield after the match " <<endl;
    bf.viewBattleField();

    cout << "\n Winner winner chicken dinner : " << winner;
    return 0;
}







/*

If we want a different firing strategy, we will make a new func to return the target

pair<int,int> fireWithDifferentStartegy(string player, int N) {
  // If we want a different firing strategy!!!
  return {0,0};
}

*/

