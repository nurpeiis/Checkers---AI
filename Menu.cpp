
#include <iostream>
#include "Menu.h"
using namespace std;
void Menu::options(){
  string option = "1";
  while (option == "1" || option == "2"){
    cout<<"\n\n\t Options"
    <<"\n1. Read Rules and Manual"
    <<"\n2. Play "
    <<"\n3. Quit"
    <<"\n Press option number: ";
        cin>>option;
    if (option == "1"){ 
      cout<< "This game is desgined using MiniMax Algorithm where the player gets to play with an artifically trained checkers player"<<endl;
      cout<<"Please enter the row and column of the starting cell then the row and column of the desired location to move to."<< endl;
    }
    else if (option == "2"){
      game.start();
    }
    else
    {
      cout<<"Exitting program... Exitting program"<<endl;
    }
  }
}
