#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <cstdio>

sf::Clock clk; // starts the clock
char str[250]; // Text

int main(int argc, char **argv)
{
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -20.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 50.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.10f, 0.10f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 1.0f;
    body->CreateFixture(&fixtureDef);

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(10, 10));
    shape.setFillColor(sf::Color::Yellow);
    shape.setScale(2,2);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf"))
        return EXIT_FAILURE;

    sf::Time old = clk.getElapsedTime();
    sf::Time now = old;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Run physics step every 1/60 sec.
        /// @IMPORTANT Physics requires constant time difference
        now = clk.getElapsedTime();
        if((now - old).asSeconds() >= 1.0 / 60.0) {
            old = now;

            // Make physics step
            world.Step(timeStep, velocityIterations, positionIterations);
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();
            sprintf(str, "Time: %4.2f\nX: %4.2f\nY: %4.2f\nAngle: %4.2f\n", now.asSeconds(), position.x, position.y, angle);
            shape.setPosition(300+5*position.x, 300+5*position.y);
            shape.setRotation(angle);

            // Draw the string
            sf::Text text(str, font, 10);
            window.clear();
            window.draw(shape);
            window.draw(text);
            window.display();
        }
    }

    return 0;
}