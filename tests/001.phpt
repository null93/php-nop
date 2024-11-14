--TEST--
Check if nop is loaded
--EXTENSIONS--
nop
--FILE--
<?php
echo 'The extension "nop" is available';
?>
--EXPECT--
The extension "nop" is available
