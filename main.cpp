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

    void buttonOne() {
        m_sprite.setTextureRect(sf::IntRect(282, 0, 32, 32));
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(880, 640), "My window");
    sf::Clock clock;

    int w = 32;
    Ob_Button freeButton;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear(sf::Color::White);
        freeButton.get_sprite().setPosition(/*x*/32, /*y*/32);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (event.mouseButton.x >= freeButton.get_sprite().getPosition().x) {
                    if (event.mouseButton.x <= freeButton.get_sprite().getPosition().x + w) {
                        if (event.mouseButton.y >= freeButton.get_sprite().getPosition().x) {
                            if (event.mouseButton.y <= freeButton.get_sprite().getPosition().x + w) {
                                freeButton.buttonOne();
                            }
                        }
                    }
                }
            }
        }
        
        window.draw(freeButton.get_sprite());

        window.display();
    }
    return 0;
}