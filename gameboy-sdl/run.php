<?php
const ROM = 'pokemon.gbc';

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

const ZOOM_LEVEL = 4;
const SCREEN_HEIGHT = 144;
const SCREEN_WIDTH = 160;

$currentSecond = 0;
$fps = 0;
$framesInSecond = 0;

$sdl = FFI::load('sdl.h');
$sameboy = FFI::load('sameboy_libretro.h');

if ($sdl->SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw new Exception('SDL_Init Error: ' . $sdl->SDL_GetError(), 1);
}

$win = $sdl->SDL_CreateWindow('PHP FFI Boy', 0, 0, SCREEN_WIDTH * ZOOM_LEVEL, SCREEN_HEIGHT * ZOOM_LEVEL, SDL_WINDOW_SHOWN);

if ($win == null){
    throw new Exception('SDL_CreateWindow Error: ' . $sdl->SDL_GetError(), 1);
    $sdl->SDL_Quit();
}

$ren = $sdl->SDL_CreateRenderer($win, -1, 0);

$sdl->SDL_SetRenderDrawColor($ren, 0, 0, 0, 255);
$sdl->SDL_RenderClear($ren);

$event = $sdl->new('SDL_Event', false);

$gameinfo = $sameboy->new('struct retro_game_info', false);
$gameinfo->path = $sameboy->strdup(ROM);

$sameboy->retro_set_environment(function($cmd, $data) use ($sameboy) {
    if ($cmd === RETRO_ENVIRONMENT_SET_PIXEL_FORMAT) {
        return true;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_VARIABLE) {
        $argument = $sameboy->cast('struct retro_variable', $data);

        if ($argument->key === 'sameboy_model') {
            $argument->value = $sameboy->strdup('Game Boy');
            $data = FFI::addr($argument);
        }

        return true;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE) {
        $argument = $sameboy->cast('bool', $data);
        $data = FFI::addr($argument);
        return false;
    }

    if ($cmd === RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE) {
        $argument = $sameboy->cast('struct retro_rumble_interface', $data);
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

$sameboy->retro_set_audio_sample(function($a, $b) {
    return;
});

$sameboy->retro_set_input_poll(function () {
    return;
});

$sameboy->retro_set_input_state(function ($port, $device, $index, $id) use (&$key) {
    if ($key === KEYBOARD_MAPPING[$id]) {
        return true;
    }

    return false;
});

$sameboy->retro_set_video_refresh(function ($data, $width, $height, $pitch) use (&$ren, $sdl) {
    $pixels = FFI::cast('uint32_t[' . ($width * $height) . ']', $data);

    $sdl->SDL_SetRenderDrawColor($ren, 142, 134, 9, 255);
    $sdl->SDL_RenderClear($ren);
    $sdl->SDL_SetRenderDrawColor($ren, 37, 57, 61, 255);

    for ($y = 0; $y < SCREEN_HEIGHT; $y++) {
        for ($x = 0; $x < SCREEN_WIDTH; $x++) {
            $pixel = $pixels[$x + (SCREEN_WIDTH * $y)];

            if ($pixel === 0) {
                $rect = $sdl->new('SDL_Rect', true);
                $rect->x = $x * ZOOM_LEVEL;
                $rect->y = $y * ZOOM_LEVEL;
                $rect->w = $rect->h = ZOOM_LEVEL;
                $sdl->SDL_RenderFillRect($ren, FFI::addr($rect));
                $sdl->SDL_RenderDrawRect($ren, FFI::addr($rect));
            }
        }
    }

    $sdl->SDL_RenderPresent($ren);

    return;
});

$sameboy->retro_init();
$sameboy->retro_load_game(FFI::addr($gameinfo));

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

    $sameboy->retro_run();

    if ($sdl->SDL_PollEvent(FFI::addr($event))) {
        if ($event->type == SDL_QUIT) {
            $isRunning = false;
        }
    }

    $sdl->SDL_SetWindowTitle($win, 'PHP FFI Boy - FPS: ' . $fps);
}
