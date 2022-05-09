#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"
int main(){
    srand(time(NULL));
    Game plansza; //edytowac mozna tylko poziom gry ktory zwieksza predkosc weza // waz nie przechodzi przez sciany
    plansza.play();
    return 0;
}