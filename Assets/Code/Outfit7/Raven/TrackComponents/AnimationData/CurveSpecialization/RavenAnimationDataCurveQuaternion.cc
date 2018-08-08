#ifdef STARLITE
#include "RavenAnimationDataCurveQuaternion.h"
#include "RavenAnimationDataCurveQuaternion.cs"

namespace Starlite {
    namespace Raven {
        RavenAnimationDataCurveQuaternion::RavenAnimationDataCurveQuaternion() {
        }

        Quaternion RavenAnimationDataCurveQuaternion::EvaluateAtTime(double time, double duration) {
            float normalizedTime = (float)GetNormalizedTime(GetCurrentTime(time, duration), duration, m_EaseType);
            Quaternion v;
            if (m_UniformCurves) {
                auto curve = m_Curves[0].GetObject();
                for (int i = 0; i < c_ValueCount; ++i) {
                    v.vector.data[i] = curve->Evaluate(normalizedTime);
                }
            } else {
                for (int i = 0; i < c_ValueCount; ++i) {
                    v.vector.data[i] = m_Curves[i]->Evaluate(normalizedTime);
                }
            }
            return v;
        }

        void RavenAnimationDataCurveQuaternion::SetStartingValues(const Quaternion& values) {
            m_Curves = Array<Ref<AnimationCurve>>(c_ValueCount);
            for (int i = 0; i < c_ValueCount; ++i) {
                m_Curves[i] = Object::New<AnimationCurve>();
                m_Curves[i]->AddKeyframe(AnimationCurve::Keyframe(0, values.vector.data[i]));
                m_Curves[i]->AddKeyframe(AnimationCurve::Keyframe(1, values.vector.data[i]));
            }
        }

        void RavenAnimationDataCurveQuaternion::SyncStartingValues(const Quaternion& values) {
            for (int i = 0; i < c_ValueCount; ++i) {
                auto& curve = m_Curves[i];
                auto& key = curve->GetKeyframes()[0];
                key.value = values.vector.data[i];
            }
        }

        void RavenAnimationDataCurveQuaternion::CopyValuesCallback(const RavenAnimationDataComponentBase* other) {
            auto otherReal = static_cast<const RavenAnimationDataCurveQuaternion*>(other);

            m_UniformCurves = otherReal->m_UniformCurves;
        }
    } // namespace Raven
} // namespace Starlite
#endif