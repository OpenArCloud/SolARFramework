/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "datastructure/Image.h"
#include <vector>
#include <map>

#include "xpcf/core/helpers.h"

#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/filesystem.h>

namespace xpcf  = org::bcom::xpcf;
using namespace org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

/**
 * @class Image::ImageInternal
 * @brief <B>A 2D image buffer.</B>.
 *
 */
class Image::ImageInternal {
public:
    ImageInternal() = default;
    explicit ImageInternal(uint32_t size);
    explicit ImageInternal(void* data, uint32_t size);
    ~ImageInternal() = default;
    void setBufferSize(uint32_t size);
    inline uint32_t getBufferSize() { return m_bufferSize; }
    void setData(void * data, uint32_t size);
    inline void* data() { return m_storageData.data(); }
    inline const void* data() const  { return m_storageData.data(); }

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:
    std::vector<uint8_t> m_storageData;
    uint32_t m_bufferSize = 0;
};

DECLARESERIALIZE(Image::ImageInternal);

Image::ImageInternal::ImageInternal(uint32_t size)
{
    setBufferSize(size);
//    std::cout << "===> Image::ImageInternal::ImageInternal buffer size = " << size << std::endl;
}

Image::ImageInternal::ImageInternal(void* data,uint32_t size)
{
   setData(data,size);
}

void Image::ImageInternal::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
    if (m_bufferSize == 0) { // invalid size
        return;
    }
    m_storageData.reserve(m_bufferSize);
    m_storageData.resize(m_bufferSize);
    //memset(m_storageData.data(),0,m_bufferSize); // Normally not useful
}

void Image::ImageInternal::setData(void * data, uint32_t size)
{
    setBufferSize(size);

    m_storageData.clear();
    m_storageData.insert(m_storageData.begin(), static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + m_bufferSize);
}

template<typename Archive>
void Image::ImageInternal::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
    ar & m_storageData;
    ar & m_bufferSize;

//    std::cout << "===> Image::ImageInternal::serialize m_storageData.size() = " << m_storageData.size() << std::endl;
//    std::cout << "===> Image::ImageInternal::serialize m_bufferSize = " << m_bufferSize << std::endl;
}

IMPLEMENTSERIALIZE(Image::ImageInternal);

static std::map<Image::ImageLayout,uint32_t> layoutChannelMapInfos = {{Image::ImageLayout::LAYOUT_RGB,3},
                                                                           {Image::ImageLayout::LAYOUT_GRB,3},
                                                                           {Image::ImageLayout::LAYOUT_BGR,3},
                                                                           {Image::ImageLayout::LAYOUT_GREY,1},
                                                                           {Image::ImageLayout::LAYOUT_RGBA,4},
                                                                           {Image::ImageLayout::LAYOUT_RGBX,4}};

static std::map<Image::DataType,uint32_t> typeSizeMapInfos = {{Image::DataType::TYPE_8U,8},
                                                                      {Image::DataType::TYPE_16U,16},
                                                                      {Image::DataType::TYPE_32U,32},
                                                                      {Image::DataType::TYPE_64U,64}};
//Add stride notion
// Hypothese : pas de bits per component : only full format image YUV444, RGB888, RGB 555 but not YUV420, RGB565 and so on or YUV422 with splatting

uint32_t Image::computeImageBufferSize()
{
    return m_size.width * m_size.height * m_nbChannels * (m_nbBitsPerComponent/8);
}

Image::Image(enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):m_layout(imgLayout),m_pixOrder(pixOrder),m_type(type),m_internalImpl(new ImageInternal())
{
    m_nbChannels = layoutChannelMapInfos.at(m_layout);
    m_nbBitsPerComponent = typeSizeMapInfos.at(m_type);
    m_nbPlanes = 1;
    if (m_pixOrder == PixelOrder::PER_CHANNEL) {
        m_nbPlanes = m_nbChannels;
    }
}

Image::Image(uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):Image(imgLayout,pixOrder,type)
{
    setSize(width,height);
}

// initialize image from external pointer data.
// note : data is copied to take full ownership and ensure deallocation will occur in the same scope allocation was made

Image::Image(void* imageData, uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):Image(width, height, imgLayout, pixOrder,type)
{
    m_internalImpl->setData(imageData,computeImageBufferSize());
}

SRef<Image> Image::copy() const
{
    // NB : maybe we should consider redefining the image copy constructor
    return xpcf::utils::make_shared<Image>(m_internalImpl->data(), m_size.width, m_size.height, m_layout, m_pixOrder, m_type);
}

// reserve new space depending on the image layers and bitspercomponent infos
// TODO handle bad size error : add return code
void Image::setSize(uint32_t width, uint32_t height)
{
    m_size.width = width;
    m_size.height = height;
    m_internalImpl->setBufferSize(computeImageBufferSize());
}

// reserve new space depending on the image layers and bitspercomponent infos
// TODO handle bad size error : add return code
void Image::setSize(Sizei size)
{
    m_size = size;
    m_internalImpl->setBufferSize(computeImageBufferSize());
}


uint32_t Image::getBufferSize()
{
    return m_internalImpl->getBufferSize();
}


void* Image::data()
{
    return m_internalImpl->data();
}


const void* Image::data() const
{
    return m_internalImpl->data();
}

void Image::setImageEncoding(enum ImageEncoding encoding)
{
    m_imageEncoding = encoding;
}

void Image::setImageEncodingQuality(uint8_t encodingQuality)
{
    if (encodingQuality <= 100) {
        m_imageEncodingQuality = encodingQuality;
    }
	else
	{
		std::cout << "Warning: Image encoding quality cannot be more than 100 for JPEG. Set to 70 by default.";
		m_imageEncodingQuality = 70;
	}
}

static std::map<Image::DataType,OIIO::TypeDesc> SolAR2OIIOType = {{Image::DataType::TYPE_8U, OIIO::TypeDesc::UINT8},
                                                                  {Image::DataType::TYPE_16U, OIIO::TypeDesc::INT16},
                                                                  {Image::DataType::TYPE_32U, OIIO::TypeDesc::FLOAT},
                                                                  {Image::DataType::TYPE_64U, OIIO::TypeDesc::DOUBLE}};

static std::map<OIIO::TypeDesc,Image::DataType> OIIO2SolAR2Type = {{OIIO::TypeDesc::UINT8, Image::DataType::TYPE_8U},
                                                             {OIIO::TypeDesc::INT8, Image::DataType::TYPE_8U},
                                                             {OIIO::TypeDesc::UINT16, Image::DataType::TYPE_16U},
                                                             {OIIO::TypeDesc::INT16, Image::DataType::TYPE_16U},
                                                             {OIIO::TypeDesc::UINT32, Image::DataType::TYPE_32U},
                                                             {OIIO::TypeDesc::INT32, Image::DataType::TYPE_32U},
                                                             {OIIO::TypeDesc::UINT64, Image::DataType::TYPE_64U},
                                                             {OIIO::TypeDesc::INT64, Image::DataType::TYPE_64U},
                                                             {OIIO::TypeDesc::FLOAT, Image::DataType::TYPE_32U},
                                                             {OIIO::TypeDesc::DOUBLE, Image::DataType::TYPE_64U}};

static std::map<std::vector<std::string>,Image::ImageLayout> OIIO2SolARLayout = {{{"R","G","B"}, Image::ImageLayout::LAYOUT_RGB},
                                                                                 {{"G","R","B"}, Image::ImageLayout::LAYOUT_GRB},
                                                                                 {{"B","G","R"}, Image::ImageLayout::LAYOUT_BGR},
                                                                                 {{"G","R","B"}, Image::ImageLayout::LAYOUT_GREY},
                                                                                 {{"R","G","B","A"}, Image::ImageLayout::LAYOUT_RGBA}};
//static std::map<Image::ImageLayout,std::initializer_list<std::string>> SolAR2OIIOLayout = {{Image::ImageLayout::LAYOUT_RGB, {"R","G","B"}},
static std::map<Image::ImageLayout,std::vector<std::string>> SolAR2OIIOLayout = {{Image::ImageLayout::LAYOUT_RGB, {"R","G","B"}},
                                                                                           {Image::ImageLayout::LAYOUT_GRB, {"G","R","B"}},
                                                                                           {Image::ImageLayout::LAYOUT_BGR, {"B","G","R"}},
                                                                                           {Image::ImageLayout::LAYOUT_GREY, {"G","R","B"}},
                                                                                           {Image::ImageLayout::LAYOUT_RGBA, {"R","G","B","A"}},
                                                                                           {Image::ImageLayout::LAYOUT_RGBX, {"R","G","B","A"}}};

template<class Archive>
void Image::save(Archive & ar, const unsigned int version) const
{
    ar & m_size;
    ar & m_layout;
    ar & m_pixOrder;
    ar & m_type;
    ar & m_nbChannels;
    ar & m_nbPlanes;
    ar & m_nbBitsPerComponent;

    ar & m_imageEncoding;

    if ((m_imageEncoding == ENCODING_JPEG) || (m_imageEncoding == ENCODING_PNG)) {

        // ImageSpec describing the image we want to write.
        OIIO::ImageSpec spec;
        if (SolAR2OIIOType.find(m_type) != SolAR2OIIOType.end())
            spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels);
        else
            spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels, SolAR2OIIOType.at(m_type));

        if (SolAR2OIIOLayout.find(m_layout) != SolAR2OIIOLayout.end())
            spec.channelnames = SolAR2OIIOLayout.at(m_layout);

        std::vector<unsigned char> file_buffer;  // bytes will go here
        OIIO::Filesystem::IOVecOutput encodingBuffer (file_buffer);  // I/O proxy object;

        std::string filename;
        switch (m_imageEncoding)
        {
            case ENCODING_JPEG:
                filename="out.jpeg";
                std::cout << "JPEG compression quality : " << std::to_string(m_imageEncodingQuality);
                spec.attribute ("Compression","jpeg:" + std::to_string(m_imageEncodingQuality));
                break;
            case ENCODING_PNG:
                filename = "out.png";
                if (m_imageEncodingQuality==0)
                    spec.attribute ("png:compressionLevel", 0);
                else if (m_imageEncodingQuality>=100)
                    spec.attribute ("png:compressionLevel", 9);
                else
                {
                    // PNG encoding quality should be defined between 0 and 9.
                    spec.attribute ("png:compressionLevel", (int)floor(m_imageEncodingQuality/10.0f));
                }
                break;
            default:
                filename = "out";
        }

        auto out = OIIO::ImageOutput::create (filename, &encodingBuffer);
        std::cout << "ImageOutput::create : " << OIIO::geterror() << std::endl;

        if (!out->supports("ioproxy"))
        {
            std::cout << "Decoding image to a buffer based on OIIO::ioporxy is not supported for this image format. Save image in raw format.)";
            ar & m_internalImpl;
            return;
        }
        out->open (filename, spec);
        if (!out->write_image (SolAR2OIIOType[m_type], m_internalImpl->data()))
        {
            std::cout << "Error while writing the " << filename << " image to the serialization buffer. " << std::endl << OIIO::geterror() << std::endl;
            return;
        }

        ar & file_buffer;

        //LOG_DEBUG("===> Original image size = {}", image_size);
        //LOG_DEBUG("===> Encoded image size = {}", file_buffer.size());

        out->close ();
    }
    else {
        ar & m_internalImpl;
    }
}

template<class Archive>
void Image::load(Archive & ar, const unsigned int version)
{
    ar & m_size;
     ar & m_layout;
     ar & m_pixOrder;
     ar & m_type;
     ar & m_nbChannels;
     ar & m_nbPlanes;
     ar & m_nbBitsPerComponent;

     ar & m_imageEncoding;

     if ((m_imageEncoding == ENCODING_JPEG) || (m_imageEncoding == ENCODING_PNG)) {
         // JPEG or PNG decoding
         std::vector<unsigned char> decodingBuffer;
         ar & decodingBuffer;

         OIIO::Filesystem::IOMemReader memreader(decodingBuffer.data(), decodingBuffer.size());

         std::string filename;
         switch (m_imageEncoding)
         {
             case ENCODING_JPEG:
                 filename="in.jpg";
                 break;
             case ENCODING_PNG:
                 filename = "in.png";
                 break;
             default:
                 filename="in.jpg";
                 break;
         }

         auto in = OIIO::ImageInput::open (filename, nullptr, &memreader);
         const OIIO::ImageSpec & spec = in->spec();
         m_size.width = spec.width;
         m_size.height = spec.height;
         m_nbChannels = spec.nchannels;

         OIIO::imagesize_t buffersize = spec.image_bytes(true);
         unsigned char* pixels = new unsigned char [buffersize];
         in->read_image(OIIO::TypeDesc::UNKNOWN, pixels);

         switch (spec.nchannels)
         {
             case 1:
                 m_layout = Image::LAYOUT_GREY;
                 m_nbChannels = 1;
                 break;
             case 3:
             case 4:
                 if (OIIO2SolARLayout.find(spec.channelnames) != OIIO2SolARLayout.end())
                     m_layout = OIIO2SolARLayout.at(spec.channelnames);
                 else
                    std::cout << "Try to decode an image with unsupported channels. Only RGB, GRB, BGR, RGBA and Grey are supported";
                 //LOG_ERROR("Try to decode an image with unsupported channels. Only RGB, GRB, BGR, RGBA and Grey are supported");
                 m_nbChannels = (unsigned int)spec.nchannels;
                 break;
             default:
                std::cout << "Error: Try to decode an image with " << spec.nchannels << " channels. Only 1, 3 or 4 channels are supported";
                //LOG_ERROR("Try to decode an image with {} channels. Only 1, 3 or 4 channels are supported", spec.nchannels);

         }

         //LOG_DEBUG("===> Encoded image size = {}", decodingBuffer.size());
         //LOG_DEBUG("===> Decoded image size = {}", buffersize);

         m_internalImpl = utils::make_shared<Image::ImageInternal>();
         m_internalImpl->setData(pixels, spec.image_bytes(true));
         in->close();
     }
     else {
         ar & m_internalImpl;
     }
}

IMPLEMENTSERIALIZE(Image);
//image creation from opencv conversion ... : howto handle memory allocation locality : factory ?
// conversion from/to opencv for instance : how to handle the T* type while bound to void* ?
}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Image)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image)
BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Image::ImageInternal)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image::ImageInternal)
BOOST_CLASS_TYPE_INFO(
SolAR::datastructure::Image::ImageInternal,
boost::serialization::extended_type_info_typeid<SolAR::datastructure::Image::ImageInternal>
)
