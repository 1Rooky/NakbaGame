#include <SFML/Graphics.hpp>
#include "Cell_Class.h"
#include "CellGrid.h"
#include "BallPlayer.h"
#include"Animation.h"
#include <SFML/Audio.hpp>

// calculates the distance in x-axis and y-axis for the two players.
Vector2f inView(Vector2f vextor1, Vector2f vector2) {

	return Vector2f(abs(vextor1.x - vector2.x), abs(vextor1.y - vector2.y));
}
// check if the distance is smaller than the window to be merged ?
bool isMerged(Vector2f windowSize, Vector2f inView) {
	if (inView.x < windowSize.x && inView.y < windowSize.y) return 1;
	return 0;
}

//history postion 
struct Position {
    float x;
    float y;
};


int main()
{
		sf::RectangleShape enemy(sf::Vector2f(20.0f, 20.0f));

		float delay = 10.f;
		std::vector<Position> positionHistory;

		//menu 
		int screenNumber = 1;
		sf::Texture backgroundTexture1;
		if (!backgroundTexture1.loadFromFile("./assets/MainMenu/background.png")) {
			return EXIT_FAILURE;
		}

		sf::Sprite background1(backgroundTexture1);
		background1.setPosition(0, 0);

		sf::Texture startGameTexture1, optionsTexture1, exitTexture1, startGameTexture2, optionsTexture2, exitTexture2;
		if (!startGameTexture1.loadFromFile("./assets/MainMenu/start1.png") ||
			!optionsTexture1.loadFromFile("./assets/MainMenu/options1.png") ||
			!exitTexture1.loadFromFile("./assets/MainMenu/exit1.png") ||
			!startGameTexture2.loadFromFile("./assets/MainMenu/start2.png") ||
			!optionsTexture2.loadFromFile("./assets/MainMenu/options2.png") ||
			!exitTexture2.loadFromFile("./assets/MainMenu/exit2.png")) {
			return EXIT_FAILURE;
		}

		sf::Sprite startGame(startGameTexture1);
		startGame.setPosition(850, 500);

		sf::Sprite options(optionsTexture1);
		options.setPosition(850, 600);

		sf::Sprite exit(exitTexture1);
		exit.setPosition(850, 700);

		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile("./assets/Music/Come.wav"))
			cout << "not loading" << endl;
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
		sound.setLoop(true);

		Texture texture;
		if (!(texture.loadFromFile("./assets/CharacterAnimations/Player1.png")))
			cout << "Error in loading";
		Texture backgroundT;
		if (!(backgroundT.loadFromFile("./assets/background.png")))
			cout << "Error in loading";
		Sprite background(backgroundT);
		background.setPosition(0, 0);

		Texture motherF;
		if (!(motherF.loadFromFile("./assets/CharacterAnimations/motherFront.png")))
			cout << "Error in loading";

		Texture motherB;
		if (!(motherB.loadFromFile("./assets/CharacterAnimations/motherBack.png")))
			cout << "Error in loading";

		Texture childF;
		if (!(childF.loadFromFile("./assets/CharacterAnimations/childFront.png")))
			cout << "Error in loading";

		Texture childB;
		if (!(childB.loadFromFile("./assets/CharacterAnimations/childBack.png")))
			cout << "Error in loading";


		Texture enemyT;
		if (!(enemyT.loadFromFile("./assets/CharacterAnimations/enemy.png")))
			cout << "Error in loading";

		Sprite enemyS(enemyT);
		Sprite mother(motherF);
		Sprite child(childF);
		mother.setScale(0.25f, 0.25f);
		child.setScale(0.25f, 0.25f);
		enemyS.setScale(0.25f, 0.25f);

		bool isFull = false;
		float splitBarSize = 20;
		float windowHeight = 900;
		float windowWidth = 1800 + splitBarSize;
		float fullMapHeight = 2000;
		float fullMapWidth = 3000;
		const int CellSize = 200;

		const int rownumber = fullMapWidth / CellSize;
		const int columnnumber = fullMapHeight / CellSize;

		sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Nakba");
		View vPlayer1; //player 1 view (camera)
		View vPlayer2;  // player 2 view (camera)
		View mergedView; // merged view (camara between both players)
		View fullView;  // full screen view (camera)
		View view = window.getDefaultView();

		vPlayer1.setViewport(FloatRect(0, 0, 0.5, 1.0f)); //puts player one camera to left
		vPlayer1.setSize(windowWidth / 2, windowHeight);

		vPlayer2.setViewport(FloatRect(((windowWidth / 2) + (splitBarSize / 2)) / windowWidth, 0, 0.5, 1.0f)); //puts player to to right with respect to the split bar
		vPlayer2.setSize(windowWidth / 2, windowHeight);

		mergedView.setSize(windowWidth, windowHeight);
		fullView.setSize(fullMapWidth, fullMapHeight);

		CellGrid test_grid(columnnumber, rownumber, CellSize);


		float time = 0;
		float deltatime = 0;
		float elapsedtime = 0;
		sf::Clock clock;
		sf::Clock clock2;
		float deltatimePlayer;

		vector<FloatRect*> myallBoundries;
		for (int i = 0; i < (rownumber * columnnumber); i++)
		{
			myallBoundries.push_back(&test_grid.Grid[i].wallSpiteBoundries[0]);
			myallBoundries.push_back(&test_grid.Grid[i].wallSpiteBoundries[1]);
			myallBoundries.push_back(&test_grid.Grid[i].wallSpiteBoundries[2]);
			myallBoundries.push_back(&test_grid.Grid[i].wallSpiteBoundries[3]);

		}
		bool isKeybroad = true;
		BallPlayer player1(20, Vector2f(100, 120), &texture, .5f, &test_grid, &deltatime, myallBoundries);
		BallPlayer player2(20, Vector2f(fullMapWidth - 120, fullMapHeight - 70), &texture, .5, &test_grid, &deltatime, myallBoundries);

		sf::Texture* HouseTexture = new sf::Texture;
		HouseTexture->loadFromFile("./assets/Tiles/house.png");
		sf::RectangleShape house(sf::Vector2f((float)CellSize, (float)CellSize));
		house.setTexture(HouseTexture);
		house.setPosition(0, 0);


		sf::Texture* TreeTexture = new sf::Texture;
		TreeTexture->loadFromFile("./assets/Tiles/Tree.png");
		sf::RectangleShape Tree(sf::Vector2f((float)CellSize, (float)CellSize));
		Tree.setTexture(TreeTexture);
		Tree.setPosition(fullMapWidth - 200, fullMapHeight - 200);

		enemy.setPosition(player2.getShap().getPosition().x, player2.getShap().getPosition().y);
		Vector2f startpostionBall2 = player2.getShap().getPosition();

		while (window.isOpen())
		{

			if (player1.isUp) {
				mother.setTexture(motherB);
			}
			else mother.setTexture(motherF);

			if (player2.isUp) {
				child.setTexture(childB);
			}
			else child.setTexture(childF);

			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			float currentTime = clock.getElapsedTime().asMilliseconds();
			deltatime = currentTime - time;
			time = clock.getElapsedTime().asMilliseconds();
			elapsedtime += deltatime;
			deltatimePlayer = clock2.restart().asSeconds();


			sf::Event event;
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					window.close();

				switch (screenNumber) {
				case 1:

					if (startGame.getGlobalBounds().contains(mousePos)) {
						// Change the picture when the mouse is over the options
						startGame.setTexture(startGameTexture2);
					}
					else {
						// Reset the texture when the mouse is not over the options
						startGame.setTexture(startGameTexture1);
					}

					if (options.getGlobalBounds().contains(mousePos)) {
						// Change the picture when the mouse is over the options
						options.setTexture(optionsTexture2);
					}
					else {
						// Reset the texture when the mouse is not over the options
						options.setTexture(optionsTexture1);
					}

					if (exit.getGlobalBounds().contains(mousePos)) {
						// Change the picture when the mouse is over the options
						exit.setTexture(exitTexture2);
					}
					else {
						// Reset the texture when the mouse is not over the options
						exit.setTexture(exitTexture1);
					}

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

						if (startGame.getGlobalBounds().contains(mousePos)) {

							screenNumber = 2;
						}
						else if (options.getGlobalBounds().contains(mousePos)) {

							//screenNumber = 3;
						}
						else if (exit.getGlobalBounds().contains(mousePos)) {
							window.close();
						}
						window.clear();

					}

					break;
				case 2:
					if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == Keyboard::X) { isFull = !isFull; } // full screen key ( X )
					}
					break;
				default:
					break;
				}



			}

			if (screenNumber == 1) {

				window.clear();
				window.setView(view);
				window.draw(background1);
				window.draw(startGame);
				window.draw(options);
				window.draw(exit);
			}

			if (screenNumber == 2)
			{
				if (Keyboard::isKeyPressed(Keyboard::K)) {
					isKeybroad = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::J)) {
					isKeybroad = false;
				}
				if (isKeybroad)
				{
					player1.move(Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S);
					player2.move(Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down);

				}
				else
				{
					player1.moveWithJoystick(0, Joystick::X, Joystick::Y);
					player2.moveWithJoystick(1, Joystick::X, Joystick::Y);

				}

				Position currentPosition = { player2.getShap().getPosition().x, player2.getShap().getPosition().y };
				positionHistory.push_back(currentPosition);

				if (!positionHistory.empty()) {
					Position delayedPosition = positionHistory[std::max(0, static_cast<int>(positionHistory.size()) - static_cast<int>(delay * 60))];
					enemy.setPosition(delayedPosition.x, delayedPosition.y);

					if ((enemy.getPosition().x != startpostionBall2.x) && enemy.getPosition().y != startpostionBall2.y)
					{
						if (child.getGlobalBounds().intersects(enemyS.getGlobalBounds()))
						{
							player2.setShap(startpostionBall2);
							//cout << "catch" << endl;

						}

					}

				}

				window.clear();

				////note: 55 and 66 are the size of players tiles so it merges after they both be in view.
				if (isMerged(Vector2f(windowWidth - 55, windowHeight - 66), inView(player1.getShap().getPosition(), player2.getShap().getPosition())) && !isFull) {

				
					mergedView.setCenter((player1.getShap().getPosition().x + player2.getShap().getPosition().x) / 2, (player1.getShap().getPosition().y + player2.getShap().getPosition().y) / 2);
					window.setView(mergedView);

					enemyS.setPosition(enemy.getPosition().x - 15, (enemy.getPosition().y - 100));
					mother.setPosition(player1.getShap().getPosition().x - 15, (player1.getShap().getPosition().y - 100));
					child.setPosition(player2.getShap().getPosition().x - 10, (player2.getShap().getPosition().y - 50));

					window.draw(background);
					window.draw(player1.getShap());
					window.draw(player2.getShap());
					test_grid.Display(window);
					window.draw(enemyS);
					window.draw(Tree);
					window.draw(child);
					window.draw(mother);
					window.draw(house);


				}
				else if (isFull) {

					fullView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
					fullView.setCenter(fullMapWidth / 2, fullMapHeight / 2);
					window.setView(fullView);

					enemyS.setPosition(enemy.getPosition().x - 15, (enemy.getPosition().y - 100));
					mother.setPosition(player1.getShap().getPosition().x - 15, (player1.getShap().getPosition().y - 100));
					child.setPosition(player2.getShap().getPosition().x - 10, (player2.getShap().getPosition().y - 50));

					window.draw(background);
					window.draw(player1.getShap());
					window.draw(player2.getShap());
					test_grid.Display(window);
					window.draw(enemyS);
					window.draw(Tree);
					window.draw(child);
					window.draw(mother);
					window.draw(house);

				}
				else {


					vPlayer1.setCenter(player1.getShap().getPosition());
					vPlayer2.setCenter(player2.getShap().getPosition());

					mother.setPosition(player1.getShap().getPosition().x - 15, (player1.getShap().getPosition().y - 100));
					child.setPosition(player2.getShap().getPosition().x - 10, (player2.getShap().getPosition().y - 50));
					enemyS.setPosition(enemy.getPosition().x - 15, (enemy.getPosition().y - 100));

					window.setView(vPlayer1);
		
					window.draw(background);
					window.draw(player1.getShap());
					window.draw(player2.getShap());
					test_grid.Display(window);
					window.draw(enemyS);
					window.draw(Tree);
					window.draw(child);
					window.draw(mother);
					window.draw(house);

					window.setView(vPlayer2);
					
					window.draw(background);
					window.draw(player1.getShap());
					window.draw(player2.getShap());
					test_grid.Display(window);
					window.draw(enemyS);
					window.draw(Tree);
					window.draw(child);
					window.draw(mother);
					window.draw(house);
				}

				if (mother.getGlobalBounds().intersects(child.getGlobalBounds()))
				{
					window.clear();
					window.setView(view);
					sf::Font font;
					if (!font.loadFromFile("./assets/Fonts/arial.ttf")) {
						std::cout << "Error loading font" << std::endl;
						return -1;
					}
					sf::Text text("You Win! ", font, 100);

					text.setPosition(windowWidth / 2 - text.getLocalBounds().width / 2,
					windowHeight / 2 - text.getLocalBounds().height / 2);
					window.draw(background);
					window.draw(text);
					window.display();
					screenNumber = 1;
					sleep(sf::seconds(5));
				}

			}
			window.display();
		}

	return 0;
}