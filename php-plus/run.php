<?php
$php = FFI::load('php.h');

const ZEND_HANDLE_FILENAME = 1;
const ZEND_HANDLE_FP = 2;
const ZEND_HANDLE_STREAM = 3;
const PHP_PLUS_EXTENSION = '.plus';
const OPEN_TAG = '<?php' . PHP_EOL;

// When a file will be opened by the PHP Engine, it checks if the
// function zend_stream_open_function is defined (default is undefined)
// if the function is defined, the engine calls it instead of using the
// default function.
$php->zend_stream_open_function = function($filename, $handle) use ($php) {
    $handle->type = ZEND_HANDLE_STREAM;
    // We are using isatty to be able to read each char of the file and
    // append the open tag if necessary
    $handle->handle->stream->isatty = 1;

    $file = fopen($filename, 'r');
    $filenameLength = strlen($filename);

    // is the file extension .plus?
    $extension = substr($filename, $filenameLength - strlen(PHP_PLUS_EXTENSION), strlen(PHP_PLUS_EXTENSION));
    $isPhpPlus = $extension === PHP_PLUS_EXTENSION;

    $currentChar = 0;

    $handle->handle->stream->reader = function($handle, $buf, $sizeOfBuf) use (&$currentChar, $file, $isPhpPlus) {
        // Appends the open tag at the beginning of the file
        if ($isPhpPlus && $currentChar < strlen(OPEN_TAG)) {
            $char = OPEN_TAG[$currentChar++];
            FFI::memcpy($buf, $char, $sizeOfBuf);
            return true;
        }

        // Reads the file
        if ($char = fread($file, $sizeOfBuf)) {
            FFI::memcpy($buf, $char, $sizeOfBuf);
            return true;
        }

        // EOF
        return false;
    };
};

include 'hello.php';
include 'hello.plus';

// var_dump($php);















