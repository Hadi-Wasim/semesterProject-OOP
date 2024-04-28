#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

//project setup by Hadi Wasim
using namespace sf;
using namespace std;

class MouseEvents : public Mouse {
	RenderWindow& window;
	bool mouseHeld = false;
	int mousePosPressedX = 0;
	int mousePosPressedY = 0;
	int mousePosReleasedX = 0;
	int mousePosReleasedY = 0;
public:
	// Constructor
	MouseEvents(RenderWindow& window) : window(window) {}

	// Handle mouse events
	void handleEvents() {
		int mouseX = getPosition(window).x;
		int mouseY = getPosition(window).y;

		if (isButtonPressed(Left)) {
			if (!mouseHeld) {  // Check if mouse was previously not held
				mouseHeld = true;
				mousePosPressedX = mouseX;
				mousePosPressedY = mouseY;
				cout << "Mouse button held at position: " << mousePosPressedX << ", " << mousePosPressedY << endl;
			}
		}
		else {
			if (mouseHeld) {  // Check if mouse was previously held
				mouseHeld = false;
				mousePosReleasedX = mouseX;
				mousePosReleasedY = mouseY;
				cout << "Mouse button released at position: " << mousePosReleasedX << ", " << mousePosReleasedY << endl;
			}
		}
	}

};
class Screen : public Sprite,public MouseEvents {

};



//Drawing the background
void createBack(RenderWindow& window) {
	//Drawing the background
	Image map_image;
	map_image.loadFromFile("Images/backwindow.jpg");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	window.draw(s_map);
}

//Drawing the map
void createMap(RenderWindow& window) {
	//Drawing a map
	Image map_image;//mage object for map
	map_image.loadFromFile("Images/grid.png");//load the file for the map
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(360, 160);

	window.draw(s_map);
}


int main()
{
	//Create a window, n*n
	RenderWindow window(VideoMode(1200, 700), "Plants Vs Zombies");
	//Game icon
	Image icon;
	if (!icon.loadFromFile("Images/icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());

	///////////////////////////////////////

	//Game field (5*9)
	//Point 137*79 - leftmost point
	//length 41; width 53
	const int ROWS = 5;
	const int COLS = 9;

	bool FIELD_GAME_STATUS[ROWS][COLS];

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			FIELD_GAME_STATUS[i][j] = true;
		}
	}

	Clock timeMoney;

	

	Clock clock;


	//test objects
	MouseEvents m(window);



	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//Create a background
		createBack(window);
		createMap(window);
		m.handleEvents();




		window.setSize(sf::Vector2u(550, 340));
		window.display();
	}
	return 0;
}