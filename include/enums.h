#pragma once

/* GameState */
enum class GAMESTATE
{
    MAINMENU,
    PLAYING,
    GAMEOVER
};

/* Entity */
enum class FACING
{
    LEFT,
    RIGHT
};

enum class EntityAnimation
{
    IDLE,
    RUNNING,
    HIT,
    DEATH
};

enum class ENEMYTYPE
{
    GOBLIN
};

enum class SPELLTYPE
{
    FIREBALL,
    TELEPORT
};


enum class CLASSTYPE
{
    MAGE
};


/* Spell */

enum class SPELLTAG
{
    FIRE,
    ARCANE
};
