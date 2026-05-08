#include <iostream>
#include <vector>
using namespace std;

//this is just declaration of function, note that all of them are void, we will change it as we go

class GameObject{ // abstract, base class
    protected:  
    int position;  //prob vector of lib
    public:
    virtual void interact()=0;

    virtual void update()=0;
    virtual void draw()=0;
    virtual ~GameObject();
};

class obstale : public GameObject{
    string obs_type;  //prob vec corrd idk
    //shape  
    //we might have to take templates
    public:
    /*    Obstacle(float x, float y, float w, float h, std::string t)
    {
        position = {x, y};
        type = t;

        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }*/
    void interact() override;  //what happens during collision
    //draw
};

class bike : public GameObject{
    int speed;
    int pos_b;
    public:
    /*    Bike(){
        position = {100.f, 100.f};

        shape.setSize(sf::Vector2f(20.f, 10.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }*/
    void move();  //key=movement
    void speedUp();  //speed+1  (dep on obs)
    //void speedDown();  //speed-1
    void update() override;
    void interact() override;
    //draw
};

class player{
    public:
    string name;
    bike b;
    //need to include bike, ahould we make a struct?
    player(string n){
        name =n;
    }
    void controlBike();  //b.move()
    void update();  //bike.update()
    //draw
};

class Game{
    public:
    //window
    player p;
    vector<obstale*>obs;
    /* Game() : window(sf::VideoMode(800, 600), "Bike Game"), player("Ali")
    {
        window.setFramerateLimit(60);

        obstacles.push_back(Obstacle(300, 200, 100, 80, "rock"));
        obstacles.push_back(Obstacle(500, 400, 120, 60, "car"));
    }
*/
    void startgame();
    void detectCollision();
    void updateGame();  //&
    //draw
};

/*int main()
{
    Game game;
    game.startGame();
    return 0;
}*/