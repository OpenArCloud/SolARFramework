#ifndef ISOLARKEYPOINTDETECTOR_H
#define ISOLARKEYPOINTDETECTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "SolARMessages.h"
#include <memory>
#include <vector>

#include "ISolARImage.h"
#include "ISolARKeypoint.h"

// Definition of ISolARKeypointDetector Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

///
/// \brief SolARKeypointDetectorType enum
/// This enum is used to define the type of an ISolARKeypointDetector object
///
	enum class SolARKeypointDetectorType {
		SURF,
		ORB,
		SIFT,
		DAISY,
		LATCH,
		AKAZE,
		AKAZEUP,
		BRISK,
		BRIEF,
	};


///
/// \brief The ISolARKeypointDetector class
///
	class  ISolARKeypointDetector : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARKeypointDetector() = default;

   ///
   /// \brief ~ISolARKeypointDetector
   ///
		virtual ~ISolARKeypointDetector() {};
    ///
    /// \brief This method is used to define the type on an ISolARKeypointDetector object
    /// \param type: type of ISolARKeypointDetector
    ///
		virtual void setType(SolARKeypointDetectorType type) = 0;

    ///
    /// \brief This method returns the type of the current ISolARKeypointDetector object
    /// \return type of ISolARKeypointDetector
    ///
		virtual SolARKeypointDetectorType  getType() = 0;

    ///
    /// \brief This method detects keypoints in an input ISolARImage
    /// \param image: input ISolARImage object
    /// \param keypoints: output vector of ISolARKeypoint objects
    ///
        virtual void detect (ISolARImage &image, std::vector< sptrnms::shared_ptr<ISolARKeypoint> > &keypoints) = 0;

    ///
    /// \brief This method outputs an ISolARImage object from an input ISolARImage and an input vector of ISolARKeypoint objects
    /// \param imageIn: input ISolARImage
    /// \param keypoints: input vector of ISolARKeypoint objects
    /// \param imageOut: output ISolARImage
    ///
		virtual void drawKeypoints(ISolARImage& imageIn,std::vector<sptrnms::shared_ptr<ISolARKeypoint>>& keypoints,ISolARImage& imageOut)=0;

		XPCF_DECLARE_UUID("0eadc8b7-1265-434c-a4c6-6da8a028e06e");
	};

}  // end of namespace SolAR

#endif // ISOLARKEYPOINTDETECTOR_H
