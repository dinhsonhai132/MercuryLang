#ifndef MERCURY_GARBAGE_COLLECTOR_HEADER_FILE
#define MERCURY_GARBAGE_COLLECTOR_HEADER_FILE

#include <vector>

#define __release(o) if (--(o)->ref_count == 0) delete (o)
#define __retain(o) (o)->ref_count++;

#define MerGC_release(object) if (object) __release(object)
#define MerGC_retain(object) if (object) __retain(object)

#endif // MERCURY_GARBAGE_COLLECTOR_HEADER_FILE