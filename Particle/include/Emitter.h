#ifndef EMITTER_H_
#define EMITTER_H_

#include <vector>
#include "Particle.h"

class Emitter
{
    public:
        Emitter() = default;
        Emitter(size_t _numParticles);

        void update();
        void render() const;

        size_t numParticles() const;
    private:
        std::vector<Particle> m_particles;
        Vec3 m_emitDir = {0.0f, 1.0f, 0.0f};
        float m_spread = 1.5f;
};

#endif