#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CloudPoint.h"

#include <memory>
namespace SolAR {
namespace datastructure {

class Keyframe;
/**
 * @class Frame
 * @brief <B>A frame.</B>
 *
 * This class provides frame definition.
 */
class SOLARFRAMEWORK_API Frame {
    ///

public:
    Frame(const SRef<Frame> frame);
	
	Frame(const SRef<Keyframe> keyframe);

    Frame(const std::vector<SRef<Keypoint>> keypoints,
          const SRef<DescriptorBuffer> descriptors,
          const SRef<Image> view,
          const SRef<Keyframe> refKeyframe,
          const Transform3Df pose = Transform3Df::Identity());

    Frame(const std::vector<SRef<Keypoint>> keypoints,
          const SRef<DescriptorBuffer> descriptors,
          const SRef<Image> view,
          const Transform3Df pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

    SRef<Image> getView();

    Transform3Df getPose();

    void setPose(Transform3Df& pose);
    void setKeypoints( std::vector<SRef<Keypoint>>& kpts);
    void setReferenceKeyframe(SRef<Keyframe> keyframe);

    SRef<Keyframe> getReferenceKeyframe();

    SRef<DescriptorBuffer> getDescriptors() const;

    std::vector<SRef<Keypoint>> getKeypoints() const;

	std::map<unsigned int, unsigned int> getVisibleKeypoints();

	void addVisibleKeypoints(const std::map<unsigned int, unsigned int>& kpVisibility);

protected:
    ///@brief pose of current frame
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptors;
    std::vector<SRef<Keypoint>>     m_keypoints ;

	std::map<unsigned int, unsigned int > m_kpVisibility;

};

}
}
#endif // FRAME_H
