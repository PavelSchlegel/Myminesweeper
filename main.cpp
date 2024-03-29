#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Ob_Button
{
public:

    bool m_flag;
    bool is_open;
    uint8_t m_fieldValue;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    Ob_Button () :
    m_flag ( false ),
    is_open ( false ),
    m_fieldValue ( 0 )

    {
        if ( ! m_texture .loadFromFile ( "../../GPG/PlayField.jpg" ) ) {
            std::cout << "Error-Image was not open!" << std::endl;
        }
        else {
            m_sprite .setTexture ( m_texture );
            m_sprite .setTextureRect ( sf::IntRect ( 320, 0, 32, 32) );
        }
    }

    explicit Ob_Button ( uint8_t value, float x, float y ) :
    m_flag ( false ),
    is_open ( false ),
    m_fieldValue ( value )

    {
        if ( ! m_texture .loadFromFile ( "../../GPG/PlayField.jpg" ) ) {
            std::cout << "Error-Image was not open!" << std::endl;
        }
        else {
            m_sprite .setTexture ( m_texture );
            m_sprite .setTextureRect ( sf::IntRect ( 320, 0, 32, 32 ) );
            m_sprite .setPosition ( x, y ) ;
        }
    }

    void set_value ( uint8_t value ) {

        if ( value < 10 ) {
            m_fieldValue = value;
        }
    }

    void buttonOpen () {
        if ( ! m_flag ) {
            if ( ! is_open ) {
                is_open = true;
                m_sprite .setTextureRect ( sf::IntRect ( m_fieldValue * 32, 0, 32, 32 ) );
            }
        }
    }

    void buttonFlag () {
        if ( ! is_open ) {
            if ( ! m_flag ) {
                m_flag = true;
                m_sprite .setTextureRect ( sf::IntRect ( 352, 0, 32, 32 ) );
                return;
            }
            m_flag = false;
            m_sprite .setTextureRect ( sf::IntRect ( 320, 0, 32, 32 ) );
        }
    }
};

int main()
{
    sf::RenderWindow window ( sf::VideoMode ( 880, 640 ), "My window" );
    // window.setVerticalSyncEnabled(true);
    window .setFramerateLimit ( 30 );
    sf::Clock clock;

    bool ButtonRight = false;

    std::size_t w = 32;

    Ob_Button field [ 10 ] [ 10 ];
    for ( std::size_t i = 0; i < 10; ++i ) {
        for ( std::size_t j = 0; j < 10; ++j ) {
            try {
                field [ i ] [ j ] .m_sprite .setPosition ( static_cast < float > ( i * w ), static_cast < float > ( j * w ) );
                // difficulty level ???
                if ( rand () % 5 == 0 ) {
                    field [ i ] [ j ] .set_value ( 9 );
                }
			    else {
                    field [ i ] [ j ] .set_value ( 0 );
                }
            }
            catch (...) {
                std::cout << "Try/catch-error!" << std::endl;
            }
        }
    }

    while ( window .isOpen () )
    {
        sf::Event event;
        while ( window .pollEvent ( event ) )
        {   
            if ( event.type == sf::Event::Closed ){
                window .close ();
            }
        }

        window .clear( sf::Color::White );

        if ( event.type == sf::Event::MouseButtonPressed ) {
            std::cout << " Mouse active " << std::endl;
            if ( event.key.code == sf::Mouse::Left ) {
                if ( ( event.mouseButton.x / w ) < 10 && ( event.mouseButton.y / w ) < 10 ) {
                    if ( ! field [ event.mouseButton.x / w ] [ event.mouseButton.y / w ] .is_open ) {
                        field [ event.mouseButton.x / w ] [ event.mouseButton.y / w ] .buttonOpen ();
                    }
                }
                std::cout << " Mouse left_button " << std::endl;
            }

            if ( event.key.code == sf::Mouse::Right ) {
                std::cout << " Mouse right_button " << std::endl;
                ButtonRight = true;
            }
        }

        for ( std::size_t i = 0; i < 10; ++i ) {
            for ( std::size_t j = 0; j < 10; ++j ) {
                try {
                    window .draw ( field [ i ] [ j ] .m_sprite );
                }
                catch (...) {
                    std::cout << "Try/catch-error!" << std::endl;
                }
            }
        }

        if ( ButtonRight ) {
            if ( event.type == sf::Event::MouseButtonReleased ) {
                std::cout << " Mouse right_release " << std::endl;
                if ( event.key.code == sf::Mouse::Right/* sf::Mouse::isButtonPressed(sf::Mouse::Button::Right )*/ ) {
                    if ( ( event.mouseButton.x / w ) < 10 && ( event.mouseButton.y / w ) < 10 ) {
                        field [ event.mouseButton.x / w ] [ event.mouseButton.y / w ] .buttonFlag ();
                        ButtonRight = false;
                    }
                }
            }
        }

        window .display ();
    }
    return 0;
}