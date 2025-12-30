#include "AnimationHandler.hpp"

#include <SFML/Graphics.hpp>



void AnimationHandler::update(const float dt) {
    if(currentAnim >= this->animations.get_size() || currentAnim < 0) return;
    float frame_duration = this->animations[currentAnim].frame_duration;

    if(int((t + dt) / frame_duration) > int(t / frame_duration)) {
        int frame = int((t + dt) / frame_duration);
        frame %= this->animations[currentAnim].getLength();
 
        sf::IntRect rect = this->frameSize;
        rect.position.x = rect.size.x * frame;
        rect.position.y = rect.size.y * this->currentAnim;
        
        this->bounds = rect;
    }
 
    this->t += dt; anim_duration -= dt;
    if (this->t > frame_duration * this->animations[currentAnim].getLength()) this->t = 0.0f;
    if (anim_duration < 0) anim_duration = 0;
    
    return;
}


void AnimationHandler::addAnim(const Animation& anim) {
    this->animations.push_back(anim);
    return;
}

void AnimationHandler::playAnim(unsigned animID) {
    if(anim_duration != 0) return;
    changeAnim(animID);
    anim_duration = animations[currentAnim].getDuration();
    return;
}

void AnimationHandler::breakAnim() {
    anim_duration = 0;
    return;
}

void AnimationHandler::changeAnim(unsigned int animID) {
    if(anim_duration != 0) return;
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