#ifdef TRIANGLEKDTREE_DLL
    #define TRIANGLEKDTREE_API __declspec(dllexport)
#else
    #define TRIANGLEKDTREE_API __declspec(dllimport)
#endif