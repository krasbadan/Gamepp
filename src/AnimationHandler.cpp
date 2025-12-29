#include <SFML/Graphics.hpp>
 
#include "AnimationHandler.hpp"
 
void AnimationHandler::update(const float dt) {
    if(currentAnim >= this->animations.get_size() || currentAnim < 0) return;
    float duration = this->animations[currentAnim].duration;

    if(int((t + dt) / duration) > int(t / duration)) {
        int frame = int((t + dt) / duration);
        frame %= this->animations[currentAnim].getLength();
 
        sf::IntRect rect = this->frameSize;
        rect.position.x = rect.size.x * frame;
        rect.position.y = rect.size.y * this->currentAnim;
        
        this->bounds = rect;
    }
 
    this->t += dt;
    if(this->t > duration * this->animations[currentAnim].getLength()) this->t = 0.0f;
    
    return;
}


void AnimationHandler::addAnim(const Animation& anim) {
    this->animations.push_back(anim);
    return;
}

void AnimationHandler::changeAnim(unsigned int animID) {
    if(this->currentAnim == animID || animID >= this->animations.get_size() || animID < 0) return;

    this->currentAnim = animID;
    sf::IntRect rect = this->frameSize;
    rect.position.y = rect.size.y * animID;
    this->bounds = rect;
    this->t = 0.0;

    return;
}

int AnimationHandler::count_animations() const {
    return animations.get_size(); // do not miss animations, the scaling would be wrong
}