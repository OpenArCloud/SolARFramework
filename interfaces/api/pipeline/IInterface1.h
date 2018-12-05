/**
 * @copyright Copyright (c) 2019 B-com http://www.b-com.com/
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

#ifndef SOLAR_IPIPELINE_H
#define SOLAR_IPIPELINE_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

namespace SolAR {
	namespace api {
		namespace pipeline {

			///
			/// \brief The IInterface1 class
			///
			class IIPipeline : public virtual org::bcom::xpcf::IComponentIntrospect {
			public:
			    virtual ~IIPipeline() = default;
			    ///
			    /// \brief pipeline interface
			    ///
			    virtual FrameworkReturnCode init(int var) = 0;
			    virtual FrameworkReturnCode start(SRef<Image> inPutImage,Transform3Df& pose) = 0;
			    virtual FrameworkReturnCode stop(int var) = 0;
			};
		}
	}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IIPipeline,
                             "ef4baacc-5906-4c9c-a8db-48ba3a403e40",
                             "IPipeline",
                             "Pipeline interface");

#endif // SOLAR_IPIPELINE_H
