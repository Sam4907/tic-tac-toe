#include <iostream>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char player, char computer);
int checkWinner(char *spaces, char player, char computer);
int checkDraw(char *spaces);
void playerFirst(char* spaces, char player, char computer);
void computerFirst(char* spaces, char player, char computer);
int minimax(char* spaces, char player, char computer, bool isComputerTurn);

int main(){
    char spaces[9];
    char player, computer, choice;
    std::fill(spaces, spaces + 9, ' ');
    std::cout<<"What would you like to play as (X or O)? ";
    std::cin>>player;
    computer=(player=='X')?'O':'X';
    std::cout<<"Do you want to start first? (Y or N) ";
    std::cin>>choice;
    (choice=='Y')?playerFirst(spaces, player, computer):computerFirst(spaces, player, computer);

    return 0;
}

void drawBoard(char *spaces){
    std::cout<<"      |      |      \n";
    std::cout<<"   "<<spaces[0]<<"  |   "<<spaces[1]<<"  |   "<<spaces[2]<<"   \n";
    std::cout<<"      |      |      \n";
    std::cout<<"____________________\n";
    std::cout<<"      |      |      \n";
    std::cout<<"   "<<spaces[3]<<"  |   "<<spaces[4]<<"  |   "<<spaces[5]<<"   \n";
    std::cout<<"      |      |      \n";
    std::cout<<"____________________\n";
    std::cout<<"      |      |      \n";
    std::cout<<"   "<<spaces[6]<<"  |   "<<spaces[7]<<"  |   "<<spaces[8]<<"   \n";
    std::cout<<"      |      |      \n";
}
void playerMove(char *spaces, char player) {
    int marker;
    while(true) {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> marker;

        if(marker < 1 || marker > 9) {
            std::cout << "Invalid input! Try 1-9.\n";
            continue;
        }

        marker--;

        if(spaces[marker] == ' ') {
            spaces[marker] = player;
            break;
        } else {
            std::cout << "Spot taken! Choose again.\n";
        }
    }
}

void computerMove(char *spaces, char player, char computer) {
    int bestScore = -1000;
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            spaces[i] = computer;
            int score = minimax(spaces, player, computer, false);
            spaces[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    if (move != -1){
    spaces[move] = computer;
    }
}

int checkWinner(char *spaces, char player, char computer){
    if((spaces[0]==player&&spaces[1]==player&&spaces[2]==player)||
    (spaces[3]==player&&spaces[4]==player&&spaces[5]==player)
        ||(spaces[6]==player&&spaces[7]==player&&spaces[8]==player)||
        (spaces[0]==player&&spaces[3]==player&&spaces[6]==player)
    ||(spaces[2]==player&&spaces[5]==player&&spaces[8]==player)||
    (spaces[1]==player&&spaces[4]==player&&spaces[7]==player)||
    (spaces[0]==player&&spaces[4]==player&&spaces[8]==player)||
    (spaces[2]==player&&spaces[4]==player&&spaces[6]==player)){
        return 1; //player wins
    }
    else if((spaces[0]==computer&&spaces[1]==computer&&spaces[2]==computer)||
    (spaces[3]==computer&&spaces[4]==computer&&spaces[5]==computer)
        ||(spaces[6]==computer&&spaces[7]==computer&&spaces[8]==computer)||
        (spaces[0]==computer&&spaces[3]==computer&&spaces[6]==computer)
    ||(spaces[2]==computer&&spaces[5]==computer&&spaces[8]==computer)||
    (spaces[1]==computer&&spaces[4]==computer&&spaces[7]==computer)||
    (spaces[0]==computer&&spaces[4]==computer&&spaces[8]==computer)||
    (spaces[2]==computer&&spaces[4]==computer&&spaces[6]==computer)){
        return 0; //computer wins
    }
    else{
        return -1;
    }

}
int checkDraw(char *spaces){
    if(spaces[0]!=' '&&spaces[1]!=' '&&spaces[2]!=' '&&spaces[3]!=' '&&spaces[4]!=' '&&spaces[5]!=' '&&
    spaces[6]!=' '&&spaces[7]!=' '&&spaces[8]!=' '){
        return 1; //draw
    }
    return 0;
}

void playerFirst(char* spaces, char player, char computer){
    bool running=true;
    drawBoard(spaces);
    while (running) {
        playerMove(spaces, player);

        int res = checkWinner(spaces, player, computer);
        if (res == 1) {
            drawBoard(spaces);
            std::cout << "You win!\n";
            break;
        }
        if (checkDraw(spaces)) {
            drawBoard(spaces);
            std::cout << "It's a draw!\n";
            break;
        }
        computerMove(spaces, player, computer);
        drawBoard(spaces);
        res = checkWinner(spaces, player, computer);
        if (res == 0) {
            std::cout << "Computer wins!\n";
            break;
        }

        if (checkDraw(spaces)) {
            std::cout << "It's a draw!\n";
            break;
        }
    }

}
void computerFirst(char* spaces, char player, char computer){
    bool running=true;
    while (running) {
        computerMove(spaces, player, computer);
        drawBoard(spaces);

        int res = checkWinner(spaces, player, computer);
        if (res == 0) {
            std::cout << "Computer wins!\n";
            break;
        }

        if (checkDraw(spaces)) {
            std::cout << "It's a draw!\n";
            break;
        }
        playerMove(spaces, player);

        res = checkWinner(spaces, player, computer);
        if (res == 1) {
            drawBoard(spaces);
            std::cout << "You win!\n";
            break;
        }

        if (checkDraw(spaces)) {
            drawBoard(spaces);
            std::cout << "It's a draw!\n";
            break;
        }
    }
}

int minimax(char *spaces, char player, char computer, bool isComputerTurn) {
    int result = checkWinner(spaces, player, computer);
    if (result == 0){
         return 10;
    }
    if (result == 1){
        return -10;
    }
    if (checkDraw(spaces)){
        return 0;
    }

    if (isComputerTurn) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                spaces[i] = computer;
                int score = minimax(spaces, player, computer, false);
                spaces[i] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                spaces[i] = player;
                int score = minimax(spaces, player, computer, true);
                spaces[i] = ' ';
                if (score < bestScore){
                    bestScore=score;
                } 
            }
        }
        return bestScore;
    }
}
