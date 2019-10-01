char *strdup(const char *s);

struct __sFile 
{
    int unused;
};
   
typedef struct __sFILE FILE;

typedef uint64_t zend_ulong;

typedef size_t (*zend_stream_fsizer_t)(void* handle);
typedef ssize_t (*zend_stream_reader_t)(void* handle, char *buf, size_t len);
typedef void   (*zend_stream_closer_t)(void* handle);

typedef struct _zend_stream {
    void        *handle;
    int         isatty;
    zend_stream_reader_t   reader;
    zend_stream_fsizer_t   fsizer;
    zend_stream_closer_t   closer;
} zend_stream;

typedef struct _zend_refcounted_h {
    uint32_t         refcount;          /* reference counter 32-bit */
    union {
        uint32_t type_info;
    } u;
} zend_refcounted_h;

struct _zend_string {
    zend_refcounted_h gc;
    zend_ulong        h;                /* hash value */
    size_t            len;
    char              val[1];
};

typedef struct _zend_string zend_string;

typedef enum {
    ZEND_HANDLE_FILENAME,
    ZEND_HANDLE_FP,
    ZEND_HANDLE_STREAM
} zend_stream_type;

typedef unsigned char zend_bool;

typedef struct _zend_file_handle {
    union {
        FILE          *fp;
        zend_stream   stream;
    } handle;
    const char        *filename;
    zend_string       *opened_path;
    zend_stream_type  type;
    /* free_filename is used by wincache */
    /* TODO: Clean up filename vs opened_path mess */
    zend_bool         free_filename;
    char              *buf;
    size_t            len;
} zend_file_handle;

typedef int (*zend_stream_open_function_func_t)(const char *filename, zend_file_handle *handle);
typedef void (*php_var_dump_func_t)(void *struc, int level);

extern zend_stream_open_function_func_t zend_stream_open_function;
extern php_var_dump_func_t php_var_dump;
