#include "../header/obstacle.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace sf;

Obstacle::Obstacle(int lane, float startY, const string& imagepath)  //lane tells x pos, each child passes own imagePath(.png)
        : laneNum(lane), texture(), sprite(texture)
        {

    position = {266.f + (lane * 133.f), startY};
    
    if (!texture.loadFromFile(imagepath)) { //if the immage isnt working; we use a placeholder
        cout << "Warning: could not load " << imagepath << "\n";
        isUsingPlaceholder = true;
        placeholder.setSize({50.f, 50.f});
        placeholder.setOrigin({25.f, 25.f});
        placeholder.setPosition(position);
        placeholder.setFillColor(Color::Magenta);
    } else{
        sprite.setTexture(texture,true);  //calls setTexture explicitly
        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin({bounds.size.x/ 2.0f, bounds.size.y / 2.0f});  //fixing the center of sprite, same as the bike logic
        sprite.setPosition(position);
    }
}

//called every frame by gameEngine
//gameSpeed comes from Game — increases over time so game gets harder
void Obstacle::update(float movementAmount) {
    position.y += movementAmount;  //big y so screen moves down, obs goes
    sprite.setPosition(position);  //sync what you see to the logic position
    if(isUsingPlaceholder) { placeholder.setPosition(position);}
}

void Obstacle::draw(RenderWindow& window) {
    if(isUsingPlaceholder) window.draw(placeholder);
    else  window.draw(sprite);
}

FloatRect Obstacle::getBounds() const {  //gives area, uses by gameEngine for collision
    if(isUsingPlaceholder)
    return placeholder.getGlobalBounds();
    else
    return sprite.getGlobalBounds();
}

float Obstacle::getY() const {  //gameEngine calls this when need to cleanObstacle; so our screen is 600, if y>650 delete obs
    return position.y;
}