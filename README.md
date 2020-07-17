![build](https://github.com/karlheinzkurt/cpp-micro-service/workflows/build/badge.svg)

To be written...

### Somce background thinking just to keep it somewhere
**Static linking** is important to have no common dependencies 
prohibiting partial service updates and to avoid varying runtime 
dependencies inside docker containers.

In common distributions like ubuntu, 'glibc' is using 'libnss'
dynamically linked to enable different providers for name resolution. 
This makes it tricky to achieve completely statically linked 
application. In Alpine libmusl can be used as an alternative, 
but therefore we have to build in Alpine and thus we do need 
a container for dev. See: 
https://stackoverflow.com/questions/2725255/create-statically-linked-binary-that-uses-getaddrinfo
I would guess the security issues mentioned there as well are
not that relevant for microservices, since they are build and 
deployed often and automatically, so security updates of basic 
libraries are coming in anyway. This is different to monolithic
architectures, because their updates are critical and not 
happening that often.
