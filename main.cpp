#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Ob_Button
{
public:

    bool m_flag;
    uint8_t m_field;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    Ob_Button(uint8_t value, float x, float y) :
    m_flag(false),
    m_field()

    {
        if ( ! m_texture.loadFromFile("../../GPG/PlayField.jpg"/*, sf::IntRect(320, 0, 32, 32)*/)) {
            std::cout << "Error-Image was not open!" << std::endl;
        }
        else {
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(320, 0, 32, 32));
        }
    }

    sf::Sprite& get_sprite() {
        return m_sprite;
    }

    void buttonOpen() {
        if ( ! m_flag ) {
            m_sprite.setTextureRect(sf::IntRect(m_field * 32, 0, 32, 32));
        }
    }

    void buttonFlag() {
        if ( ! m_flag ) {
            m_sprite.setTextureRect(sf::IntRect(352, 0, 32, 32));
            return;
        }
        m_sprite.setTextureRect(sf::IntRect(320, 0, 32, 32));
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(880, 640), "My window");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    int w = 32;
    // Ob_Button freeButton;
    Ob_Button field[10][10];
    for (std::size_t i = 0; i < 10; ++i) {
        for (std::size_t j = 0; j < 10; ++j) {
            try {
                field[i][j].get_sprite().setPosition(i * w, j * w);
                // window.draw(field[i][j].get_sprite());
            }
            catch (...) {
                std::cout << "Try/catch-error!" << std::endl;
            }
        }
    }

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

        //freeButton.get_sprite().setPosition(/*x*/32, /*y*/32);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // if (event.mouseButton.x >= freeButton.get_sprite().getPosition().x) {
                //     if (event.mouseButton.x <= freeButton.get_sprite().getPosition().x + w) {
                //         if (event.mouseButton.y >= freeButton.get_sprite().getPosition().x) {
                //             if (event.mouseButton.y <= freeButton.get_sprite().getPosition().x + w) {
                //                freeButton.buttonOne();
                //             }
                //         }
                //     }
                // }
                std::cout << event.mouseButton.x / w << " " <<  event.mouseButton.y / w << std::endl;
                if ((event.mouseButton.x / w) < 10) {
                    if ((event.mouseButton.y / w) < 10)
                    field[event.mouseButton.x / w][event.mouseButton.y / w].buttonOpen();
                } else {
                    std::cout << "Mous-field_ERROR!" << std::endl;
                }
            }

            if (event.mouseButton.button == sf::Mouse::Right) {
                std::cout << event.mouseButton.x / w << " " <<  event.mouseButton.y / w << std::endl;
                if ((event.mouseButton.x / w) < 10) {
                    if ((event.mouseButton.y / w) < 10)
                    field[event.mouseButton.x / w][event.mouseButton.y / w].buttonFlag();
                } else {
                    std::cout << "Mous-field_ERROR!" << std::endl;
                }
            }
        }

        for (std::size_t i = 0; i < 10; ++i) {
            for (std::size_t j = 0; j < 10; ++j) {
                try {
                    // field[i][j].get_sprite().setPosition(i * w, j * w);
                    window.draw(field[i][j].get_sprite());
                }
                catch (...) {
                    std::cout << "Try/catch-error!" << std::endl;
                }
            }
        }
        
        //window.draw(freeButton.get_sprite());

        window.display();
    }
    return 0;
}