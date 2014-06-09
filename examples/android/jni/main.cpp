#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <algorithm>
#include <vector>

// A simple struct to define/store circles
struct circle {
    float x;
    float y;
    int size;
};

// A callback for std::remove_if() used to determine circles to be deleted
bool removeCheck(const circle &c)
{
    return c.size > 255;
}

int main(int argc, char *argv[])
{
    // Create a window as usual
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");

    // Determine the line width based on resolution
    const float lineThickness = sf::VideoMode::getDesktopMode().width / 255.f;

    // This vector will store all circles to be drawn
    std::vector<circle> circles;

    // A shape to be used for actual drawing
    sf::CircleShape shape(1);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOrigin(.5f, .5f);
    shape.setOutlineThickness(lineThickness);

    // Some music to be played
    sf::Music music;
    if (!music.openFromFile("canary.wav"))
        return EXIT_FAILURE;

    music.play();

    // A sound for touch events
    sf::SoundBuffer effectBuffer;
    if (!effectBuffer.loadFromFile("dum.ogg"))
        return EXIT_FAILURE;

    sf::Sound effectSound(effectBuffer);

    // Standard main loop
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Touch events work similar to mouse events
                case sf::Event::TouchBegan:
                    // Create a new circle
                    circle c;
                    c.x = event.touch.x;
                    c.y = event.touch.y;
                    c.size = 0;
                    // Store it for later
                    circles.push_back(c);
                    // Play a sound effect
                    effectSound.play();
                    break;
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Iterate over all circles in the vector
        for (std::vector<circle>::iterator a = circles.begin(); a != circles.end(); ++a)
        {
            // Determine the current radius and update the shape
            const float radius = a->size * lineThickness;
            shape.setRadius(radius);
            shape.setPosition(a->x - radius, a->y - radius);
            shape.setOutlineColor(sf::Color(0, 255, 0, 255 - a->size));
            // Draw the shape
            window.draw(shape);
            // Increase this circle's radius
            ++a->size;
        }

        // Look for older circles ready to vanish
        circles.erase(std::remove_if(circles.begin(), circles.end(), removeCheck), circles.end());

        // Display the window contents
        window.display();
    }
}
