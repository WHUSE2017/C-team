#ifndef __P_DEBUG_
#define __P_DEBUG_

#define _DEBUG_ 1

#if _DEBUG_
#define p_debug(...) printf(__VA_ARGS__)
#define ENTER p_debug("%s  %s\n",__FILE__, __LINE__);
#else
#define p_debug(...) 
#define ENTER
#endif

#endif