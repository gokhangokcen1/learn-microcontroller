![Devre](https://github.com/gokhangokcen1/learn-microcontroller/blob/main/esp/06-leds/circuit.png)


## PULL UP - PULL DOWN
Pull up: Pin boştayken içeride 3.3V vererek onu 1 yapar. Butonda basınca 1 > 0 olur
Pull down: Pin boştayken içeride onu GND'ye başlayarak 0 yapar. Butonda basınca 0 > 1 olur

## KESME 
Normal iş yapılırken başka bir şey gelince işi bırak ona bak. 

```
while (true) {
    button_state = gpio_get_level(BUTTON_PIN);
}
```

Burada sürekli buton durumu kontrol ediliyor. Buna `polling` denir. 

Kesme kullanılırsa bu sürekli sorulmaz, butona basıldığında ESP32'ye bilgi gider. Fakat kesme fonksiyonlarını yazmak gerekir. 