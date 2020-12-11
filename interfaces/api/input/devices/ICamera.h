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

#ifndef SOLAR_ICAMERA_H
#define SOLAR_ICAMERA_H

#include "api/input/devices/IDevice.h"
#include "datastructure/Image.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "api/input/devices/IDevice.h"

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/**
 * @class ICamera
 * @brief <B>Grabs images captured in real-time by a video camera.</B>
 * <TT>UUID: 5ddc7df0-8377-437f-9c81-3643f7676a5b</TT>
 *
 * This class describes the interface of a camera capture device.
 */
class ICamera : virtual public IDevice {
public:
    /// @brief Specify the ICamera constructor class
    ICamera() = default;

    /// @brief Specify the ICamera destructor class
    virtual ~ICamera() = default;

    /// @brief Fill the SRef img buffer with a new image captured by the camera device.
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextImage(SRef<datastructure::Image> & img) = 0;
        
    /// @brief Set the acquisition device image resolution
    virtual void setResolution(const datastructure::Sizei & resolution) = 0;

    /// @brief Set the intrinsic camera parameters
    virtual void setIntrinsicParameters(const datastructure::CamCalibration & intrinsic_parameters) =0;
    
    /// @brief Set the distortion intrinsic camera parameters
    virtual void setDistortionParameters(const datastructure::CamDistortion & distortion_parameters) =0;

    /// @brief Set the distortion and intrinsic camera parameters
    virtual void setParameters(const datastructure::CameraParameters & parameters) =0;

    /// @brief Get the acquisition device image resolution
    virtual datastructure::Sizei getResolution() = 0;

    /// @return Return the intrinsic camera parameters
    virtual const datastructure::CamCalibration & getIntrinsicsParameters() = 0;

    /// @return Return the camera parameters
    virtual const datastructure::CameraParameters & getParameters() = 0;
    
    /// @return Return the distortion camera lens parameters
    virtual const datastructure::CamDistortion & getDistortionParameters() = 0;

    //virtual params getCameraIntrinsics() = 0;
    //Frame : image + timestamp image + depth + timestamp depth ...

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::ICamera,
                             "5ddc7df0-8377-437f-9c81-3643f7676a5b",
                             "ICamera",
                             "SolAR::ICamera interface");

#endif // SOLAR_ICAMERA_H

