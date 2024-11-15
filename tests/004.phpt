--TEST--
functions=printf
--EXTENSIONS--
nop
--INI--
nop.functions=printf
--FILE--
<?php
printf("Hello, World!\n");
?>
--EXPECT--

