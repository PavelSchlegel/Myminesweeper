#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Ob_Button
{
public:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    Ob_Button()
    {
        if ( ! m_texture.loadFromFile("../../GPG/PlayField.jpg", sf::IntRect(320, 0, 32, 32))) {
            std::cout << "Error-Image was not open!" << std::endl;
        }
        else {
            m_sprite.setTexture(m_texture);
        }
    }

    sf::Sprite& get_sprite() {
        return m_sprite;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(880, 640), "My window");
    sf::Clock clock;

    //sf::Texture ButtonTexture;
    int w = 32;
    Ob_Button freeButton;
    

    //sf::Sprite ButtonSprite(ButtonTexture);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        //ButtonSprite.setTextureRect(sf::IntRect(320, 0, 32, 32));
        freeButton.get_sprite().setPosition(32, 32);
        window.draw(freeButton.get_sprite());

        window.display();
    }
    return 0;
}