#ifndef ISOLARKEYPOINT_H
#define ISOLARKEYPOINT_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of ISolARKeypoint Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {


///
/// \brief The ISolARKeypoint class
///
	class  ISolARKeypoint : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARKeypoint() = default;

   ///
   /// \brief ~ISolARKeypoint
   ///
		virtual ~ISolARKeypoint() {};
/// \brief This method initializes an ISolARKeypoint object
    /// \param x: x-coordinate of the keypoint
    /// \param y: y-coordinate of the keypoint
    /// \param size: diameter of the meaningful keypoint neighborhood
    /// \param angle: orientation of the keypoint
    /// \param response: the response by which the most strong keypoints have been selected. Can be used for the further sorting or subsampling
    /// \param octave: octave (pyramid layer) from which the keypoint has been extracted
    /// \param class_id: object class (if the keypoints need to be clustered by an object they belong to)
    ///
		virtual void Init(   float  	x,
			float  	y,
			float  	size,
			float  	angle,
			float  	response,
			int  	octave,
			int  	class_id ) = 0;

    ///
    /// \brief This method returns the x-coordinate of an ISolARKeypoint
    /// \return x-coordinate
    ///
		virtual float GetX()=0;

    ///
    /// \brief This method returns the y-coordinate of an ISolARKeypoint
    /// \return y-coordinate
    ///
		virtual float GetY()=0;

    ///
    /// \brief This method returns the angle of an ISolARKeypoint
    /// \return angle
    ///
		virtual float GetAngle()=0;

    ///
    /// \brief This method returns the size of an ISolARKeypoint
    /// \return size
    ///
		virtual float GetSize()=0;

    ///
    /// \brief GetResponse
    /// \return
    ///
		virtual float GetResponse()=0;

    ///
    /// \brief This method returns the octave of an ISolARKeypoint
    /// \return octave
    ///
		virtual int   GetOctave()=0;

    ///
    /// \brief This method returns the classid of an ISolARKeypoint
    /// \return classid
    ///
		virtual int   GetClassId()=0;

		XPCF_DECLARE_UUID("dc891870-dd41-4b9c-ae97-489eb7d03ce2");
	};

}  // end of namespace SolAR

#endif // ISOLARKEYPOINT_H
