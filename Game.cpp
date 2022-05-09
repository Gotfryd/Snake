#include "Game.h"

Game::Game() {

}

void Game::snakeLogic() {


    for(int i = snakeLength; i>0; i--){     //ogolne poruszanie sie weza
        wonsz[i].x= wonsz[i-1].x;
        wonsz[i].y = wonsz[i-1].y;
    }
    if(direction==0){
        wonsz[0].y+=1;
    }
    else if(direction==1){
        wonsz[0].x-=1;
    }
    else if(direction==2){
        wonsz[0].x+=1;
    }
    else if(direction==3){
        wonsz[0].y-=1;
    }

    if((wonsz[0].x == apple.x) && (wonsz[0].y == apple.y)){     //warunek zjedzenia jablka i dodanie segmentu wezowi oraz wygenerowanie jablka w nowym losowym miejscu
        snakeLength++;
        apple.x = rand() % xLine;
        apple.y = rand() % yLine;
    }

    if(wonsz[0].x > xLine ){        // 4 warunki zderzenia sie ze sciana w kazdym mozliwym kierunku i ustawienie weza w pozycje i dlugosc startowa
        wonsz[0].x = 0;
        wonsz[0].y = 0;
        snakeLength = 3;
    }

    if(wonsz[0].y > yLine){
        wonsz[0].x = 0;
        wonsz[0].y = 0;
        snakeLength = 3;
    }

    if(wonsz[0].x < 0){
        wonsz[0].x = 0;
        wonsz[0].y = 0;
        snakeLength = 3;
    }

    if(wonsz[0].y < 0){
        wonsz[0].x = 0;
        wonsz[0].y = 0;
        snakeLength = 3;
    }

    for(int i=1;i<snakeLength;i++){
        if(wonsz[0].x == wonsz[i].x && wonsz[0].y == wonsz[i].y){   // warunek zderzenia sie samym z soba i ustawienie pozycji oraz dlugosc startowej
            wonsz[0].x = 0;
            wonsz[0].y = 0;
            snakeLength = 3;
        }
    }

}

void Game::play() {

    sf::RenderWindow window(sf::VideoMode(screenWidth , screenHeight), "Gra Snake");
    window.setFramerateLimit(60);

    sf::Font fontCalibri;
    if (!fontCalibri.loadFromFile("../calibri.ttf"))
    {
        std::cout<< "Czcionka nie zaladowana!";
    }

    sf::Text menuText;
    menuText.setFont(fontCalibri);
    menuText.setFillColor(sf::Color::Green);
    menuText.setCharacterSize(80);
    menuText.setString("1. Graj \n2. Ranking \n3. Wyjdz");

    sf::Text difficultyText;
    difficultyText.setFont(fontCalibri);
    difficultyText.setFillColor(sf::Color::Green);
    difficultyText.setCharacterSize(80);
    difficultyText.setString("1. Easy \n2. Medium \n3. Hard");

    sf::RectangleShape square;
    sf::RectangleShape squareSnake;
    sf::RectangleShape squareApple;

    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::Black);
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color(128,128,128));

    squareSnake.setSize(sf::Vector2f(squareSize, squareSize));
    squareSnake.setFillColor(sf::Color::Green);
    squareSnake.setOutlineThickness(1);
    squareSnake.setOutlineColor(sf::Color(128,128,128));

    squareApple.setSize(sf::Vector2f(squareSize, squareSize));
    squareApple.setFillColor(sf::Color::Red);
    squareApple.setOutlineThickness(1);
    squareApple.setOutlineColor(sf::Color(128,128,128));

    sf::Clock countTime;

    apple.x = rand() % xLine;    //losowe ustawienie jablka przy wlaczeniu gry
    apple.y = rand() % yLine;



    while(window.isOpen()){
        float currentTime = countTime.getElapsedTime().asSeconds();
        countTime.restart();
        czas += currentTime;
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                direction = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                direction = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                direction = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                direction = 3;
            }
        }

        if(czas>delay){
            czas=0;
            snakeLogic();
        }

        window.clear();
        squareApple.setPosition(apple.x*squareSize, apple.y*squareSize);
        if(state == RUN) {

            for (int i = 0; i < yLine; i++) {
                for (int j = 0; j < xLine; j++) {
                    square.setPosition(j * squareSize, i * squareSize);
                    window.draw(square);
                }
            }
            for (int i = 0; i < snakeLength; i++) {
                squareSnake.setPosition(wonsz[i].x * squareSize, wonsz[i].y * squareSize);
                window.draw(squareSnake);
            }
            window.draw(squareApple);
        }
        if(state == MENU){
            window.draw(menuText);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                window.draw(difficultyText);    //trudnosc gry od razu sie wybiera pewnie dlatego, ze ekran odswieza sie zbyt szybko
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                    mode = EASY;
                    state = RUN;
                    delay = 0.2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    mode = MEDIUM;
                    state = RUN;
                    delay = 0.1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    mode = HARD;
                    state = RUN;
                    delay = 0.05;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                //pokaz ranking
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                //wylacz aplikacje
            }
        }

        window.display();
    }
}
