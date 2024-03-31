#ifndef SWEEPER
#define SWEEPER

namespace sweeper {
    class Sweeper {
        public:
            std::size_t X;
            std::size_t Y;
            sf::Texture m_texture;
            std::size_t minen_count;

            explicit Sweeper ( std::size_t X, std::size_t Y ) :
            X ( X ) ,
            Y ( Y ) {
                /* zwei Gelegenheiten :
                    - bis 100 Felder ( X * Y ) -> arbeiten mit Stack
                    - über -> bieten Platz vom System
                */
                if ( ! m_texture .loadFromFile ( "../../GPG/PlayField.jpg" ) ) {
                    std::cout << "Error-Image was not open!( ../../GPG/PlayField.jpg )" << std::endl;
                }
                else {
                    // m_sprite .setTexture ( m_texture );
                    // m_sprite .setTextureRect ( sf::IntRect ( 320, 0, 32, 32) );
                }
            }
    }
} // namespace sweeper
#endif // SWEEPER