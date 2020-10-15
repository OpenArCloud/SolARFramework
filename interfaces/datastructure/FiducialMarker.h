/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#ifndef FIDUCIALMARKER_H
#define FIDUCIALMARKER_H

#include "core/SolARFrameworkDefinitions.h"
#include <core/SerializationDefinitions.h>
#include <datastructure/SquaredBinaryPattern.h>
#include <datastructure/Trackable2D.h>

// Definition of FiducialMarker Class //
// part of SolAR namespace //

using namespace SolAR::datastructure;

namespace SolAR {
namespace datastructure {

/**
    * @class FiducialMarker
    * @brief <B>This class defines a fiducial marker datastructure.</B>
    */
class SOLARFRAMEWORK_API FiducialMarker : virtual public Trackable2D {
    public:
        ///
        /// @brief FiducialMarker default constructor
        ///
        FiducialMarker() = default;

        ///
        /// @brief FiducialMarker constructor
        /// with binary pattern and size of fiducial image
        /// @param binaryPattern: binary pattern of the fiducial marker
        /// @param size: size (width and height) of the fiducial marker image
        ///
        FiducialMarker(SquaredBinaryPattern & binaryPattern, Sizef & size);

        // Class methods

        ///
        /// @brief Returns the type of the Trackable object
        /// i.e. the class name
        ///
        std::string getTrackableType() override;

        /// @brief Sets the binary pattern of the fiducial marker
        /// @param[in] binaryPattern: the binary pattern of the fiducial marker object
        void setPattern(const SquaredBinaryPattern & binaryPattern);

        /// @brief Returns the pattern of the fiducial marker
        /// @result SquaredBinaryPattern: the binary pattern of the fiducial marker object
        SquaredBinaryPattern getPattern();

    private:
        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    private:
        SquaredBinaryPattern m_pattern; // Binary pattern of the fiducial marker
};

DECLARESERIALIZE(FiducialMarker);

}
} // end of namespace SolAR

#endif // FIDUCIALMARKER_H
