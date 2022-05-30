# Kotxesitua
Kotxesitua kontrolatzen duen programa

## Proiektua eraiki
Proiektua eraikitzeko beharrezko gauzak:
	- CMake 3.16 edo berriagoa.
	- arm-linux-gnueabihf-gcc (konpilazio gurutzaturako).
	- GNU Make

Behin horiek instalatuta exekutatu:
```
# Sortu proiektua eraikiko den karpeta
$ mkdir eraiki/

# Sartu karpetan
$ cd eraiki/

# Konpilazio gurutzatua aktibatuta
$ cmake -G "Unix Makefiles" -D KONP_GURUTZ=ON --build eraiki/ --config Release --target all ..

# Konpilazio gurutzatua desaktibatuta
$ cmake -G "Unix Makefiles" -D KONP_GURUTZ=OFF --build eraiki/ --config Release --target all ..

# Azkenik proiektua eraiki
make all
```
