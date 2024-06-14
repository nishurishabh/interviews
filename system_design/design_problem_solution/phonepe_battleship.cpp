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

