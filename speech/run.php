<?php
const kCFStringEncodingUTF8 = 0x08000100;

$speech = FFI::load('speech.h');

// Text to speech. One phrase per line.
$text = <<<EOT
Olá, eu sou a assistente virtual do Bob.
Sejam bem-vindos a palestra sobre F F I.
E sim, esse texto está sendo sintetizado pela biblioteca nativa do Mac, conversando direto com o P H P através do F F I.
Com vocês, o rei da gambiarra, Boooooob.
É nóis que voa bruxão!
EOT;

// Create a speech channel
$speechChannel = $speech->new('SpeechChannel', false);
$speech->NewSpeechChannel(null, FFI::addr($speechChannel));

$phrases = explode(PHP_EOL, $text);

foreach ($phrases as $phrase) {
    // Transform the C String into CF String (Mac format)
    $string = $speech->CFStringCreateWithCString(null, $phrase, kCFStringEncodingUTF8);
    // Speak
    $speech->SpeakCFString($speechChannel, $string, null);

    while ($speech->SpeechBusy()) {
        // Waits speech finish
    }

    echo $phrase . PHP_EOL;
}











