## PHP Extension — NOP

Sometimes you just want to disable the functionality of a build-in PHP function without touching code or using the `disable_functions` option which spits out a fatal error.
This extension is a proof of concept that allows you to replace any built-in function in PHP with a NOP (no operation) function.
The NOP replacement function does not return any value so it is not guaranteed to be a drop-in replacement for all functions.

## Installation

Once you copy the `.so` file to the PHP extensions directory, you can enable it by adding the following line to your `php.ini` file:

```ini
extension=nop.so
nop.ignore_functions=chmod,chown
```

Notice that `nop.ignore_functions` is a comma-separated list of functions that you want to replace with the NOP function.

## Development

```
# Run inside docker container
docker run -v `pwd`:/usr/src -w /usr/src --rm -it php:8.3-cli-alpine sh

# Install build dependencies and build the extension
apk --update add php83-dev make g++
phpize && ./configure && make && make install

# Setup a quick test
touch ./private/sample
echo "<?php chmod(__DIR__ . '/sample', 0777);" > ./private/sample.php

# Run the test
chmod 644 ./private/sample
ls -la ./private/sample
php -d 'extension=nop.so' -d 'nop.ignore_functions=chmod' ./private/sample.php
ls -la ./private/sample
```

## Additional Resources

- https://www.phpinternalsbook.com/
- https://www.zend.com/sites/zend/files/pdfs/whitepaper-zend-php-extensions.pdf
