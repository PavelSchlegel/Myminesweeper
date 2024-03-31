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
    sf::RenderWindow window ( sf::VideoMode ( 320, 320 ), "My window" );
    // window.setVerticalSyncEnabled(true);
    window .setFramerateLimit ( 30 );
    sf::Clock clock;

    bool ButtonRight = false;

    std::size_t w = 32;

    int count  = 0;
    Ob_Button field [ 12 ] [ 12 ];
    for ( std::size_t i = 1; i < 11; ++i ) {
        for ( std::size_t j = 1; j < 11; ++j ) {
            try {
                field [ i ] [ j ] .m_sprite .setPosition ( static_cast < float > ( ( i - 1 ) * w ), static_cast < float > ( ( j - 1 ) * w ) );
                count++;
                std::cout << count << std::endl;
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

    for ( std::size_t i = 1; i <= 10; ++i ) {
        for ( std::size_t j = 1; j <= 10; ++j ) {
            try {
                if ( field [ i ] [ j ] .m_fieldValue  == 9 ) {
                    continue;
                }

                int n = 0;
                if ( field [ i + 1 ] [ j ] .m_fieldValue ==  9 ) n++;
                if ( field [ i ] [ j + 1 ] .m_fieldValue ==  9 ) n++;
                if ( field [ i - 1 ] [ j ] .m_fieldValue ==  9 ) n++;
                if ( field [ i ] [ j - 1 ] .m_fieldValue  == 9 ) n++;
                if ( field [ i + 1 ] [ j + 1 ] .m_fieldValue == 9) n++;
                if ( field [ i - 1 ] [ j - 1 ] .m_fieldValue == 9) n++;
                if ( field [ i - 1 ] [ j + 1 ] .m_fieldValue == 9) n++;
                if ( field [ i + 1 ] [ j - 1 ] .m_fieldValue == 9) n++;
                field [ i ] [ j ] .m_fieldValue = n;
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
                if ( ( event.mouseButton.x / w ) < 12 && ( event.mouseButton.y / w ) < 12 ) {
                    if ( ! field [ ( event.mouseButton.x / w ) + 1] [ ( event.mouseButton.y / w ) + 1 ] .is_open ) {
                        field [ ( event.mouseButton.x / w ) + 1] [ ( event.mouseButton.y / w ) + 1 ] .buttonOpen ();
                    }
                }
                std::cout << " Mouse left_button " << std::endl;
            }

            if ( event.key.code == sf::Mouse::Right ) {
                std::cout << " Mouse right_button " << std::endl;
                ButtonRight = true;
            }
        }

        for ( std::size_t i = 1; i < 11; ++i ) {
            for ( std::size_t j = 1; j < 11; ++j ) {
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
                    if ( ( event.mouseButton.x / w ) < 12 && ( event.mouseButton.y / w ) < 12 ) {
                        field [ ( event.mouseButton.x / w ) + 1 ] [ ( event.mouseButton.y / w ) + 1 ] .buttonFlag ();
                        ButtonRight = false;
                    }
                }
            }
        }

        window .display ();
    }
    return 0;
}