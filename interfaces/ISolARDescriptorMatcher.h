#ifndef ISOLARDESCRIPTORMATCHER_H
#define ISOLARDESCRIPTORMATCHER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "ISolARDescriptor.h"

// Definition of ISolARDescriptorMatcher Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

	namespace DescriptorMatcher {

    ///
    /// \brief The DescriptorMatcher return codes
    ///
		enum  RetCode {
          DESCRIPTORS_MATCHER_OK=0,     /**< the default OK code*/
           DESCRIPTORS_DONT_MATCH,      /**< try to match descriptors of different types*/
           DESCRIPTOR_TYPE_UNDEFINED,   /**< one of the descriptor sets is is unknown*/
           DESCRIPTOR_EMPTY             /**< One set is empty*/
		};

    ///
    /// \brief The DescriptorMatcher Match element
    ///
		struct Match{
            int idx1;               /**< the index of the match in the first set of descriptors*/
            int idx2;               /**< the index of the match in the second set of descriptors*/
            float distance;         /**< the distance betwenn the two descriptors*/
		};
    }    // end of namespace DescriptorMatcher

///
/// \brief The ISolARDescriptorMatcher class
///
    class  ISolARDescriptorMatcher : public virtual org::bcom::xpcf::IComponentIntrospect {
    public:
    	ISolARDescriptorMatcher() = default;

   ///
   /// \brief ~ISolARDescriptorMatcher
   ///
    	virtual ~ISolARDescriptorMatcher() {};
       ///
       /// \brief Match function
       /// returns one match per element of the first descriptor set
       ///
    	virtual DescriptorMatcher::RetCode match(
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors1,       /**< first set of descriptors*/
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors2,       /**< second set of descriptors to match against the first set*/
               std::vector<DescriptorMatcher::Match>& matches        /**< one dimensional set of matches */
    		)=0;


       ///
       /// \brief Match function
       /// returns several matches per element of the first descriptor set
       ///
    	virtual DescriptorMatcher::RetCode match(
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors1,                      /**< first set of descriptors*/
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors2,                      /**< second set of descriptors to match against the first set*/
               std::vector<std::vector<DescriptorMatcher::Match>>& matches,         /**< two dimensional set of matches */
               int nbOfMatches                                                      /**< number of matches per element of the first set of descriptors*/
    		)=0;



    	XPCF_DECLARE_UUID("dda38a40-c50a-4e7d-8433-0f04c7c98518");
    };

}  // end of namespace SolAR

#endif // ISOLARDESCRIPTORMATCHER_H
