<?php
// create FFI object, loading libc and exporting function printf()
$ffi = FFI::cdef("
    int printf(const char *format, ...);
    int atoi(const char *str);
");
// call C printf()
$ffi->printf("Hello %s!\n", "world");
var_dump($ffi->atoi('21'));
