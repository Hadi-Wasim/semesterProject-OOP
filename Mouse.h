#ifndef MOUSEEVENTS_H
#define MOUSEEVENTS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

//project setup by Hadi Wasim
using namespace sf;
using namespace std;

class MouseEvents {
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
    virtual void handleEvents() {
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!mouseHeld) {  // Check if mouse was previously not held
                mouseHeld = true;
                mousePosPressedX = mouseX;
                mousePosPressedY = mouseY;
                std::cout << "Mouse button held at position: " << mousePosPressedX << ", " << mousePosPressedY << std::endl;
            }
        }
        else {
            if (mouseHeld) {  // Check if mouse was previously held
                mouseHeld = false;
                mousePosReleasedX = mouseX;
                mousePosReleasedY = mouseY;
                std::cout << "Mouse button released at position: " << mousePosReleasedX << ", " << mousePosReleasedY << std::endl;
            }
        }
    }
};


#endif // MOUSEEVENTS_H