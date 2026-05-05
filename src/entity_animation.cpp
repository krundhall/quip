#include "entity_animation.h"

void entity_animate(AnimationState &anim, float dt)
{
    anim.frame_timer += dt;

    if (anim.frame_timer >= 0.1f)
    {
        anim.frame_timer = 0.0f;
        anim.current_frame++;
    }
}
