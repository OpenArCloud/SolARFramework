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

#ifndef SOLAR_I2DOVERLAY_H
#define SOLAR_I2DOVERLAY_H

#include "datastructure/MathDefinitions.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace display {

/**
 * @class I2DOverlay
 * @brief Drawing interface to overlay 2D information on top of an image.
 *
 * This class provides drawing methods to overlay 2D debug informations on top of an image.
 */

class I2DOverlay : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I2DOverlay default constructor
    I2DOverlay() = default;

    /// @brief I2DOverlay default destructor
    virtual ~I2DOverlay() = default;

     /// @brief Draw one Circle.
    /// Draw a circle on the image displayImage center on the point with specified radius and thickness.
    /// @param[in] point The position of the circle to draw
    /// @param[in,out] displayImage The image on which the the circles will be drawn.
    virtual void drawCircle(const SRef<Point2Df> point, SRef<Image> displayImage) = 0;

    /// @brief Draw Circles.
    /// Draw all the circles stored in the vector std::vector <SRef<Point2Df>> & points on image displayImage with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in] point The positions of the circles to draw
    /// @param[in,out] displayImage The image on which the circles will be drawn.
    virtual void drawCircles(const std::vector<SRef<Point2Df>>& points, SRef<Image> displayImage) = 0;

    /// @brief Draw Circles.
    /// Draw all the circles stored in the vector std::vector <SRef<Keypoint>> & keypoints on image displayImage with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in] keypoint The positions of the circles to draw
    /// @param[in,out] displayImage The image on which the circles will be drawn.
    virtual void drawCircles(const std::vector<SRef<Keypoint>>& keypoints, SRef<Image> displayImage) = 0;

    /// @brief Draw a Contour.
    /// Draw a contour on image displayImage
    /// @param[in] contour The contour in 2D to draw with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in,out] displayImage The image on which the contours will be drawn.
    virtual void drawContour (const Contour2Df& contours, SRef<Image> displayImage) = 0;

    /// @brief Draw Contours.
    /// Draw all the contours stored in the vector  std::vector <SRef<Contour2Df>> & contours on image displayImage
    /// @param[in] contours The vector of contours in 2D to draw with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in,out] displayImage The image on which the contours will be drawn.
    virtual void drawContours (const std::vector <SRef<Contour2Df>> & contours, SRef<Image> displayImage) = 0;

    /// @brief Draw a Squared Binary Pattern.
    /// @param[in] pattern The squared binary pattern to display.
    /// @param[in,out] displayImage The image on which the squared binary pattern will be drawn (on the whole image).
    virtual void drawSBPattern (const SRef<SquaredBinaryPattern> pattern, SRef<Image> displayImage) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I2DOverlay,
                             "62b8b0b5-9344-40e6-a288-e609eb3ff0f1",
                             "I2DOverlay",
                             "SolAR::I2DOverlay interface")

#endif // SOLAR_I2DOVERLAY_H
