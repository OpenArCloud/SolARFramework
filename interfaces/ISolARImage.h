#ifndef ISOLARIMAGE_H
#define ISOLARIMAGE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "SolARMessages.h"
#include <string>

// Definition of ISolARImage Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {


//defines pixels type, 8bit, 16bit
#define SolAR_IMAGE_TYPE_8 1

///
/// \enum Colorspace
/// \brief Definition of SolAR colorspace type
///
	enum ColorSpace { RGB_709, Linear,GREY };

///
/// \brief Definition of SolAR Image Data types
/// \enum ImageDepth
///
	enum ImageDepth {
    IMAGE_DEPTH_8U=0,           /**< unsigned char */
    IMAGE_DEPTH_8S,             /**< char */
    IMAGE_DEPTH_16U,            /**< unsigned short */
    IMAGE_DEPTH_16S,            /**< short */
    IMAGE_DEPTH_32S,            /**< 32-bit int */
    IMAGE_DEPTH_32F,            /**< 32-bit float */
    IMAGE_DEPTH_64F,            /**< 64-bit float */
		IMAGE_DEPTH_UNDEFINED
	};

///
/// \brief Definition of SolAR Image types
/// \enum ColorModel
///
	enum ColorModel {
    COLOR_MODEL_RGB=0,          /**< means 3 channels per pixel : Red, Green, Blue */
    COLOR_MODEL_GRB,            /**< means 3 channels per pixel : Green,Red, Blue (this is opencv model)*/
    COLOR_MODEL_GREY,           /**< means 1 channel per pixel  : grey color*/
    COLOR_MODEL_RGBX,           /**< means 4 channels per pixel : Red, Green, Blue and transparency */
		COLOR_MODEL_UNDIFINED
	};


///
/// \brief The ISolARImage class
///
	class  ISolARImage : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARImage() = default;

   ///
   /// \brief ~ISolARImage
   ///
		virtual ~ISolARImage() {};
    ///
    ///
    /// \brief Image Loading method, from an image file
    /// \param filename: full path to an image file
    ///
		virtual FrameworkReturnCode loadImage(const std::string & filename)=0;

    ///
    /// \brief Image Loading method, from an image loaded in memory
    /// \param ptr_res: pointer to a memory address containing image pixels
    /// \param type: image type
    /// \param w: width of the image
    /// \param h: height of the image
    /// \param pixel_format: colorspace of image pixels
    ///
		virtual FrameworkReturnCode loadImage(unsigned char* ptr_res, const unsigned int w, const unsigned int h, const ImageDepth depth, const ColorModel model)=0;

    ///
    /// \brief Image create method, from volatile data
    /// \param ptr_res: pointer to a memory address containing image pixels that is not resilient
    /// \param type: image type
    /// \param w: width of the image
    /// \param h: height of the image
    /// \param pixel_format: colorspace of image pixels
    ///
		virtual FrameworkReturnCode createImage(unsigned char* ptr_res, const unsigned int w, const unsigned int h,const  ImageDepth depth, const ColorModel model)=0;

    ///
    /// \brief Image Loading method, from an other ISolARImage object
    /// \param value: ISolARImage object
    ///
		virtual FrameworkReturnCode loadImage(const ISolARImage &value)=0;

    ///
    /// \brief Simple method to display current ISolARImage in a window
    ///
		virtual FrameworkReturnCode simpleDisplay()=0;

    ///
    /// \brief the following methods do not return error codes for efficiency purpose
    ///
    ///

    ///
    /// \brief method to access width of current ISolARImage
    /// \return width
    /// \0 means empty or non initialised image
    ///
		virtual unsigned int getWidth()=0;

    ///
    /// \brief method to access height of current ISolARImage
    /// \return height
    /// \0 means empty or non initialised image
    ///
		virtual  unsigned int getHeight()=0;

    ///
    /// \brief method to access depth of current ISolARImage
    /// \return Image depth
    /// \SolAR::ImageDepth::IMAGE_DEPTH_UNDEFINED means empty or non initialised image
    ///
		virtual   SolAR::ImageDepth getImageDepth()=0;

    ///
    /// \brief method to access the color model of current ISolARImage
    /// \return ColorModel
    /// \SolAR::ColorMode::COLOR_MODEL_UNDIFINED means empty or non initialised image
    ///
		virtual   SolAR::ColorModel getColorModel()=0;

    ///
    /// \brief method to access memory address of ISolARImage's pixels
    /// \return pointer to ISolARImage's pixels
    /// \0 or Null means empty or non initialised image
    ///
		virtual unsigned char* getImagePtr()=0;

		XPCF_DECLARE_UUID("b5f31065-af42-4976-bde8-2769243dffc5");
	};

}  // end of namespace SolAR

#endif // ISOLARIMAGE_H
