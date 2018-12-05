#ifndef SOLARMESSAGES_H
#define SOLARMESSAGES_H

namespace SolAR {

enum class FrameworkReturnCode:long{
  _SUCCESS=0, /** Successfull operation */

  // error codes
    _ERROR_=-1,               /** unknown error, better stop!! */

  // for ISolARImage
    _ERROR_LOAD_IMAGE=-10,    /** Cannot load Image */
    _ERROR_ACCESS_IMAGE=-11,  /** Cannot acces Image */
};

}  // end of namespace Argo

#endif // SOLARMESSAGES_H
