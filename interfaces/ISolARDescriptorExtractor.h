#ifndef ISOLARDESCRIPTOREXTRACTOR_H
#define ISOLARDESCRIPTOREXTRACTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "ISolARImage.h"
#include "ISolARKeypoint.h"
#include "ISolARDescriptor.h"


// Definition of ISolARDescriptorExtractor Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

///
/// \brief The SolARDescriptorExtractorType enum
///
	enum class SolARDescriptorExtractorType {
		UNKNOWN_TYPE=-1,
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
/// \brief The ISolARDescriptorExtractor class
///
	class  ISolARDescriptorExtractor : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARDescriptorExtractor() = default;

   ///
   /// \brief ~ISolARDescriptorExtractor
   ///
		virtual ~ISolARDescriptorExtractor() {};

   ///
   /// \brief setType
   /// \param type
   ///
		virtual void setType(SolARDescriptorExtractorType type) = 0;

   ///
   /// \brief getType
   /// \return
   ///
		virtual SolARDescriptorExtractorType  getType() = 0;
		virtual std::string  getTypeString() = 0;

   ///
   /// \brief compute
   /// \param image
   /// \param keypoints
   /// \param descriptors
   ///
		virtual void compute (ISolARImage &image, std::vector< sptrnms::shared_ptr<ISolARKeypoint> > &keypoints,sptrnms::shared_ptr<ISolARDescriptor>& descriptors) = 0;
		XPCF_DECLARE_UUID("c0e49ff1-0696-4fe6-85a8-9b2c1e155d2e");
	};

}  // end of namespace SolAR

#endif // ISOLARDESCRIPTOREXTRACTOR_H
