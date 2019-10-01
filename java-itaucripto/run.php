<?php
const JNI_VERSION_1_1 = 0x00010001;
const JNI_VERSION_1_2 = 0x00010002;
const JNI_VERSION_1_4 = 0x00010004;
const JNI_VERSION_1_6 = 0x00010006;
const JNI_VERSION_1_8 = 0x00010008;
const JNI_VERSION_9   = 0x00090000;
const JNI_VERSION_10  = 0x000a0000;

$jni = FFI::load('libjvm.h');

$vm = $jni->new('JavaVM', false);
$env = $jni->new('JNIEnv', false);
$vmArgs = $jni->new('JavaVMInitArgs', false);
$options = $jni->new('JavaVMOption[1]', false);

$options[0]->optionString = $jni->strdup('-Djava.class.path=/php-itaucripto');

$vmArgs->options = $options;
$vmArgs->version = JNI_VERSION_10;
$vmArgs->nOptions = 1;

$res = $jni->JNI_CreateJavaVM(FFI::addr(FFI::addr($vm)), FFI::addr($env), FFI::addr($vmArgs));

$env = $jni->cast('JNIEnv', $env[0]);
$envPointer = FFI::addr($env);

$callObjectMethod = $jni->cast('CallObjectMethod_func_t', $env->CallObjectMethod);
$findClass = $jni->cast('FindClass_func_t', $env->FindClass);
$getMethodID = $jni->cast('GetMethodID_func_t', $env->GetMethodID);
$getStringUTFChars = $jni->cast('GetStringUTFChars_func_t', $env->GetStringUTFChars);
$newObject = $jni->cast('NewObject_func_t', $env->NewObject);
$newStringUTF = $jni->cast('NewStringUTF_func_t', $env->NewStringUTF);

$itaucriptoClass = $findClass($envPointer, 'Itau/Itaucripto');
$itaucriptoConstructor = $getMethodID($envPointer, $itaucriptoClass, '<init>', '()V');
$itaucripto = $newObject($envPointer, $itaucriptoClass, $itaucriptoConstructor);

$codEmp = $newStringUTF($envPointer, 'J1234567890123456789012345');
$chave = $newStringUTF($envPointer, 'ABCD123456ABCD12');
$pedido = $newStringUTF($envPointer, '1234');
$valor = $newStringUTF($envPointer, '1,99');
$observacao = $newStringUTF($envPointer, 'Essa é uma observação');
$nomeSacado = $newStringUTF($envPointer, 'José Antônio');
$codigoInscricao = $newStringUTF($envPointer, '01');
$numeroInscricao = $newStringUTF($envPointer, '82938674341');
$enderecoSacado = $newStringUTF($envPointer, 'Rua das Hortências');
$bairroSacado = $newStringUTF($envPointer, 'Jardim das Flores');
$cepSacado = $newStringUTF($envPointer, '13080040');
$cidadeSacado = $newStringUTF($envPointer, 'Campinas');
$estadoSacado = $newStringUTF($envPointer, 'SP');
$dataVencimento = $newStringUTF($envPointer, '31122013');
$urlRetorna = $newStringUTF($envPointer, 'retorno/retorno.php');
$obsAd1 = $newStringUTF($envPointer, 'Aqui vai a observação 1');
$obsAd2 = $newStringUTF($envPointer, 'Aqui vai a observação 2');
$obsAd3 = $newStringUTF($envPointer, 'Aqui vai a observação 3');

/*
"L<fully-qualified-name>;", with dot replaced by forward slash (/), e.g.,, the class descriptor for String is "Ljava/lang/String;". For primitives, use "I" for int, "B" for byte, "S" for short, "J" for long, "F" for float, "D" for double, "C" for char, and "Z" for boolean. For arrays, include a prefix "[", e.g., "[Ljava/lang/Object;" for an array of Object; "[I" for an array of int.
 */
$geraDados = $getMethodID($envPointer, $itaucriptoClass, 'geraDados', '(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;');

$dados = $callObjectMethod($envPointer, $itaucripto, $geraDados, $codEmp, $pedido, $valor, $observacao, $chave, $nomeSacado, $codigoInscricao, $numeroInscricao, $enderecoSacado, $bairroSacado, $cepSacado, $cidadeSacado, $estadoSacado, $dataVencimento, $urlRetorna, $obsAd1, $obsAd2, $obsAd3);

var_dump($getStringUTFChars($envPointer, $dados, null));
