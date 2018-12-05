#ifndef ISOLARDESCRIPTOR_H
#define ISOLARDESCRIPTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <string>

// Definition of ISolARDescriptor Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {


///
/// \brief SolARDescriptorType enum
///        Specifies what format is allowed for the descriptors
///


	enum  SolARDescriptorType {
    SOLAR_DESCRIPTOR_UNDEFINED=-1,   /**< the format is undefined */
    SOLAR_DESCRIPTOR_8U,             /**< unsigned char */
    SOLAR_DESCRIPTOR_8S,             /**< char */
    SOLAR_DESCRIPTOR_16U,            /**< unsigned short */
    SOLAR_DESCRIPTOR_16S,            /**< short */
    SOLAR_DESCRIPTOR_32S,            /**< 32-bit int */
    SOLAR_DESCRIPTOR_32F,            /**< 32-bit float */
    SOLAR_DESCRIPTOR_64F,            /**< 64-bit float */
	};

///
/// \brief The ISolARDescriptor class
///
	class  ISolARDescriptor : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARDescriptor() = default;

   ///
   /// \brief ~ISolARDescriptor
   ///
		virtual ~ISolARDescriptor() {};

	///
	/// \brief Loads an openCV set of descriptors and convert it to an SolAR set of descriptors
	///
	/// \param descriptor_src  A void pointer to the openCV descriptors set resource
	///
		virtual void LoadCVDescriptor(void* descriptor_src)=0;

	///
	/// \brief Returns a pointer to the descriptors
	/// \return A void-casted pointer to the internal resource
	///
		virtual void* GetDescriptorPtr()=0;

	///
	/// \brief Returns the type (format) of the extracted descriptors
	/// \return An SolARDescriptorType value
	///
		virtual SolARDescriptorType GetType()=0;

	///
	/// \brief  The descriptors are stored as a matrix rows x cols where rows are the number of parameters considered and cols is the dimension of the parameters
	/// \return The value for rows
	///
		virtual int GetRows()=0;

	///
	/// \brief  The descriptors are stored as a matrix rows x cols where rows are the number of parameters considered and cols is the dimension of the parameters
	/// \return The value for cols
	///
		virtual int GetCols()=0;

	///
	/// \brief  The descriptors are stored as a matrix rows x cols where rows are the number of parameters considered and cols is the dimension of the parameters
	///
	/// \param r the number of parameters
	/// \return
	///
		virtual void SetRows(int r)=0;

	///
	/// \brief  The descriptors are stored as a matrix rows x cols where rows are the number of parameters considered and cols is the dimension of the parameters
	///
	/// \param c the dimension of each parameter
	/// \return
	///
		virtual void SetCols(int c)=0;


		XPCF_DECLARE_UUID("422925e0-5f41-4ad9-b9e1-a93e73411358");
	};

}  // end of namespace SolAR

#endif // ISOLARDESCRIPTOR_H