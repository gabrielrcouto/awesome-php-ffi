<?php
$gtk3 = FFI::load('gtk3.h');

const GTK_WINDOW_TOPLEVEL = 0;
const GTK_WINDOW_POPUP = 1;

$gtkArgc = $gtk3->new('int32_t', false);
$gtk3->gtk_init(FFI::addr($gtkArgc), null);

$window = $gtk3->gtk_window_new(GTK_WINDOW_TOPLEVEL);
$button = $gtk3->gtk_button_new_with_label('Created by PHP');
$gtk3->gtk_container_add($window, $button);
$gtk3->gtk_container_set_border_width($window, 50);
$gtk3->gtk_window_set_title($window, 'GTK3 by PHP');

$gtk3->gtk_widget_show_all($window);
$gtk3->gtk_main();
