<?php
require_once('canvas.php');

const ROM = 'Super Mario World (U) [!].smc';

const RETRO_ENVIRONMENT_SET_PIXEL_FORMAT = 10;
const RETRO_ENVIRONMENT_GET_VARIABLE = 15;
const RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE = 17;
const RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE = 23;
const RETRO_ENVIRONMENT_GET_LOG_INTERFACE = 27;

const RETRO_DEVICE_ID_JOYPAD_B = 0;
const RETRO_DEVICE_ID_JOYPAD_Y = 1;
const RETRO_DEVICE_ID_JOYPAD_SELECT = 2;
const RETRO_DEVICE_ID_JOYPAD_START = 3;
const RETRO_DEVICE_ID_JOYPAD_UP = 4;
const RETRO_DEVICE_ID_JOYPAD_DOWN = 5;
const RETRO_DEVICE_ID_JOYPAD_LEFT = 6;
const RETRO_DEVICE_ID_JOYPAD_RIGHT = 7;
const RETRO_DEVICE_ID_JOYPAD_A = 8;
const RETRO_DEVICE_ID_JOYPAD_X = 9;
const RETRO_DEVICE_ID_JOYPAD_L = 10;
const RETRO_DEVICE_ID_JOYPAD_R = 11;
const RETRO_DEVICE_ID_JOYPAD_L2 = 12;
const RETRO_DEVICE_ID_JOYPAD_R2 = 13;
const RETRO_DEVICE_ID_JOYPAD_L3 = 14;
const RETRO_DEVICE_ID_JOYPAD_R3 = 15;

const KEYBOARD_MAPPING = [
    RETRO_DEVICE_ID_JOYPAD_RIGHT => 'd',
    RETRO_DEVICE_ID_JOYPAD_LEFT => 'a',
    RETRO_DEVICE_ID_JOYPAD_UP => 'w',
    RETRO_DEVICE_ID_JOYPAD_DOWN => 's',
    RETRO_DEVICE_ID_JOYPAD_A => ',',
    RETRO_DEVICE_ID_JOYPAD_B => '.',
    RETRO_DEVICE_ID_JOYPAD_SELECT => 'n',
    RETRO_DEVICE_ID_JOYPAD_START => 'm'
];

$canvas = new TerminalCanvas();

$snes9x = FFI::load('snes9x_libretro.h');

$gameinfo = $snes9x->new('struct retro_game_info', false);
$gameinfo->path = $snes9x->strdup(ROM);

// Start listening for keypress
exec('stty -icanon -echo');
$keyboard = fopen('php://stdin', 'r');
stream_set_blocking($keyboard, false);
$key = fread($keyboard, 1);

// Set Enviroment callback
$snes9x->retro_set_environment(function($cmd, $data) use ($snes9x) {
    if ($cmd === RETRO_ENVIRONMENT_SET_PIXEL_FORMAT) {
        return true;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_VARIABLE) {
        $argument = $snes9x->cast('struct retro_variable', $data);

        if ($argument->key === 'snes9x_gfx_hires') {
            $argument->value = $snes9x->strdup('disabled');
            $data = FFI::addr($argument);
            return false;
        }

        if ($argument->key === 'snes9x_aspect') {
            $argument->value = $snes9x->strdup('uncorrected');
            $data = FFI::addr($argument);
            return true;
        }

        return false;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE) {
        $argument = $snes9x->cast('bool', $data);
        $data = FFI::addr($argument);
        return false;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE) {
        $argument = $snes9x->cast('struct retro_rumble_interface', $data);
        $argument->set_rumble_state = function($port, $effect, $strength) {
            return;
        };
        $data = FFI::addr($argument);
        return false;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_LOG_INTERFACE) {
        return false;
    }

    return;
});

$snes9x->retro_set_audio_sample(function($a, $b) {
    return;
});

$snes9x->retro_set_audio_sample_batch(function($data, $frames) {
    return;
});

$snes9x->retro_set_input_poll(function () {
    return;
});

$snes9x->retro_set_input_state(function ($port, $device, $index, $id) use (&$key) {
    if ($key === KEYBOARD_MAPPING[$id]) {
        return true;
    }

    return false;
});

$forceWidth = 302;

// Set the video refresh callback, called for rendering each frame
$snes9x->retro_set_video_refresh(function ($data, $width, $height, $pitch) use ($canvas, &$forceWidth) {
    $pixels = FFI::cast('uint16_t[' . ($height * $pitch) . ']', $data);
    $canvas->draw($pixels, $forceWidth, $height + 80);

    return;
});

$snes9x->retro_init();
$snes9x->retro_load_game(FFI::addr($gameinfo));

while (true) {
    $key = fread($keyboard, 1);
    $snes9x->retro_run();
}
