//Pinout entradas

  //Entradas sensores divisor de monedas
    #define diezc 14
    #define cincoc 15
    #define veintec 16
    #define cienc 17
    #define cincuentac 18
    #define doscientosc 19

    uint8_t cantidad10 = 0;
    uint8_t cantidad5 = 0;
    uint8_t cantidad20 = 0;
    uint8_t cantidad100 = 0;
    uint8_t cantidad50 = 0;
    uint8_t cantidad200 = 0;

    int estadosensor10 = 0;
    int estadosensor5 = 0;
    int estadosensor20 = 0;
    int estadosensor100 = 0;
    int estadosensor50 = 0;
    int estadosensor200 = 0;

    int diez = 0;
    int cinco = 0;
    int veinte = 0;
    int cien = 0;
    int cincuenta = 0;
    int doscientos = 0;

    int suma = 0;
    int resta = 0;

  //Entradas botones
    #define boton1 22
    #define boton2 23
    #define boton3 24
    #define boton4 25
    #define botondev 26

    int estadoboton1 = 0;
    int estadoboton2 = 0;
    int estadoboton3 = 0;
    int estadoboton4 = 0;
    int devolucion = 0;

  //Entradas fotocélula grande
    #define detector 6

    int estadodetector = 0;

//Pinout salidas

  //Salida conexión
    #define pinmaster 12

  //Entrada conexión
    #define pinslave 13

  //Salida conexión entre arduinos (dinero)
    #define pindin 2

  //Salida conexión entre arduinos (bits) 
    #define bit1 3
    #define bit2 4
    #define bit3 5

  //Servos dispensador de monedas
    #include <Servo.h>
    Servo servodiez;
    Servo servocinco;
    Servo servoveinte;
    Servo servocien;
    Servo servocincuenta;
    Servo servodoscientos;

  //Memoria interna arduino
    #include <EEPROM.h>

  //LCD (en el montaje hay que conectarlo a los pines 20 y 21)
    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>
    LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() 
  {

    //Inputs
      pinMode (diezc, INPUT_PULLUP);
      pinMode (cincoc, INPUT_PULLUP);
      pinMode (veintec, INPUT_PULLUP);
      pinMode (cienc, INPUT_PULLUP);
      pinMode (cincuentac, INPUT_PULLUP);
      pinMode (doscientosc, INPUT_PULLUP);
      pinMode (detector, INPUT_PULLUP);

      pinMode (boton1, INPUT);
      pinMode (boton2, INPUT);
      pinMode (boton3, INPUT);
      pinMode (boton4, INPUT);
      pinMode (botondev, INPUT);

      pinMode (pinslave, INPUT);

    //Outputs
      pinMode (pinmaster, OUTPUT);
      pinMode (pindin, OUTPUT);
      pinMode (bit1, OUTPUT);
      pinMode (bit2, OUTPUT);
      pinMode (bit3, OUTPUT);
      servodiez.attach (27);
      servocinco.attach (28);
      servoveinte.attach (29);
      servocien.attach (30);
      servocincuenta.attach (31);
      servodoscientos.attach (32);

      digitalWrite (pinmaster, HIGH);
      digitalWrite (pindin, LOW);
      digitalWrite (bit1, LOW);
      digitalWrite (bit2, LOW);
      digitalWrite (bit3, LOW);
      servodiez.write (0);
      servocinco.write (0);
      servoveinte.write (0);
      servocien.write (0);
      servocincuenta.write (0);
      servodoscientos.write (0);

      cantidad10 = EEPROM.read (10);
      cantidad5 = EEPROM.read (5);
      cantidad20 = EEPROM.read (20);
      cantidad100 = EEPROM.read (100);
      cantidad50 = EEPROM.read (50);
      cantidad200 = EEPROM.read (200);
    
    //LCD
      lcd.init();
      lcd.backlight();

  }

void Mensaje() 
  {
    lcd.clear();

    if (cantidad10 == 0 || cantidad5 == 0 || cantidad20 == 0 || cantidad100 == 0 || cantidad50 == 0 || cantidad200 == 0)
      {
        lcd.print ("Sin cambios");
        lcd.setCursor(0, 1);
        lcd.print ("Saldo: ");
        lcd.print (suma);

        if (estadoboton1 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton2 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton3 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton4 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }
      }

    else
      {
        lcd.print ("Saldo: ");
        lcd.print (suma);

        if (estadoboton1 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton2 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton3 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }

        if (estadoboton4 == LOW)
          {
            lcd.print ("Precio: 1 euro");
          }
      }
  }

void loop()
  { 
    // Cepo de seguridad, para el caso en donde los dos arduinos no estén conectados entre si
    while (digitalRead (pinslave) == LOW); 

    //Lectura variables
    estadosensor10 = digitalRead (diezc);
    estadosensor5 = digitalRead (cincoc);
    estadosensor20 = digitalRead (veintec);
    estadosensor100 = digitalRead (cienc);
    estadosensor50 = digitalRead (cincuentac);
    estadosensor200 = digitalRead (doscientosc);

    //Lectura sensor diez cent.
    if (estadosensor10 == LOW)
      {
        while (estadosensor10 == LOW)
          {
            estadosensor10 = digitalRead (diezc);
            delay (100);
          }
        diez = diez + 10;
        cantidad10++;
        EEPROM.write (10, cantidad10);
      }

    //Lectura sensor cinco cent.;
    if (estadosensor5 == LOW)
      {
        while (estadosensor5 == LOW)
          {
            estadosensor5 = digitalRead (cincoc);
            delay(100);
          }
        cinco = cinco + 5;
        cantidad5++;
        EEPROM.write (5, cantidad5);
      }

    //Lectura sensor veinte cent.
    if (estadosensor20 == LOW)
      {
        while (estadosensor20 == LOW)
          {
            estadosensor20 = digitalRead (veintec);
            delay(100);
          }
        veinte = veinte + 20;
        cantidad20++;
        EEPROM.write (20, cantidad20);
      }
    
    //Lectura sensor cien cent.
    if (estadosensor100 == LOW)
      {
        while (estadosensor100 == LOW)
          {
            estadosensor100 = digitalRead (cienc);
            delay(100);
          }
        cien = cien + 100;
        cantidad100++;
        EEPROM.write (100, cantidad100);
      }

    //Lectura sensor cincuenta cent.
    if (estadosensor50 == LOW)
      {
        while (estadosensor50 == LOW)
          {
            estadosensor50 = digitalRead (cincuentac);
            delay (100);
          }
        cincuenta = cincuenta + 50;
        cantidad50++;
        EEPROM.write (50, cantidad50);
      }

    //Lectura sensor doscientos cent.
    if (estadosensor200 == LOW)
      {
        while (estadosensor200 == LOW)
          {
            estadosensor200 = digitalRead (doscientosc);
            delay (100);
          }
        doscientos = doscientos + 200;
        cantidad200++;
        EEPROM.write (200, cantidad200);
      } 

    //La cantidad de monedas que han entrado
    suma = diez + cinco + veinte + cien + cincuenta + doscientos;

    //LCD
    Mensaje();

    //Lectura de variables
    estadoboton1 = digitalRead (boton1);
    estadoboton2 = digitalRead (boton2);
    estadoboton3 = digitalRead (boton3);
    estadoboton4 = digitalRead (boton4);
    devolucion = digitalRead (botondev);

    //LCD
    Mensaje();

    //Sistema devolución monedas
    if (devolucion == HIGH)
      {
        while (suma > 0)
          {
            if (suma - 200 >= resta && cantidad200 > 0)
              {
                servodoscientos.write (40);
                servodoscientos.write (0);
                resta = suma - 200;
                suma = suma - 200;
                cantidad200 = cantidad200 - 1;
                EEPROM.write (200, cantidad200);
              }

            if (suma - 100 >= resta && cantidad100 > 0)
              {
                servocien.write (40);
                servocien.write (0);
                resta = suma - 100;
                suma = suma - 100;
                cantidad100 = cantidad100 - 1;
                EEPROM.write (100, cantidad100);
              }
            
            if (suma - 50 >= resta && cantidad50 > 0)
              {
                servocincuenta.write (40);
                servocincuenta.write (0);
                resta = suma - 50;
                suma = suma - 50;
                cantidad50 = cantidad50 - 1;
                EEPROM.write (50, cantidad50);
              }

            if (suma - 20 >= resta && cantidad20 > 0)
              {
                servoveinte.write (40);
                servoveinte.write (0);
                resta = suma - 20;
                suma = suma - 20;
                cantidad20 = cantidad20 - 1;
                EEPROM.write (20, cantidad20);
              }

            if (suma - 10 >= resta && cantidad10 > 0)
              {
                servodiez.write (40);
                servodiez.write (0);
                resta = suma - 10;
                suma = suma - 10;
                cantidad10 = cantidad10 - 1;
                EEPROM.write (10, cantidad10);
              }

            if (suma - 5 >= resta && cantidad5 > 0)
              {
                servocinco.write (40);
                servocinco.write (0);
                resta = suma - 5;
                suma = suma - 5;
                cantidad5 = cantidad5 - 1;
                EEPROM.write (5, cantidad5);
              }
          }
      }

    //Sistema dispensa producto 1
    if (estadoboton1 == HIGH && suma > 100)
      {
        while (estadoboton1 == HIGH)
          {
            estadoboton1 = digitalRead (boton1);
          }
        
        estadodetector = digitalRead (detector);
        while (estadodetector == LOW)
          {
            digitalWrite (pindin, HIGH);
            digitalWrite (bit1, HIGH);
            digitalWrite (bit2, LOW);
            digitalWrite (bit3, LOW);
          }

        digitalWrite (pindin, LOW);
        digitalWrite (bit1, LOW);

        while (suma > 0)
          {
            suma = suma - 100;
            if (suma >= 200 && cantidad200 > 0)
              {
                servodoscientos.write (40);
                servodoscientos.write (0);
                suma = suma - 200;
                cantidad200 = cantidad200 - 1;
                EEPROM.write (200, cantidad200);
              }
            
            if (suma >= 100 && cantidad100 > 0)
              {
                servocien.write (40);
                servocien.write (0);
                suma = suma - 100;
                cantidad100 = cantidad100 - 1;
                EEPROM.write (100, cantidad100);
                
              }

            if (suma >= 50 && cantidad50 > 0)
              {
                servocincuenta.write (40);
                servocincuenta.write (0);
                suma = suma - 50;
                cantidad50 = cantidad50 - 1;
                EEPROM.write (50, cantidad50);
              }

            if (suma >= 20 && cantidad20 > 0)
              {
                servoveinte.write (40);
                servoveinte.write (0);
                suma = suma - 20;
                cantidad20 = cantidad20 - 1;
                EEPROM.write (20, cantidad20);
              }

            if (suma >= 10 && cantidad10 > 0)
              {
                servodiez.write (40);
                servodiez.write (0);
                suma = suma - 10;
                cantidad10 = cantidad10 - 1;
                EEPROM.write (10, cantidad10);
              }

            if (suma >= 5 && cantidad5 > 0)
              {
                servocinco.write (40);
                servocinco.write (0);
                suma = suma - 5;
                cantidad5 = cantidad5 - 1;
                EEPROM.write (5, cantidad5);
              }
          }
      }

    //Sistema dispensa producto 2
    if (estadoboton2 == HIGH && suma > 100)
      {
        while (estadoboton2 == HIGH)
          {
            estadoboton2 = digitalRead (boton2);
          }
        
        estadodetector = digitalRead (detector);
        while (estadodetector == LOW)
          {
            digitalWrite (pindin, HIGH);
            digitalWrite (bit1, LOW);
            digitalWrite (bit2, HIGH);
            digitalWrite (bit3, LOW);
          }

        digitalWrite (pindin, LOW);
        digitalWrite (bit2, LOW);

        while (suma > 0)
          {
            suma = suma - 100;
            if (suma >= 200 && cantidad200 > 0)
              {
                servodoscientos.write (40);
                servodoscientos.write (0);
                suma = suma - 200;
                cantidad200 = cantidad200 - 1;
                EEPROM.write (200, cantidad200);
              }
            
            if (suma >= 100 && cantidad100 > 0)
              {
                servocien.write (40);
                servocien.write (0);
                suma = suma - 100;
                cantidad100 = cantidad100 - 1;
                EEPROM.write (100, cantidad100);
                
              }

            if (suma >= 50 && cantidad50 > 0)
              {
                servocincuenta.write (40);
                servocincuenta.write (0);
                suma = suma - 50;
                cantidad50 = cantidad50 - 1;
                EEPROM.write (50, cantidad50);
              }

            if (suma >= 20 && cantidad20 > 0)
              {
                servoveinte.write (40);
                servoveinte.write (0);
                suma = suma - 20;
                cantidad20 = cantidad20 - 1;
                EEPROM.write (20, cantidad20);
              }

            if (suma >= 10 && cantidad10 > 0)
              {
                servodiez.write (40);
                servodiez.write (0);
                suma = suma - 10;
                cantidad10 = cantidad10 - 1;
                EEPROM.write (10, cantidad10);
              }

            if (suma >= 5 && cantidad5 > 0)
              {
                servocinco.write (40);
                servocinco.write (0);
                suma = suma - 5;
                cantidad5 = cantidad5 - 1;
                EEPROM.write (5, cantidad5);
              }
          }
      }

    //Sistema dispensa producto 3
    if (estadoboton3 == HIGH && suma > 100)
      {
        while (estadoboton3 == HIGH)
          {
            estadoboton3 = digitalRead (boton3);
          }
        
        estadodetector = digitalRead (detector);
        while (estadodetector == LOW)
          {
            digitalWrite (pindin, HIGH);
            digitalWrite (bit1, HIGH);
            digitalWrite (bit2, HIGH);
            digitalWrite (bit3, LOW);
          }

        digitalWrite (pindin, LOW);
        digitalWrite (bit1, LOW);
        digitalWrite (bit2, LOW);

        while (suma > 0)
          {
            suma = suma - 100;
            if (suma >= 200 && cantidad200 > 0)
              {
                servodoscientos.write (40);
                servodoscientos.write (0);
                suma = suma - 200;
                cantidad200 = cantidad200 - 1;
                EEPROM.write (200, cantidad200);
              }
            
            if (suma >= 100 && cantidad100 > 0)
              {
                servocien.write (40);
                servocien.write (0);
                suma = suma - 100;
                cantidad100 = cantidad100 - 1;
                EEPROM.write (100, cantidad100);
                
              }

            if (suma >= 50 && cantidad50 > 0)
              {
                servocincuenta.write (40);
                servocincuenta.write (0);
                suma = suma - 50;
                cantidad50 = cantidad50 - 1;
                EEPROM.write (50, cantidad50);
              }

            if (suma >= 20 && cantidad20 > 0)
              {
                servoveinte.write (40);
                servoveinte.write (0);
                suma = suma - 20;
                cantidad20 = cantidad20 - 1;
                EEPROM.write (20, cantidad20);
              }

            if (suma >= 10 && cantidad10 > 0)
              {
                servodiez.write (40);
                servodiez.write (0);
                suma = suma - 10;
                cantidad10 = cantidad10 - 1;
                EEPROM.write (10, cantidad10);
              }

            if (suma >= 5 && cantidad5 > 0)
              {
                servocinco.write (40);
                servocinco.write (0);
                suma = suma - 5;
                cantidad5 = cantidad5 - 1;
                EEPROM.write (5, cantidad5);
              }
          }
      }

    //Sistema dispensa producto 4
    if (estadoboton4 == HIGH && suma > 100)
      {
        while (estadoboton4 == HIGH)
          {
            estadoboton4 = digitalRead (boton4);
          }
        
        estadodetector = digitalRead (detector);
        while (estadodetector == LOW)
          {
            digitalWrite (pindin, HIGH);
            digitalWrite (bit1, LOW);
            digitalWrite (bit2, LOW);
            digitalWrite (bit3, HIGH);
          }

        digitalWrite (pindin, LOW);
        digitalWrite (bit3, LOW);

        while (suma > 0)
          {
            suma = suma - 100;
            if (suma >= 200 && cantidad200 > 0)
              {
                servodoscientos.write (40);
                servodoscientos.write (0);
                suma = suma - 200;
                cantidad200 = cantidad200 - 1;
                EEPROM.write (200, cantidad200);
              }
            
            if (suma >= 100 && cantidad100 > 0)
              {
                servocien.write (40);
                servocien.write (0);
                suma = suma - 100;
                cantidad100 = cantidad100 - 1;
                EEPROM.write (100, cantidad100);
                
              }

            if (suma >= 50 && cantidad50 > 0)
              {
                servocincuenta.write (40);
                servocincuenta.write (0);
                suma = suma - 50;
                cantidad50 = cantidad50 - 1;
                EEPROM.write (50, cantidad50);
              }

            if (suma >= 20 && cantidad20 > 0)
              {
                servoveinte.write (40);
                servoveinte.write (0);
                suma = suma - 20;
                cantidad20 = cantidad20 - 1;
                EEPROM.write (20, cantidad20);
              }

            if (suma >= 10 && cantidad10 > 0)
              {
                servodiez.write (40);
                servodiez.write (0);
                suma = suma - 10;
                cantidad10 = cantidad10 - 1;
                EEPROM.write (10, cantidad10);
              }

            if (suma >= 5 && cantidad5 > 0)
              {
                servocinco.write (40);
                servocinco.write (0);
                suma = suma - 5;
                cantidad5 = cantidad5 - 1;
                EEPROM.write (5, cantidad5);
              }
          }
      }
    
    suma = 0;
  }