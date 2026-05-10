#include "../header/obstacle.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace sf;

Obstacle::Obstacle(int lane, float startY, const string& imagepath)  //lane tells x pos, each child passes own imagePath(.png)
        : laneNum(lane), texture(), sprite(texture){

    position = {200.f + (lane * 200.f), startY};  //x position, same as bike; 0lane->200, 1lane->400, 2lane-600

    if (!texture.loadFromFile(filesystem::path(imagepath))) { //if the immage isnt working; we use a placeholder
        cout << "Warning: could not load " << imagepath << ", using placeholder\n";
        isUsingPlaceholder = true;
        placeholder.setSize({50.f, 50.f});  //square
        placeholder.setOrigin({25.f, 25.f});  //center origin
        placeholder.setPosition(position);  
        placeholder.setFillColor(Color::Magenta);  //shocking colour so we know something is off
    }

    sprite.setTexture(texture);  //else do the normal immage

    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.0f);  //fixing the center of sprite, same as the bike logic
    sprite.setPosition(position);
}

//called every frame by gameEngine
//gameSpeed comes from Game — increases over time so game gets harder
void Obstacle::update(float gameSpeed) {
    position.y += gameSpeed;  //big y so screen moves down, obs goes
    sprite.setPosition(position);  //sync what you see to the logic position
    if(isUsingPlaceholder)  placeholder.setPosition(position);
}

void Obstacle::draw(RenderWindow& window) {
    if(isUsingPlaceholder) window.draw(placeholder);
    else  window.draw(sprite);
}

FloatRect Obstacle::getBounds() const {  //gives area, uses by gameEngine for collision
    return sprite.getGlobalBounds();
}

float Obstacle::getY() const {  //gameEngine calls this when need to cleanObstacle; so our screen is 600, if y>650 delete obs
    return position.y;
}