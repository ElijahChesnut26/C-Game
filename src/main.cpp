#include <SFML/Graphics.hpp>
#include <iostream>

bool intersects(const sf::CircleShape &circle1, const sf::RectangleShape &rectangle);

void movement(sf::CircleShape &circle){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        circle.move({-1, 0});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        circle.move({1, 0});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        circle.move({0, -1});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        circle.move({0, 1});
    }
}

void shoot(sf::CircleShape &circle, sf::RectangleShape &bullet, bool &isMoving, bool &can_shoot){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && can_shoot){
        can_shoot = false;
        sf::Vector2f x = circle.getPosition();
        // std::cout << x.x << std::endl;
        // std::cout << x.y;
        bullet.setPosition(x);
        // break;
        // while(bullet.getPosition().y > 0){
        // bullet.move({0, -1});
        isMoving = true;
        // }
    }

    if (isMoving){
        bullet.move({0, -3});
        if (bullet.getPosition().y < 0){
            isMoving = false;
            bullet.setPosition({-100, -100});
            can_shoot = true;
        }
    }
}

// bool intersects(const sf::CircleShape &circle1, const sf::RectangleShape &rectangle){
//     const sf::Vector2f delta = circle1.getPosition() - rectangle.getPosition();
//     const float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
//     return distance < circle1.getRadius() + rectangle.getRadius();
// }

bool intersects(sf::CircleShape &circle, sf::RectangleShape &rectangle){
    const sf::Vector2f circlePosition = circle.getPosition();
    const sf::Vector2f rectanglePosition = rectangle.getPosition();
    const sf::Vector2f circleHalfSize = {circle.getRadius(), circle.getRadius()};
    const sf::Vector2f rectangleHalfSize = {rectangle.getSize().x / 2, rectangle.getSize().y / 2};

    const sf::Vector2f delta = {circlePosition.x - rectanglePosition.x, circlePosition.y - rectanglePosition.y};

    const sf::Vector2f intersection = {std::abs(delta.x) - (circleHalfSize.x + rectangleHalfSize.x), std::abs(delta.y) - (circleHalfSize.y + rectangleHalfSize.y)};

    return (intersection.x < 0) && (intersection.y < 0);
}

bool intersects(sf::RectangleShape &rect, sf::RectangleShape &bullet){
    const sf::Vector2f rectPosition = rect.getPosition();
    const sf::Vector2f bulletPosition = bullet.getPosition();
    const sf::Vector2f rectHalfSize = {rect.getSize().x / 2, rect.getSize().y / 2};
    const sf::Vector2f bulletHalfSize = {bullet.getSize().x / 2, bullet.getSize().y / 2};

    const sf::Vector2f delta = {bulletPosition.x - rectPosition.x, bulletPosition.y - rectPosition.y};

    const sf::Vector2f intersection = {std::abs(delta.x) - (bulletHalfSize.x + rectHalfSize.x), std::abs(delta.y) - (bulletHalfSize.y + rectHalfSize.y)};

    return (intersection.x < 0) && (intersection.y < 0);
}

void play(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangle){
    window.draw(circle);
        // window.draw(circle2);
        window.draw(rectangle);
        movement(circle);
        // shoot(circle, window);
        if (intersects(circle, rectangle)){
            std::cout << "Intersects" << std::endl;
        }else{
            std::cout << "Not Intersects" << std::endl;
        }

}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1000u, 750u}), "CMake SFML Project");
    window.setFramerateLimit(120);

    sf::CircleShape circle(25);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin({25, 25});

    // sf::CircleShape circle2(25);
    // circle2.setFillColor(sf::Color::Red);
    // circle2.setPosition({100, 100});

    sf::RectangleShape rectangle({50, 50});
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition({100, 100});

    sf::RectangleShape bullet(sf::Vector2f(10, 20));
    bullet.setFillColor(sf::Color::Red);
    bullet.setPosition({-100, -100});
    bullet.setOrigin({5, 10});

    sf::Image icon;
    icon.loadFromFile("/Users/elichesnut/Documents/GitHub/C-Game/icon.png");
    
    bool isMoving = false;
    bool can_shoot = true;
    bool if_killed = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.setIcon(icon);
        
        if (!if_killed){
            window.draw(rectangle);
        }
        // window.draw(rectangle);
        window.draw(bullet);
        window.draw(circle);

        movement(circle);
        shoot(circle, bullet, isMoving, can_shoot);

        if (intersects(circle, bullet)){
            std::cout << "Intersects" << std::endl;
            if_killed = true;
            bullet.setPosition({-100, -100});
            can_shoot = true;
        }else{
            std::cout << "Not Intersects" << std::endl;
        }

        if (intersects(circle, rectangle)){
            std::cout << "Intersects" << std::endl;
        }else{
            std::cout << "Not Intersects" << std::endl;
        }
        // fall(circle);
        window.display();
    }
}
