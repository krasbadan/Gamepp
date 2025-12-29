#pragma once
 
#include <SFML/Graphics.hpp>
#include "sequence.hpp"
 
class Animation {
public:
    unsigned int startFrame;
    unsigned int endFrame;
    float duration;

    Animation(unsigned int _startFrame, unsigned int _endFrame, float _duration) : startFrame(_startFrame), endFrame(_endFrame), duration(_duration) {}

    unsigned int getLength() { return endFrame - startFrame + 1; }
};

class AnimationHandler {
private:
    Sequence<Animation> animations;
    float t;
    int currentAnim;

public:
    void addAnim(const Animation& anim);
    void update(const float dt);
    void changeAnim(unsigned int animNum); 
    int count_animations() const;
    sf::IntRect bounds;
    sf::IntRect frameSize;

    AnimationHandler() : t(0), currentAnim(-1) {}
    AnimationHandler(const sf::IntRect& _frameSize) : t(0), currentAnim(-1), frameSize(_frameSize) {}
};
