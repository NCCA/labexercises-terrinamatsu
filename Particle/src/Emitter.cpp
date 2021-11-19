#include "Emitter.h"
#include <iostream>
#include "Random.h"

Emitter::Emitter(size_t _numParticles)
{
    Particle p;
    for(size_t i = 0; i < _numParticles; ++i)
    {
        p.dir = m_emitDir * Random::randomPositiveFloat() + Random::randomVectorOnSphere() * m_spread;
        p.dir.y = std::abs(p.dir.y);
        
        m_particles.push_back(p);
    }
}

void Emitter::update()
{

}

void Emitter::render() const
{
    for(auto p : m_particles)
    {
        std::cout<<p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z<<' ';
        std::cout<<p.dir.x<<' '<<p.dir.y<<' '<<p.dir.z<<'\n';
    }
}

size_t Emitter::numParticles() const
{
    return m_particles.size();
}
