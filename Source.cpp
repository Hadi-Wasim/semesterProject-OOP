#include "Mouse.h"

class MainMenu : public MouseEvents
{
    RenderWindow& window;
    Texture PlayButtonTexture;
    Texture InstructionsButtonTexture;
    Sprite PlayButton;
    Sprite InstructionsButton;
    Image backgroundImage;
    Texture backgroundTexture;
    Sprite background;

    void setupButtons() {
        PlayButtonTexture.loadFromFile("Images/startButton.png");
        InstructionsButtonTexture.loadFromFile("Images/Instructions.png");

        PlayButton.setTexture(PlayButtonTexture);
        InstructionsButton.setTexture(InstructionsButtonTexture);

        // Position and size adjustments for the buttons
        PlayButton.setPosition(700, 350);
        InstructionsButton.setPosition(690, 600);
    }
    void setupBG() {
        backgroundImage.loadFromFile("Images/MainMenuorg.jpg");
        backgroundTexture.loadFromImage(backgroundImage);

        background.setTexture(backgroundTexture);
        background.setPosition(0, 0);
    }

public:
    MainMenu(RenderWindow& window) : MouseEvents(window), window(window) {
        setupBG();
        setupButtons();
    }

    virtual void handleEvents()  {
        MouseEvents::handleEvents();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;
            if (PlayButton.getGlobalBounds().contains(mouseX, mouseY)) {
                cout << "Play button clicked!" << endl;
                // Switch to gameplay screen
            }
            else if (InstructionsButton.getGlobalBounds().contains(mouseX, mouseY)) {
                cout << "Instructions button clicked!" << endl;
                // Switch to instructions screen
            }
            // Add more button checks as needed
        }
    }

    void draw(RenderWindow& window) {
        window.draw(background);
        window.draw(PlayButton);
        window.draw(InstructionsButton);
    }
};

class ScreenManager {
    RenderWindow& window;
    MainMenu mainMenu;

public:
    ScreenManager(RenderWindow& window) : window(window), mainMenu(window) {}

    void handleEvents() {
        mainMenu.handleEvents();
    }

    void draw() {
        window.clear(Color::White);
        mainMenu.draw(window);
        window.display();
    }
};

int main()
{
    //Create a window, n*n
    RenderWindow window(VideoMode(1600, 914), "Plants Vs Zombies");
    //Game icon
    Image icon;
    if (!icon.loadFromFile("Images/icon.png")) {
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

    ScreenManager screenManager(window);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        float moneyTime = timeMoney.getElapsedTime().asSeconds();

        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        screenManager.handleEvents();
        screenManager.draw();

    }
    return 0;
}