<?php
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

const SDL_INIT_VIDEO = 0x00000020;
const SDL_RENDERER_ACCELERATED = 0x00000002;
const SDL_RENDERER_PRESENTVSYNC = 0x00000004;
const SDL_QUIT = 0x100;
const SDL_WINDOW_SHOWN = 0x00000004;

const ZOOM_LEVEL = 2;
// The correct is 224
const SCREEN_HEIGHT = 336;
// The correct is 256
const SCREEN_WIDTH = 302;

$snes9x = FFI::load('snes9x_libretro.h');
$sdl = FFI::load('sdl.h');

// Initializes the SDL
if ($sdl->SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw new Exception('SDL_Init Error: ' . $sdl->SDL_GetError(), 1);
}

// Create the window
$win = $sdl->SDL_CreateWindow('PHP FFI SNES', 0, 0, SCREEN_WIDTH * ZOOM_LEVEL, SCREEN_HEIGHT * ZOOM_LEVEL, SDL_WINDOW_SHOWN);

if ($win == null){
    throw new Exception('SDL_CreateWindow Error: ' . $sdl->SDL_GetError(), 1);
    $sdl->SDL_Quit();
}

// Create the window renderer
$ren = $sdl->SDL_CreateRenderer($win, -1, 0);

// Set the background color to black
$sdl->SDL_SetRenderDrawColor($ren, 0, 0, 0, 255);
$sdl->SDL_RenderClear($ren);

// Pointer to SDL Events (like quit, click, keydown)
$event = $sdl->new('SDL_Event', false);

// Create the gameinfo struct
$gameinfo = $snes9x->new('struct retro_game_info', false);
$gameinfo->path = $snes9x->strdup(ROM);

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

$snes9x->retro_set_input_state(function ($port, $device, $index, $id) {
    return false;
});

// Set the video refresh callback, called for rendering each frame
$snes9x->retro_set_video_refresh(function ($data, $width, $height, $pitch) use (&$ren, $sdl) {
    // The snes9x library uses uint16 for representing a pixel
    $pixels = FFI::cast('uint16_t[' . ($height * $pitch) . ']', $data);

    // Background is black
    $sdl->SDL_SetRenderDrawColor($ren, 0, 0, 0, 255);
    $sdl->SDL_RenderClear($ren);
    // Foreground is white
    $sdl->SDL_SetRenderDrawColor($ren, 255, 255, 255, 255);

    for ($y = 0; $y < SCREEN_HEIGHT; $y++) {
        for ($x = 0; $x < SCREEN_WIDTH; $x++) {
            $pixel = $pixels[$x + (SCREEN_WIDTH * $y)];

            if ($pixel === 0) {
                $rect = $sdl->new('SDL_Rect', false);
                $rect->x = $x * ZOOM_LEVEL;
                $rect->y = $y * ZOOM_LEVEL;
                $rect->w = $rect->h = ZOOM_LEVEL;
                $sdl->SDL_RenderFillRect($ren, FFI::addr($rect));
                $sdl->SDL_RenderDrawRect($ren, FFI::addr($rect));
            }
        }
    }

    // Render the pixels
    $sdl->SDL_RenderPresent($ren);

    return;
});

$snes9x->retro_init();
$snes9x->retro_load_game(FFI::addr($gameinfo));

$isRunning = true;

while ($isRunning) {
    //Calculate current FPS
    if ($currentSecond != time()) {
        $fps = $framesInSecond;
        $currentSecond = time();
        $framesInSecond = 1;
    } else {
        ++$framesInSecond;
    }

    $snes9x->retro_run();

    if ($sdl->SDL_PollEvent(FFI::addr($event))) {
        if ($event->type == SDL_QUIT) {
            $isRunning = false;
        }
    }

    $sdl->SDL_SetWindowTitle($win, 'PHP FFI SNES - FPS: ' . $fps);
}
