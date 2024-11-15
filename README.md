## PHP Extension — NOP

Sometimes you just want to disable the functionality of a build-in PHP function without touching code or using the `disable_functions` option which spits out a fatal error.
This extension is a proof of concept that allows you to replace any built-in function in PHP with a NOP (no operation) function.
The NOP replacement function does not return any value so it is not guaranteed to be a drop-in replacement for all functions.

## Installation

Once you copy the `.so` file to the PHP extensions directory, you can enable it by adding the following line to your `php.ini` file:

```ini
extension=nop.so
nop.functions=chmod,chown
```

Notice that `nop.functions` is a comma-separated list of functions that you want to replace with the NOP function.

## Development

Spin up a Docker container:

```shell
docker run -v `pwd`:/usr/src -w /usr/src --rm -it php:8.3-cli-alpine sh
```

Inside the container, run the following commands:

```shell
# Install build dependencies and build the extension
apk --update add php83-dev make g++
phpize && ./configure && make && make install
make test

# Manually test functionality
php -d 'extension=nop.so' -d 'nop.functions=' -r 'printf ("hi\n");'
php -d 'extension=nop.so' -d 'nop.functions=printf' -r 'printf ("hi\n");'
```

## Additional Resources

- https://www.phpinternalsbook.com/
- https://www.zend.com/sites/zend/files/pdfs/whitepaper-zend-php-extensions.pdf
