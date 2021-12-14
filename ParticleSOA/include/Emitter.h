#ifndef EMITTER_H_
#define EMITTER_H_

#include <ngl/Vec3.h>
#include <ngl/SimpleVAO.h>
#include <memory>

class Emitter
{
    public:
        Emitter() = default;
        Emitter(size_t _numParticles, const ngl::Vec3 &_emitDir);

        void update();
        void render() const;
        void saveFrame(int _frameNo) const;

        size_t numParticles() const;
    private:
        void resetParticle(size_t _index);
        //std::vector<Particle> m_particles;
        std::vector<ngl::Vec4> m_posSize;
        std::vector<ngl::Vec3> m_dir;
        std::vector<ngl::Vec3> m_colour;
        std::vector<int> m_maxLife;
        std::vector<int> m_life;

        size_t m_numParticles;

        ngl::Vec3 m_emitDir = {0.0f, 20.0f, 0.0f};
        float m_spread = 1.5f;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif