## PHP Extension — NOP

Sometimes you just want to disable the functionality of a build-in PHP function without touching code or using the `disable_functions` option which spits out a fatal error.
This extension is a proof of concept that allows you to replace any built-in function in PHP with a NOP (no operation) function.
The NOP replacement function does not return any value so it is not guaranteed to be a drop-in replacement for all functions.

## Installation

You can install this extension via the deb packages in the releases section.
For example, to install the extension for PHP 8.3 on an ARM64 machine, run the following:

```shell
curl -sLo ./php8.3-nop_arm64_0.1.0.deb https://github.com/null93/php-nop/releases/download/0.1.0/php8.3-nop_arm64_0.1.0.deb
apt install ./php8.3-nop_arm64_0.1.0.deb
```

Next, you will want to enable the extension in your PHP configuration file.

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

## Package Extension

Automatically packaged with NFPM and Github actions. Simply tag and push. If you need to manually package, run the following:

```shell
export VERSION=0.1.0
export PHP_VERSION=8.3
export ARCH=amd64
./scripts/nfpm-template > nfpm.yaml
nfpm pkg --packager deb --target php8.3_nop_amd64.deb
```

## Additional Resources

- https://www.phpinternalsbook.com/
- https://www.zend.com/sites/zend/files/pdfs/whitepaper-zend-php-extensions.pdf
- https://www.zend.com/resources/writing-php-extensions
