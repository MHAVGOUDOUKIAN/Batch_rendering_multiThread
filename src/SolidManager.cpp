#include "SolidManager.hpp"
#include <iostream>

sf::Mutex mutex;

SolidManager::SolidManager(const int nb_Forme) : 
    listVertex(sf::Quads, 4),
    nbFormeMax(nb_Forme),
    t_upgrade1(std::bind(&SolidManager::updatedef, this, 0, nbFormeMax/2)),
    t_upgrade2(std::bind(&SolidManager::updatedef, this, 1*nbFormeMax/2, 2*(nbFormeMax/2))),
    t_upgrade3(std::bind(&SolidManager::updatedef, this, 2*(nbFormeMax/4), 3*(nbFormeMax/4))),
    t_upgrade4(std::bind(&SolidManager::updatedef, this, 3*(nbFormeMax/4), 4*(nbFormeMax/4))),
    t_render1(std::bind(&SolidManager::renderdef, this, 0, nbFormeMax/2)),
    t_render2(std::bind(&SolidManager::renderdef, this, 1*nbFormeMax/2, 2*(nbFormeMax/2)))
{
    listVertex.resize(nb_Forme*4);
    listSolid.reserve(nb_Forme);
    for(int i=0; i < nb_Forme; ++i)
    {
        listSolid.emplace_back(0,0,0,i,true);

        listVertex[listSolid[i].indiceVertex*4].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+1].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+2].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+3].color = listSolid[i].m_color;
    }
}

void SolidManager::add(const float& x, const float& y, const float& taille)
{

    unsigned int i=0;
    while(i < nbFormeMax-1 && !listSolid[i].dead)
    {
        i++;
    }

    if(listSolid[i].dead) // ON en remplace un
    {
        Solid& s = listSolid[i];
        //listSolid.erase(listSolid.begin()+i);
        //listSolid.emplace_back(pos.x,pos.y, taille, i );
        s.pos.x = x;
        s.pos.y = y;
        s.taille = taille;
        s.dead = false;
        s.m_color = sf::Color(randomi(0,255),randomi(0,255),randomi(0,255));
        s.vit.x = randomf(-500,500);
        s.vit.y = randomf(-500,500);
        s.posInit = sf::Vector2f(x, y);
        s.vitInit = sf::Vector2f(s.vit.x, s.vit.y);
        s.timeElapsedJump = 0;
        s.masse=10;
    } 

    ++nb_forme;
}

void SolidManager::add(const sf::Vector2f& pos, const float& taille)
{
    unsigned int i=0;
    while(i < nbFormeMax-1 && !listSolid[i].dead)
    {
        i++;
    }

    if(listSolid[i].dead) // ON en remplace un
    {
        Solid& s = listSolid[i];
        //listSolid.erase(listSolid.begin()+i);
        //listSolid.emplace_back(pos.x,pos.y, taille, i );
        s.pos.x = pos.x;
        s.pos.y = pos.y;
        s.taille = taille;
        s.dead = false;
        s.m_color = sf::Color(randomi(0,255),randomi(0,255),randomi(0,255));
        s.vit.x = randomf(-500,500);
        s.vit.y = randomf(-500,500);
        s.posInit = sf::Vector2f(pos.x, pos.y);
        s.vitInit = sf::Vector2f(s.vit.x, s.vit.y);
        s.timeElapsedJump = 0;
        s.masse=10;
    }

    ++nb_forme;
}

void SolidManager::update(sf::Time& deltaTime)
{
    this->deltaTime = deltaTime.asSeconds();  
    compteur =0;

    t_upgrade1.launch();
    t_upgrade2.launch();
    //t_upgrade3.launch();
    //t_upgrade4.launch();

    while(compteur < 2) {}
}

void SolidManager::updatedef(const int& indice_dep, const int& indice_fin)
{
    for(int i=indice_dep; i < indice_fin ; ++i)
    {
        if(!listSolid[i].dead) listSolid[i].update(this->deltaTime);
    }

    mutex.lock();
        
        compteur++;

    mutex.unlock();
}

void SolidManager::render()
{
    compteur =0;

    t_render1.launch();
    t_render2.launch();

    while(compteur < 2) {}
}

void SolidManager::renderdef(const int& indice_dep, const int& indice_fin)
{
    for(int i=indice_dep; i < indice_fin; ++i) {
        unsigned int indice = listSolid[i].indiceVertex;
        if(!listSolid[i].dead) {
            float x =listSolid[i].pos.x;
            float y =listSolid[i].pos.y;
            float taille = listSolid[i].taille;

            listVertex[indice*4].position = sf::Vector2f(x+taille, y-taille);
            listVertex[indice*4+1].position = sf::Vector2f(x+taille, y+taille);
            listVertex[indice*4+2].position = sf::Vector2f(x-taille, y+taille);
            listVertex[indice*4+3].position = sf::Vector2f(x-taille, y-taille);

            /*listVertex[listSolid[i].indiceVertex*4].position = sf::Vector2f(listSolid[i].pos.x+listSolid[i].taille, listSolid[i].pos.y-listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+1].position = sf::Vector2f(listSolid[i].pos.x+listSolid[i].taille, listSolid[i].pos.y+listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+2].position = sf::Vector2f(listSolid[i].pos.x-listSolid[i].taille, listSolid[i].pos.y+listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+3].position = sf::Vector2f(listSolid[i].pos.x-listSolid[i].taille, listSolid[i].pos.y-listSolid[i].taille);
            */
        }
        else {
            listVertex[indice*4].position = sf::Vector2f(0,0);
            listVertex[indice*4+1].position = sf::Vector2f(0,0);
            listVertex[indice*4+2].position = sf::Vector2f(0,0);
            listVertex[indice*4+3].position = sf::Vector2f(0,0);
        }
    }

    mutex.lock();
        
        compteur++;

    mutex.unlock();
}

void SolidManager::draw(sf::RenderWindow& target)
{
    render();
    target.draw(listVertex);
}

void SolidManager::afficher()
{   
    system("clear");
    for(unsigned int i=0; i < nbFormeMax; ++i)
    {   
        std::cout << "Correspondance tablVertex: " << listSolid[i].indiceVertex << std::endl;
        std::cout << listSolid[i].pos.x << " / " << listSolid[i].pos.y << std::endl;
        std::cout << listSolid[i].dead << std::endl;
    }
}

SolidManager::~SolidManager() {}