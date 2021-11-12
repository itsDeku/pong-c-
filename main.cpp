#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<omp.h>

int main()
{
    int Lskip;
    Lskip = 0;
    int Rskip;
    Rskip = 0;
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    const float gameWidth = 800;
    const float gamehight = 600;
    const float ViewHight = 600;
    float pi = 3.14;
    sf::Vector2f paddleSize(12,100);
    float ballRadius = 10.f;

    sf::Clock AItimer;
    const float paddleSpeed = 500.f;
    float ballSpeed = 400.f;
    float ballAngle = 0.f;
    float AIspeed = 0.0f;
    sf::Time AItime = sf::seconds(0.1f);




    sf::RenderWindow window(sf::VideoMode(gameWidth,gamehight),"pong!!",sf::Style::Close |sf::Style::Resize);
    sf::View view(sf::Vector2f(gameWidth/2,gamehight/2),sf::Vector2f(gameWidth,gamehight));
    window.setFramerateLimit(100);
    sf::RectangleShape backGround(sf::Vector2f(gameWidth,gamehight));
    sf::Texture Lpaddle,Rpaddle,Tball,backgd;

    backgd.loadFromFile("data/background.png");
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize);
    Lpaddle.loadFromFile("data/paddle1.png");
    sf::RectangleShape rightPaddle;
    rightPaddle.setSize(paddleSize);
    Rpaddle.loadFromFile("data/paddle2.jpg");
    {
        {
            leftPaddle.setTexture(&Lpaddle);
        }
        {
            rightPaddle.setTexture(&Rpaddle);
        }
        {
            backGround.setTexture(&backgd);
        }
    }












    //declare left paddle

    //
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setOrigin(paddleSize/2.f);
    leftPaddle.setPosition(paddleSize.x/2 ,gamehight/2);

    //declare right paddle

    //
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(gameWidth - paddleSize.x /2 ,gamehight);
    rightPaddle.setOrigin(paddleSize/2.f);

    //declare ball
    sf::CircleShape ball;
    ball.setRadius(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius/2,ballRadius/2);
    //SOUND
    sf::SoundBuffer ballSoundF;
    ballSoundF.loadFromFile("data/peep.ogg");
    sf::Sound ballSound(ballSoundF);

    sf::SoundBuffer buttonSoundF;
    buttonSoundF.loadFromFile("data/button.wav");
    sf::Sound buttonSound(buttonSoundF);

    //font
    sf::Font font;
    font.loadFromFile("data/font.ttf");
    sf::Font font2;
    font2.loadFromFile("data/font2.ttf");
    //START UI
    sf::Text start;
    start.setFont(font2);
    start.setCharacterSize(60);
    start.setPosition(290,190);
    start.setColor(sf::Color(253,253,253));

    //SCORE ON GAMEPLAY
    //left score
    sf::Text Lscore;
    Lscore.setFont(font);
    Lscore.setCharacterSize(80);
    Lscore.setPosition(50.f,100.0f);
    Lscore.setColor(sf::Color::White);
    Lscore.setString("0");

    //right score
    sf::Text Rscore;
    Rscore.setFont(font);
    Rscore.setCharacterSize(80);
    Rscore.setPosition(gameWidth - 100.f,100.0f);
    Rscore.setColor(sf::Color::White);
    Rscore.setString("0");

    //GAMEOVER font
    //RESULTS

    sf::Text result;
    result.setFont(font2);
    result.setCharacterSize(60);
    result.setPosition(50.0f,gamehight/2 - 60);
    result.setColor(sf::Color(251,251,251));

    //button
    sf::Text over;
    over.setFont(font2);
    over.setCharacterSize(40);
    over.setPosition(25,515);
    over.setColor(sf::Color(253,253,253));

    //USER INTERFACE
    sf::RectangleShape mainMenu(sf::Vector2f(gameWidth,gamehight));
    sf::Vector2f ButtonSize(200,70);
    sf::RectangleShape Button1;
    Button1.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Button2;
    Button2.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Button3;
    Button3.setFillColor(sf::Color::Transparent);
    Button3.setSize(ButtonSize);
    Button3.setPosition(gameWidth /2 - ButtonSize.x /2 - 15, gamehight /2 + ButtonSize.y + 55);
    Button2.setSize(ButtonSize);
    Button2.setPosition(gameWidth /2 - ButtonSize.x /2 ,gamehight /2 - ButtonSize.y - 35);
    Button1.setSize(ButtonSize);
    Button1.setPosition(gameWidth/2 - ButtonSize.x /2 - 15 ,gamehight/2 + 10);


    sf::Texture maintex;
    maintex.loadFromFile("data/main.jpg");

    mainMenu.setTexture(&maintex);
    //game over
    sf::RectangleShape gameover(sf::Vector2f(gameWidth,gamehight));
    sf::Texture overback;
    overback.loadFromFile("data/deadpool.png");
    gameover.setTexture(&overback);
    sf::Vector2f eButtonSize(150,60);
    sf::RectangleShape eButton1;
    sf::RectangleShape eButton2;
    eButton2.setSize(eButtonSize);
    eButton1.setSize(eButtonSize);
    eButton1.setPosition(30,570 - 60);
    eButton2.setPosition(621,570 - 60);
    eButton1.setFillColor(sf::Color(25,25,25));
    eButton2.setFillColor(sf::Color(25,25,25));




    sf::Clock clock;

    bool UI = true;
    bool UIend = false;
    bool duo_palyer = false;
    bool solo_palyer = false;

    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if((event.type == sf::Event::Closed)||
                ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                UI = false;
                UIend = false;
                solo_palyer = true;

                clock.restart();

                leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                ball.setPosition(gameWidth /2 , gamehight /2 );
                do
                {
                    ballAngle = (std::rand()%360) * 2 * pi / 360;
                }
                while(std::abs(std::cos(ballAngle)) <0.7f);

            }

            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LShift))
            {
                UI = false;
                UIend = false;
                duo_palyer = true;

                clock.restart();

                leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                rightPaddle.setPosition(gameWidth - paddleSize.x/2 , gamehight/2);
                ball.setPosition(gameWidth/2 , gamehight/2);
                do
                {
                    ballAngle = (std::rand()%360) * 2 * pi / 360;
                }
                while(std::abs(std::cos(ballAngle)) < 0.7f);


            }

            if(event.type == sf::Event::Resized)
            {
                float aspectRatio = float(window.getSize().x/float(window.getSize().y));
                view.setSize(ViewHight * aspectRatio, ViewHight);


                Button1.setPosition(gameWidth/2,gamehight/2);
            }


        }
        if(UI)
        {
            clock.restart();
            ballSound.stop();
            start.setString("SOLO\n\nDUO\n\nEXIT");
            Lscore.setString("0");
            Rscore.setString("0");
            Lskip = 0;
            Rskip = 0;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(Button1.getPosition().x + ButtonSize.x > float(mousepos.x) &&
               Button1.getPosition().x < float(mousepos.x) &&
               Button1.getPosition().y + ButtonSize.y > float(mousepos.y) &&
               Button1.getPosition().y < float(mousepos.y))
            {
                 buttonSound.play();
                 UI = false;
                 duo_palyer = true;
                    clock.restart();

                    leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

            }



                if(Button2.getPosition().x < float(mousepos.x) &&
                   Button2.getPosition().x + ButtonSize.x > float(mousepos.x) &&
                   Button2.getPosition().y < float(mousepos.y) &&
                   Button2.getPosition().y + ButtonSize.y > float(mousepos.y))
                {
                    buttonSound.play();
                    UI = false;
                    solo_palyer = true;
                    clock.restart();

                    leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

                }
                if(Button3.getPosition().x < float(mousepos.x) &&
                   Button3.getPosition().x + ButtonSize.x > float(mousepos.x) &&
                   Button3.getPosition().y < float(mousepos.y) &&
                   Button3.getPosition().y + ButtonSize.y > float(mousepos.y))
                {
                    buttonSound.play();
                    window.close();
                }
            }


        }
        if(UIend)
        {
            clock.restart();
            ballSound.stop();
            over.setString("MENU\t\t\t\t\t   EXIT");
            if(Lskip >= 3 && Rskip < 3)
            result.setString("lost\t\t\t\twins");
            if(Rskip >= 3 && Lskip < 3)
            result.setString("wins\t\t\t\tlost");

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(eButton1.getPosition().x + ButtonSize.x > float(mousepos.x) &&
               eButton1.getPosition().x < float(mousepos.x) &&
               eButton1.getPosition().y + ButtonSize.y > float(mousepos.y) &&
               eButton1.getPosition().y < float(mousepos.y))
               {
                   buttonSound.play();
                   sf::sleep(sf::seconds(0.5));
                   UIend = false;
                   UI = true;

               }
            if(eButton2.getPosition().x < float(mousepos.x) &&
               eButton2.getPosition().x + eButtonSize.x > float(mousepos.x) &&
               eButton2.getPosition().y < float(mousepos.y) &&
               eButton2.getPosition().y + eButtonSize.y > float(mousepos.y))
            {
                buttonSound.play();
                window.close();
            }


            }

        }



        if(duo_palyer)
        {

        float deltaTime = clock.restart().asSeconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
           (leftPaddle.getPosition().y -paddleSize.y /2 > 5.0f))
        {
            leftPaddle.move(0.0f, -paddleSpeed * deltaTime);

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&
           (leftPaddle.getPosition().y + paddleSize.y /2 < gamehight - 5.0f))
        {
            leftPaddle.move(0.0f, paddleSpeed * deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&
        (rightPaddle.getPosition().y -paddleSize.y / 2 > 5.0f))
        {
            rightPaddle.move(0.0f, -paddleSpeed * deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&
        (rightPaddle.getPosition().y + paddleSize.y / 2 < gamehight - 5.0f))
        {
            rightPaddle.move(0.0f, paddleSpeed * deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            leftPaddle.setPosition(paddleSize.x/2,ball.getPosition().y);
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            rightPaddle.setPosition(gameWidth - paddleSize.x/2,ball.getPosition().y);
        }

        float factor = ballSpeed * deltaTime;
        ball.move(std::cos(ballAngle)*factor ,std::sin(ballAngle)*factor);

        //check collision
        if(ball.getPosition().x - ballRadius < 0.0f)
        {

            if(Lskip==0)
                Lscore.setString("1");
            if(Lskip==1)
                Lscore.setString("2");
            if(Lskip==2)
                Lscore.setString("3");
            if(Lskip==3)
          {
          sf::sleep(sf::seconds(0.1f));
          duo_palyer = false;
          solo_palyer = false;
          UIend = true;

          Rscore.setString("0");
          Lscore.setString("0");
          }
          else


            leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

                    Lskip++;


        }

           if(ball.getPosition().x - ballRadius >  gameWidth)
        {

            if(Rskip==0)
                Rscore.setString("1");
            if(Rskip==1)
                Rscore.setString("2");
            if(Rskip==2)
                Rscore.setString("3");
            if(Rskip==3)
          {
          sf::sleep(sf::seconds(0.1f));
          duo_palyer = false;
          solo_palyer = false;
          UIend = true;

          Rscore.setString("0");
          Lscore.setString("0");
          }
          else


            leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

                    Rskip++;

        }
        if(ball.getPosition().y - ballRadius - 10 < 0.0f)
        {
            ballSound.play();
            ballAngle = -ballAngle ;
        }
        if(ball.getPosition().y + ballRadius + 10 > gamehight)
        {
            ballSound.play();
            ballAngle = -ballAngle ;
        }
        //check collision paddles
        if(ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x/2 &&
           ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
           ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y/2 &&
           ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y/2  )
          {
              if(ball.getPosition().y > leftPaddle.getPosition().y)
                ballAngle = pi - ballAngle + (std::rand()%20) * pi/180;
              else
                ballAngle = pi - ballAngle - (std::rand()%20) * pi /180;


            ballSound.play();
            ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 +0.1f ,ball.getPosition().y);
          }
        if(ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x/2 &&
           ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
           ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y/2 &&
           ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y /2)
        {
            if(ball.getPosition().y > rightPaddle.getPosition().y)
                ballAngle = pi - ballAngle + (std::rand()%20) * pi / 180;
            else
                ballAngle = pi - ballAngle - (std::rand()%20) * pi / 180;


            ballSound.play();
            ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f , ball.getPosition().y);
        }
        }

        if(solo_palyer);
        {

            float deltaTime = clock.restart().asSeconds();

            // Move the player's paddle
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
               (leftPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
            {
                leftPaddle.move(0.f, -paddleSpeed * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
               (leftPaddle.getPosition().y + paddleSize.y / 2 < gamehight - 5.f))
            {
                leftPaddle.move(0.f, paddleSpeed * deltaTime);
            }

            // Move the computer's paddle
            if (((AIspeed < 0.f) && (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
                ((AIspeed > 0.f) && (rightPaddle.getPosition().y + paddleSize.y / 2 < gamehight - 5.f)))
            {
                rightPaddle.move(0.f, AIspeed * deltaTime);
            }

            // Update the computer's paddle direction according to the ball position
            if (AItimer.getElapsedTime() > AItime)
            {
                AItimer.restart();
                if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + paddleSize.y / 2)
                    AIspeed = paddleSpeed;
                else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - paddleSize.y / 2)
                    AIspeed = -paddleSpeed;
                else
                    AIspeed = 0.f;
            }

            // Move the ball
            float factor = ballSpeed * deltaTime;
            ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

            // Check collisions between the ball and the screen
            if (ball.getPosition().x - ballRadius < 0.f)
            {

            if(Lskip==0)
                Lscore.setString("1");
            if(Lskip==1)
                Lscore.setString("2");
            if(Lskip==2)
                Lscore.setString("3");
            if(Lskip==3)
          {
          sf::sleep(sf::seconds(0.1f));
          duo_palyer = false;
          solo_palyer = false;
          UIend = true;

          Rscore.setString("0");
          Lscore.setString("0");
          }
          else


            leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

                    Lskip++;
            }
            if (ball.getPosition().x + ballRadius > gameWidth)
            {

            if(Rskip==0)
                Rscore.setString("1");
            if(Rskip==1)
                Rscore.setString("2");
            if(Rskip==2)
                Rscore.setString("3");
            if(Rskip==3)
          {
          sf::sleep(sf::seconds(0.1f));
          duo_palyer = false;
          solo_palyer = false;
          UIend = true;

          Rscore.setString("0");
          Lscore.setString("0");
          }
          else


            leftPaddle.setPosition(paddleSize.x/2 , gamehight/2);
                    rightPaddle.setPosition(gameWidth - paddleSize.x / 2 , gamehight / 2 );
                    ball.setPosition(gameWidth /2 , gamehight /2 );
                    do
                    {
                        ballAngle = (std::rand()%360) * 2 * pi / 360;
                    }
                    while(std::abs(std::cos(ballAngle)) <0.7f);

                    Rskip++;
            }
            if (ball.getPosition().y - ballRadius < 0.f)
            {
                ballSound.play();
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
            }
            if (ball.getPosition().y + ballRadius > gamehight)
            {
                ballSound.play();
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, gamehight - ballRadius - 0.1f);
            }

            // Check the collisions between the ball and the paddles
            // Left Paddle
            if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
                ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > leftPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;


                ballSound.play();
                ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
            }

            // Right Paddle
            if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
                ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > rightPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;


                ballSound.play();
                ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
            }


        }




         window.clear(sf::Color::Black);
         window.setView(view);

         if(duo_palyer)
         {

         window.draw(backGround);
         window.draw(rightPaddle);
         window.draw(leftPaddle);
         window.draw(ball);
         window.draw(Rscore);
         window.draw(Lscore);

         }
         if(solo_palyer)
         {
             window.draw(backGround);
             window.draw(rightPaddle);
             window.draw(leftPaddle);
             window.draw(ball);
             window.draw(Rscore);
             window.draw(Lscore);

         }
         if(UI)

         {
             window.draw(mainMenu);
             window.draw(Button1);
             window.draw(Button2);
             window.draw(Button3);
             window.draw(start);


         }

         if(UIend)
         {
             window.draw(gameover);
             window.draw(eButton1);
             window.draw(eButton2);
             window.draw(result);
             window.draw(over);




         }

         window.display();
    }
    return 1;
}
