#include <iostream>
#include <ctime>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
int checkWinner(char *spaces, char player, char computer);
int checkDraw(char *spaces);

int main(){
    char spaces[9];
    std::fill(spaces, spaces + 9, ' ');
    char player= 'X';
    char computer= 'O';
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

        computerMove(spaces, computer);
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
void playerMove(char *spaces, char player){
    int marker;
    do{
        std::cout<<"Enter a spot to place a marker (1-9): ";
        std::cin>>marker;
        marker--;
        if(spaces[marker]==' '){
            spaces[marker]=player;
            break;
        }
    }while(marker < 0 || marker > 8);
}

void computerMove(char *spaces, char computer){
    srand(time(0));
    while(true){
        int marker=(rand()%9);
        if(spaces[marker]==' '){
            spaces[marker]=computer;
            break;
        }

    }
}
int checkWinner(char *spaces, char player, char computer){
    if((spaces[0]=='X'&&spaces[1]=='X'&&spaces[2]=='X')||(spaces[3]=='X'&&spaces[4]=='X'&&spaces[5]=='X')
        ||(spaces[6]=='X'&&spaces[7]=='X'&&spaces[8]=='X')||(spaces[0]=='X'&&spaces[3]=='X'&&spaces[6]=='X')
    ||(spaces[2]=='X'&&spaces[5]=='X'&&spaces[8]=='X')||(spaces[1]=='X'&&spaces[4]=='X'&&spaces[7]=='X')||
    (spaces[0]=='X'&&spaces[4]=='X'&&spaces[8]=='X')||(spaces[2]=='X'&&spaces[4]=='X'&&spaces[6]=='X')){
        return 1; //player wins
    }
    else if((spaces[0]=='O'&&spaces[1]=='O'&&spaces[2]=='O')||(spaces[3]=='O'&&spaces[4]=='O'&&spaces[5]=='O')
        ||(spaces[6]=='O'&&spaces[7]=='O'&&spaces[8]=='O')||(spaces[0]=='O'&&spaces[3]=='O'&&spaces[6]=='O')
    ||(spaces[2]=='O'&&spaces[5]=='O'&&spaces[8]=='O')||(spaces[1]=='O'&&spaces[4]=='O'&&spaces[7]=='O')||
    (spaces[0]=='O'&&spaces[4]=='O'&&spaces[8]=='O')||(spaces[2]=='O'&&spaces[4]=='O'&&spaces[6]=='O')){
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
