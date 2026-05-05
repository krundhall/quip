#pragma once

enum class EntityAnimation
{
    IDLE,
    RUNNING,
    HIT,
    DEATH
};

struct AnimationState
{
    EntityAnimation current_animation;
    int current_frame;
    float frame_timer;
    bool flip_horizontal;
};

void entity_animate(AnimationState &anim, float dt);
