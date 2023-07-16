# lib-ch340g
> read/write to ch340g device without tty driver

___

### why?
You bought an off brand arduino and realize that it comes with a ch340 instead of ftdi. Can't find arm64 binary for tty driver? Use lib-ch340g to easily read/write to your microcontroller from any linux host.


### usage

Dynamic lib

```bash
wget https://github.com/seanavery/lib-ch340g/releases/download/v0.0.1/libch340g.so.0.0.1 -o /usr/local/lib
```

Static lib
```bash
wget https://github.com/seanavery/lib-ch340g/releases/download/v0.0.1/libch340g_static.a -o /usr/local/lib
```

Header File
```bash
wget https://github.com/seanavery/lib-ch340g/releases/download/v0.0.1/ch340g.h -o /usr/local/include
```
