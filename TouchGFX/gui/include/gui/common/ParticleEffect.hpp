#ifndef PARTICLEEFFECT_HPP
#define PARTICLEEFFECT_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/Application.hpp>
#include <BitmapDatabase.hpp>

class Particle : public touchgfx::Image
{
public:
    void init(int cx, int cy, int counter, bool fadeEnabled, touchgfx::BitmapId bmp);
    void update();
    bool done(int maxX, int maxY);

    // Make sure that we do not JSMOC split
    virtual touchgfx::Rect getSolidRect() const
    {
        return touchgfx::Rect();
    }

    float dvdt;
    float vx;
    float vy;
    float x;
    float y;
    float alpha;
    float dalpha;
};

class ParticleEffect : public touchgfx::Widget
{
public:
    ParticleEffect();
    virtual ~ParticleEffect();

    virtual touchgfx::Rect getSolidRect() const;
    virtual void draw(const touchgfx::Rect& invalidatedArea) const;

    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);
    virtual void handleDragEvent(const touchgfx::DragEvent& evt);

    virtual void handleTickEvent();

    void setNumberOfParticles(int particles);
    void setCenter(int x, int y);
    void setSnapToOrigin(bool snap);
    void setOrigin(int oX, int oY);
    void spawnNewParticles(bool spawn);
    void setParticleFade(bool fade);

    void setParticleBitmap(touchgfx::BitmapId bmp);
private:
    static const uint16_t MAX_NUMBER_OF_PARTICLES = 100;
    Particle particles[MAX_NUMBER_OF_PARTICLES];

    int numberOfParticles;
    int originX;
    int originY;
    bool snapToOrigin;
    bool spawnActive;
    bool fadeParticles;
    touchgfx::BitmapId endParticleBitmap;

    int cx;
    int cy;
    int counter;
};

#endif
