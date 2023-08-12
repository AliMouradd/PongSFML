#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
class Game{

private:
    sf::RenderWindow window; // Window
    sf::SoundBuffer bufferPaddleHit; // buffer for paddle hit sound
    sf::SoundBuffer bufferScore; //Buffer for Score Sound
    sf::Sound paddleHit; //Paddle sound
    sf::Sound scoreSound; // Score Sound
    sf::RectangleShape p1; // left player
    sf::RectangleShape p2; // right player
    sf::CircleShape ball; // Pong ball
    sf::Text scoreP1Text; //P1 score
    sf::Text scoreP2Text; //P2 score
    sf::Text startGame; // Starts game

    unsigned int screenWidth = sf::VideoMode::getDesktopMode().width; //Screenwidth
    unsigned int screenHeight = sf::VideoMode::getDesktopMode().height; // screen Height
    unsigned int ballStartPositionX = (screenWidth/2)-50;
    unsigned int ballStartPositionY = (screenHeight/2)+50;
    float xVelo = 8.89;
    float yVelo = 5;
    

public:
    Game(){

    }
    ~Game(){

    }

    int run(){


        window.create(sf::VideoMode::getDesktopMode(), "Pong", sf::Style::Fullscreen); //

        // Player 1 Left Side
        p1.setSize(sf::Vector2f(25,100));
        p1.setFillColor(sf::Color::White);
        p1.setPosition(5,screenHeight/2);

        //Player 2 Right Side
        p2.setSize(sf::Vector2f(25,100));
        p2.setFillColor(sf::Color::White);
        p2.setPosition(screenWidth-30,screenHeight/2);

        //Ball
        const float ballRad = 8.0f;
        ball.setRadius(ballRad);
        ball.setFillColor(sf::Color::White);
        ball.setOrigin(ballRad/2,ballRad/2);
        ball.setPosition(ballStartPositionX,ballStartPositionY);

        //Score Board
        int scoreP1 = 0;
        int scoreP2 = 0;


        sf::Clock clock;
        sf::Time elapsed1;

        bool isGameStart = false;

        //Start menu Text and settings
        sf::Font font;
        if(!font.loadFromFile("arial.ttf")){
            std::cout<<"Could not find font" << std::endl;
        }
        startGame.setFont(font);
        startGame.setString("Press Spacebar to start the Game");
        startGame.setCharacterSize(50);
        startGame.setFillColor(sf::Color::White);
        startGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
        startGame.setPosition(screenWidth/2 - 400,screenHeight/2);

        scoreP1Text.setFont(font);
        scoreP1Text.setString(std::to_string(scoreP1));
        scoreP1Text.setCharacterSize(50);
        scoreP1Text.setFillColor(sf::Color::White);
        scoreP1Text.setStyle(sf::Text::Bold);
        scoreP1Text.setPosition(100,100);

        scoreP2Text.setFont(font);
        scoreP2Text.setString(std::to_string(scoreP2));
        scoreP2Text.setCharacterSize(50);
        scoreP2Text.setFillColor(sf::Color::White);
        scoreP2Text.setStyle(sf::Text::Bold);
        scoreP2Text.setPosition(screenWidth-100,100);

        //Sound loading
        if(!bufferPaddleHit.loadFromFile("hit.mp3")){
            std::cout<<"Failled paddle hit noise" << std::endl;
        }
        paddleHit.setBuffer(bufferPaddleHit);
        if(!bufferScore.loadFromFile("score.mp3")){
            std::cout<<"Failled score noise" << std::endl;
        }
        scoreSound.setBuffer(bufferScore);

        //Game Engine
            while (window.isOpen())
        {
            if(isGameStart){

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                        
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window.close();
                }

                elapsed1 = clock.getElapsedTime();
                if(elapsed1.asMilliseconds() > sf::milliseconds(16).asMilliseconds()){ // Internal Clock

                    //Player 1 Movement Handling
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p1.getPosition().y > 0){
                        p1.move(0,-5);
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && p1.getPosition().y < screenHeight-p1.getSize().y){
                        p1.move(0,5);
                    }

                    //Player 2 Movement Handling
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p2.getPosition().y > 0){
                        p2.move(0,-5);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p2.getPosition().y < screenHeight-p2.getSize().y){
                        p2.move(0,5);

                    }
                    clock.restart();


                    //Ball Movement
                    ball.move(xVelo,yVelo);

                    // If the ball hits the roof or floor, bounce
                    if(ball.getPosition().y - ballRad <= 0 || ball.getPosition().y + ballRad >= screenHeight){
                        yVelo *= -1;
                        paddleHit.play();
                    }
                    
                    // If the ball hits the right wall restart the game +1 to player 1
                    if(ball.getPosition().x + ballRad >= screenWidth){

                        scoreP1 ++;
                        ball.setPosition(ballStartPositionX,ballStartPositionY);
                        scoreSound.play();
                        scoreP1Text.setString(std::to_string(scoreP1));

                    }

                    // If the ball hits the left wall restart the game +1 to player 2
                    if(ball.getPosition().x - ballRad <= 0){

                        scoreP2 ++;
                        ball.setPosition(ballStartPositionX,ballStartPositionY);
                        scoreSound.play();
                        scoreP2Text.setString(std::to_string(scoreP2));
                    }

                    //If the ball bounces with paddles flip its x velocity

                    if(ball.getGlobalBounds().intersects(p1.getGlobalBounds())){

                        xVelo *= -1;
                        paddleHit.play();
                    }

                    if(ball.getGlobalBounds().intersects(p2.getGlobalBounds())){

                        xVelo *= -1;
                        paddleHit.play();
                    }
                    


                    
                }

                window.clear();
                window.draw(ball);
                window.draw(p1);
                window.draw(p2);
                window.draw(scoreP1Text);
                window.draw(scoreP2Text);
                window.display();
            }
            else{
                

                

                bool endLoop = true;
                while(endLoop){
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed){
                            window.close();
                        }
                            
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                        isGameStart = true;
                        endLoop = false;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                        window.close();
                    }

                    window.clear();
                    window.draw(startGame);
                    window.display();

                }

            }
            
        }

        
        

        
    }


};


int main()
{
    Game myGame;
    myGame.run();
    return 0;
}
