#pragma once
 
#include <SFML/Graphics.hpp>

#include "sequence.hpp"


 
struct Animation {
    unsigned int startFrame;
    unsigned int endFrame;
    float frame_duration;

    Animation(unsigned int _startFrame, unsigned int _endFrame, float _frame_duration):
        startFrame(_startFrame), endFrame(_endFrame), frame_duration(_frame_duration)
    {}

    unsigned int getLength() { return endFrame - startFrame + 1; }
    float getDuration() { return getLength() * frame_duration; }
};

class AnimationHandler {
private:
    Sequence<Animation> animations;
    float t;
    int currentAnim;
    float anim_duration = 0;

public:
    float get_anim_duration() {return anim_duration;}
    void addAnim(const Animation& anim);
    void update(const float dt);
    void playAnim(unsigned animID);
    void breakAnim();
    void changeAnim(unsigned animID);
    int count_animations() const;
    sf::IntRect bounds;
    sf::IntRect frameSize;

    AnimationHandler() : t(0), currentAnim(-1) {}
    AnimationHandler(const sf::IntRect& _frameSize) : t(0), currentAnim(-1), frameSize(_frameSize) {}
};
