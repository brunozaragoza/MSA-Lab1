#include <nori/bsdf.h>
#include <nori/emitter.h>
#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN
class DepthIntegrator : public Integrator {
public:
  DepthIntegrator(const PropertyList &props) {
    /* No parameters this time */
  }
  Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
             /* Find the surface that is visible in the requested direction */
      Intersection its;
        if (scene->rayIntersect(ray, its)){
        EmitterQueryRecord emitterRecord(its.p);

        const std::vector<Emitter *> lights = scene->getLights();

        const Emitter *em = lights[0];
        Color3f Le = em->sample(emitterRecord, sampler->next2D(), 0.);
        float d= emitterRecord.dist;   
        return (1/d);
        }
        else{
            return 0.;
        }

  }
  std::string toString() const { return "Depth Integrator []"; }
};
NORI_REGISTER_CLASS(DepthIntegrator, "depth");
NORI_NAMESPACE_END