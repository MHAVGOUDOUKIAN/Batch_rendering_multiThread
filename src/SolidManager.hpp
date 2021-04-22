#ifndef SOLIDMANAGER_HPP_INCLUDED
#define SOLIDMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <tuple>
#include <vector>
#include <functional>
#include <SFML/System.hpp>
#include "Solid.hpp"

class SolidManager
{
    public:
        SolidManager(const int nb_Forme);
        ~SolidManager();

        void add(const float& x, const float& y, const float& taille);
        void add(const sf::Vector2f& pos, const float& taille);
        void update(sf::Time& deltaTime);
        void updatedef(const int& indice_dep, const int& indice_fin);
        void render();
        void renderdef(const int& indice_dep, const int& indice_fin);
        void draw(sf::RenderWindow& target);

        void afficher();

        sf::VertexArray listVertex;
        std::vector<Solid> listSolid;
        unsigned int nbFormeMax;
        float deltaTime;
        int nb_forme=0;

        int compteur;

        sf::Thread t_upgrade1;
        sf::Thread t_upgrade2;
        sf::Thread t_upgrade3;
        sf::Thread t_upgrade4;

        sf::Thread t_render1;
        sf::Thread t_render2;

    private:
};

#endif //SOLIDMANAGER_HPP_INCLUDED