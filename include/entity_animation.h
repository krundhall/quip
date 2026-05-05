#pragma once
#include "enums.h"

struct AnimationState
{
    EntityAnimation current_animation;
    int current_frame;
    float frame_timer;
    bool flip_horizontal;
};

void entity_animate(AnimationState &anim, float dt);
void entity_begin_death(AnimationState &anim);
