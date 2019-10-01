<?php
// To install SDL2 Lib on Mac, use:
// brew install sdl2

const SDL_INIT_VIDEO = 0x00000020;
const SDL_RENDERER_ACCELERATED = 0x00000002;
const SDL_RENDERER_PRESENTVSYNC = 0x00000004;
const SDL_QUIT = 0x100;
const SDL_WINDOW_SHOWN = 0x00000004;

$sdl = FFI::load('./sdl.h');

// Initializes the SDL
if ($sdl->SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw new Exception('SDL_Init Error: ' . $sdl->SDL_GetError(), 1);
}

$width = 640;
$height = 480;

// Create the window
$win = $sdl->SDL_CreateWindow('FFI', 0, 0, $width, $height, SDL_WINDOW_SHOWN);

if ($win == null){
    throw new Exception('SDL_CreateWindow Error: ' . $sdl->SDL_GetError(), 1);
    $sdl->SDL_Quit();
}

// Create the window renderer
$ren = $sdl->SDL_CreateRenderer($win, -1, 0);

// Set the background color to black
$sdl->SDL_SetRenderDrawColor($ren, 0, 0, 0, 255);
$sdl->SDL_RenderClear($ren);

$event = $sdl->new('SDL_Event', false);

$x = 0;
$y = 0;
$isRunning = true;

while ($isRunning) {
    // Set the foreground color to green
    $sdl->SDL_SetRenderDrawColor($ren, 0, 255, 0, 255);
    // Draw a single point
    $sdl->SDL_RenderDrawPoint($ren, $x++, $y);

    if ($x === $width - 1) {
        $x = 0;
        $y++;
    }

    // Render
    $sdl->SDL_RenderPresent($ren);

    // Verify if the window was closed
    if ($sdl->SDL_PollEvent(FFI::addr($event))) {
        if ($event->type == SDL_QUIT) {
            $isRunning = false;
        }
    }
}

$sdl->SDL_Quit();
