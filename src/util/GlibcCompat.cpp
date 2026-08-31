#include <cstdlib>

// Compatibility shim for environments where code references __isoc23_strtol
// but the runtime libc does not provide this symbol.
extern "C" long __isoc23_strtol(const char *nptr, char **endptr, int base) { return std::strtol(nptr, endptr, base); }
