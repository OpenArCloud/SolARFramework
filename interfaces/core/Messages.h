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

#ifndef SOLAR_MESSAGES_H
#define SOLAR_MESSAGES_H

namespace SolAR {

enum class FrameworkReturnCode:long{

    /** means stop the process */
    _STOP = 1,
    /** Successfull operation */
    _SUCCESS = 0,

    // error codes
    /** unknown error, better stop!! */
    _ERROR_ = -1,

    // Not implemented interface
    _NOT_IMPLEMENTED = -2,

    // for IImage
    /** Cannot load Image */
    _ERROR_LOAD_IMAGE = -10,
    /** Cannot acces Image */
    _ERROR_ACCESS_IMAGE = -11,

    // for services
    /** Service is busy */
    _BUSY = -20,
    /** No service registered (Service Manager) */
    _NO_SERVICE_REGISTERED = -21,
    /** No service available (Service Manager) */
    _NO_SERVICE_AVAILABLE = -22,
    /** Service not locked by a client (Service Manager) */
    _NO_SERVICE_LOCKED = -23,

    // for client sessions
    _UNKNOWN_MAP_UUID = -30,
    _UNKNOWN_CLIENT_UUID = -31,
    _REQUEST_SERVICE_FAILURE = -32,
    _INIT_SERVICE_FAILURE = -33,
    _SERVICE_NOT_INITIALIZED = -34,
    _CAMERA_PARAMETERS_NOT_SET = -35,
    _SERVICE_NOT_STARTED = -36,

    // for license management
    _LICENSE_SERVER_UNKNOWN_ERROR = -40,
    _LICENSE_SERVER_NOT_REACHABLE = -41,
    _LICENSE_NOT_VALID = -42,
    _LICENSE_UNAVAILABLE_PARAMETER = -43,
    _LICENSE_INCORRECT_SERVICE_VERSION = -44,
    _LICENSE_MAX_CLIENTS_MAPPING_EXCEEDED = -45,
    _LICENSE_MAX_CLIENTS_RELOC_EXCEEDED = -46,
    _LICENSE_MAX_CLIENTS_STEREO_MAPPING_EXCEEDED = -47,
    _LICENSE_MAX_CLIENTS_DENSE_MAPPING_EXCEEDED = -48

};

}  // end of namespace SolAR

#endif // SOLAR_MESSAGES_H
