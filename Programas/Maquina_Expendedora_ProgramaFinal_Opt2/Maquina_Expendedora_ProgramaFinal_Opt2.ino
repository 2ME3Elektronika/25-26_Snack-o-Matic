//Librerías
  #include <EEPROM.h>
  #include <Servo.h>
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>

//Pinout entradas
  //Entradas sensores divisor de monedas
    #define diezc 14
    #define cincoc 15
    #define veintec 16
    #define cienc 17
    #define cincuentac 18
    #define doscientosc 19

  //Entradas botones de selección
    #define boton1 22
    #define boton2 23
    #define boton3 24
    #define boton4 25
    #define botondev 33

  //Entrada fotocélula productos
    #define detector 6

//Pinout salidas
  //Servos dispensador de monedas
    Servo servodiez;
    Servo servocinco;
    Servo servoveinte;
    Servo servocien;
    Servo servocincuenta;
    Servo servodoscientos;

  //LCD (en el montaje hay que conectarlo a los pines 20 y 21 del Arduino Mega)
    LiquidCrystal_I2C lcd(0x27, 20, 4);

  //Motores sinfines (dispensador de productos)
    #define motor1 7 
    #define motor2 8
    #define motor3 9 
    #define motor4 10 

//Variables
    uint8_t cantidad10 = 0; //Indica la cantidad de monedas de 10 céntimos que hay en la máquina
    uint8_t cantidad5 = 0; //Indica la cantidad de monedas de 5 céntimos que hay en la máquina
    uint8_t cantidad20 = 0; //Indica la cantidad de monedas de 20 céntimos que hay en la máquina
    uint8_t cantidad100 = 0; //Indica la cantidad de monedas de 1 euro que hay en la máquina
    uint8_t cantidad50 = 0; //Indica la cantidad de monedas de 50 céntimos que hay en la máquina
    uint8_t cantidad200 = 0; //Indica la cantidad de monedas de 2 euros que hay en la máquina

    int estadosensor10 = 0; //Indica si el sensor de 10 céntimos ha detectado una moneda
    int estadosensor5 = 0; //Indica si el sensor de 5 céntimos ha detectado una moneda
    int estadosensor20 = 0; //Indica si el sensor de 20 céntimos ha detectado una moneda
    int estadosensor100 = 0; //Indica si el sensor de 1 euro ha detectado una moneda
    int estadosensor50 = 0; //Indica si el sensor de 50 céntimos ha detectado una moneda
    int estadosensor200 = 0; //Indica si el sensor de 2 euros ha detectado una moneda

    int diez = 0; //Variable para la suma de monedas que tenemos
    int cinco = 0; //Variable para la suma de monedas que tenemos
    int veinte = 0; //Variable para la suma de monedas que tenemos
    int cien = 0; //Variable para la suma de monedas que tenemos
    int cincuenta = 0; //Variable para la suma de monedas que tenemos
    int doscientos = 0; //Variable para la suma de monedas que tenemos

    float suma = 0; //Ecuación para saber cuánto se ha metido (en cent)
    float sumaeuro = 0; //Ecuación para saber cuánto se ha metido (en euros)

    int estadoboton1 = 0; //Indica si el botón 1 se ha pulsado
    int estadoboton2 = 0; //Indica si el botón 2 se ha pulsado
    int estadoboton3 = 0; //Indica si el botón 3 se ha pulsado
    int estadoboton4 = 0; //Indica si el botón 4 se ha pulsado
    int devolucion = 0; //Indica si el botón de devolución se ha pulsado

    int estadodetector = 0; //Indica si el detector de productos se ha activado

    int Estado = 0; //Indica el estado de la máquina

void setup() 
  {
    Serial.begin (9600);
    //Inputs
      pinMode (diezc, INPUT_PULLUP);
      pinMode (cincoc, INPUT_PULLUP);
      pinMode (veintec, INPUT_PULLUP);
      pinMode (cienc, INPUT_PULLUP);
      pinMode (cincuentac, INPUT_PULLUP);
      pinMode (doscientosc, INPUT_PULLUP);
      pinMode (detector, INPUT);

      pinMode (boton1, INPUT);
      pinMode (boton2, INPUT);
      pinMode (boton3, INPUT);
      pinMode (boton4, INPUT);
      pinMode (botondev, INPUT);


    //Outputs
      pinMode (motor1, OUTPUT);
      pinMode (motor2, OUTPUT);
      pinMode (motor3, OUTPUT);
      pinMode (motor4, OUTPUT);

      servodiez.attach (27);
      servocinco.attach (28);
      servoveinte.attach (29);
      servocien.attach (30);
      servocincuenta.attach (31);
      servodoscientos.attach (32);

      digitalWrite (motor1, LOW);
      digitalWrite (motor2, LOW);
      digitalWrite (motor3, LOW);
      digitalWrite (motor4, LOW);

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
      Mensaje ();
  }

void Mensaje() 
  {
    lcd.clear();

    if (cantidad10 == 0 || cantidad5 == 0 || cantidad20 == 0 || cantidad100 == 0 || cantidad50 == 0 || cantidad200 == 0)
      {
        sumaeuro = suma / 100.00;
        lcd.print ("      Sin cambios    ");
        lcd.setCursor(0, 1);
        lcd.print ("       Saldo: ");
        lcd.print (sumaeuro);
        lcd.print ("$");
      }

    else
      {
        sumaeuro = suma / 100;
        lcd.print ("       Saldo: ");
        lcd.print (sumaeuro);
        lcd.print ("$");
      }

    if (estadoboton1 == HIGH)
      {
        while (estadoboton1 == HIGH)
          {
            estadoboton1 = digitalRead (boton1);
          }
        lcd.setCursor (0, 1);
        lcd.print ("  Precio: 1,20 euros");
      }

    if (estadoboton2 == HIGH)
      {
        while (estadoboton2 == HIGH)
          {
            estadoboton2 = digitalRead (boton2);
          }
        lcd.setCursor (0, 1);
        lcd.print ("  Precio: 1,50 euros");
      }

    if (estadoboton3 == HIGH)
      {
        while (estadoboton3 == HIGH)
          {
            estadoboton3 = digitalRead (boton3);
          }
        lcd.setCursor (0, 1);
        lcd.print ("  Precio: 1,70 euros");
      }

    if (estadoboton4 == HIGH)
      {
        while (estadoboton4 == HIGH)
          {
            estadoboton4 = digitalRead (boton4);
          }
        lcd.setCursor (0, 1);
        lcd.print ("     Precio: 2 euros");
      }
  }

void Lectura_de_5cent() //Lee si se ha introducido una moneda de 5 céntimos
  {
    estadosensor5 = digitalRead (cincoc);

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
        suma = diez + cinco + veinte + cien + cincuenta + doscientos;
        EEPROM.write (5, cantidad5);
        Mensaje ();
      }
  }

void Lectura_de_10cent() //Lee si se ha introducido una moneda de 10 céntimos
  {
    estadosensor10 = digitalRead (diezc);

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
        suma = diez + cinco + veinte + cien + cincuenta + doscientos;
        EEPROM.write (10, cantidad10);
        Mensaje ();
      }
  }

void Lectura_de_20cent() //Lee si se ha introducido una moneda de 20 céntimos
  {
    estadosensor20 = digitalRead (veintec);

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
          suma = diez + cinco + veinte + cien + cincuenta + doscientos;
          EEPROM.write (20, cantidad20);
          Mensaje ();
        }
  }

void Lectura_de_50cent() //Lee si se ha introducido una moneda de 50 céntimos
  {
    estadosensor50 = digitalRead (cincuentac);

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
        suma = diez + cinco + veinte + cien + cincuenta + doscientos;
        EEPROM.write (50, cantidad50);
        Mensaje ();
      }
  }

void Lectura_de_1euro() //Lee si se ha introducido una moneda de 1 euro
  {
    estadosensor100 = digitalRead (cienc);

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
        suma = diez + cinco + veinte + cien + cincuenta + doscientos;
        EEPROM.write (100, cantidad100);
        Mensaje ();
      }
  }

void Lectura_de_2euros() //Lee si se ha introducido una moneda de 2 euros
  {
    estadosensor200 = digitalRead (doscientosc);

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
        suma = diez + cinco + veinte + cien + cincuenta + doscientos;
        EEPROM.write (200, cantidad200);
        Mensaje ();
      } 
  }
void Dispensa_Producto_1() //Reconoce y en caso de pedrise dispensa el producto denominado 1
  {
    estadoboton1 = digitalRead (boton1);

    if (estadoboton1 == HIGH && suma >= 120)
      {
        while (estadoboton1 == HIGH)
          {
            estadoboton1 = digitalRead (boton1);
          }
        
        suma = suma - 120;
        estadodetector = digitalRead (detector);
        lcd.clear();
        lcd.print ("      Dispensando...");

        while (estadodetector == LOW)
          {
            estadodetector = digitalRead (detector);
            digitalWrite (motor1, HIGH);
          }

        digitalWrite (motor1, LOW);

        while (suma > 0)
          {
            Devolver();
          }

        diez = 0;
        cinco = 0;
        veinte = 0;
        cien = 0;
        cincuenta = 0;
        doscientos = 0;
        suma = 0;
        lcd.clear();
        Mensaje();
      }

    if (estadoboton1 == HIGH) { Mensaje(); }
  }

void Dispensa_Producto_2() //Reconoce y en caso de pedrise dispensa el producto denominado 2
   {
    estadoboton2 = digitalRead (boton2);

    if (estadoboton1 == HIGH && suma >= 150)
      {
        while (estadoboton2 == HIGH)
          {
            estadoboton2 = digitalRead (boton2);
          }
        
        suma = suma - 150;
        estadodetector = digitalRead (detector);
        lcd.clear();
        lcd.print ("      Dispensando...");

        while (estadodetector == LOW)
          {
            estadodetector = digitalRead (detector);
            digitalWrite (motor2, HIGH);
          }

        digitalWrite (motor2, LOW);

        while (suma > 0)
          {
            Devolver();
          }

        diez = 0;
        cinco = 0;
        veinte = 0;
        cien = 0;
        cincuenta = 0;
        doscientos = 0;
        suma = 0;
        lcd.clear();
        Mensaje();
      }

    if (estadoboton2 == HIGH) { Mensaje(); }
   }

void Dispensa_Producto_3() //Reconoce y en caso de pedrise dispensa el producto denominado 3
  {
    if (estadoboton3 == HIGH && suma >= 170)
      {
        while (estadoboton3 == HIGH)
          {
            estadoboton3 = digitalRead (boton3);
          }
        
        suma = suma - 170;
        estadodetector = digitalRead (detector);
        lcd.clear();
        lcd.print ("      Dispensando...");

        while (estadodetector == LOW)
          {
            estadodetector = digitalRead (detector);
            digitalWrite (motor3, HIGH);
          }

        digitalWrite (motor3, LOW);

        while (suma > 0)
          {
            Devolver();
          }

        diez = 0;
        cinco = 0;
        veinte = 0;
        cien = 0;
        cincuenta = 0;
        doscientos = 0;
        suma = 0;
        lcd.clear();
        Mensaje();
      }

    if (estadoboton3 == HIGH) { Mensaje(); }
  }

void Dispensa_Producto_4 () //Reconoce y en caso de pedrise dispensa el producto denominado 4
  {
    if (estadoboton4 == HIGH && suma >= 200)
      {
        while (estadoboton4 == HIGH)
          {
            estadoboton4 = digitalRead (boton4);
          }

        suma = suma - 200;
        estadodetector = digitalRead (detector);
        lcd.clear();
        lcd.print ("      Dispensando...");

        while (estadodetector == LOW)
          {
            estadodetector = digitalRead (detector);
            digitalWrite (motor4, HIGH);
          }

        digitalWrite (motor4, LOW);

        while (suma > 0)
          {
            Devolver();
          }

        diez = 0;
        cinco = 0;
        veinte = 0;
        cien = 0;
        cincuenta = 0;
        doscientos = 0;
        suma = 0;
        lcd.clear();
        Mensaje();
      }

    if (estadoboton4 == HIGH) { Mensaje(); }
  }

void Boton_Devolucion() //Reconoce y en caso de pedrise devuelve el dinero introducido (no las mismas monedas, solo el mismo valor)
  {
    devolucion = digitalRead (botondev);

    if (devolucion == HIGH)
      {
        while (devolucion == HIGH)
          {
            devolucion = digitalRead (botondev);
          }

        lcd.clear();
        lcd.print ("      Devolviendo...");

        while (suma > 0)
          {
            Devolver();
          }
        lcd.clear();
        Mensaje();
      }
  }

void Devolver() //El sistema de cambios, se encarga de devolver el dinero correspondiente
  {
    if (suma >= 200 && cantidad200 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servodoscientos.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servodoscientos.write(angulo);
            delay(15);
          }

        suma = suma - 200;
        cantidad200 = cantidad200 - 1;
        EEPROM.write (200, cantidad200);
      }

    if (suma >= 100 && cantidad100 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servocien.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servocien.write(angulo);
            delay(15);
          }

        suma = suma - 100;
        cantidad100 = cantidad100 - 1;
        EEPROM.write (100, cantidad100);
      }

    if (suma >= 50 && cantidad50 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servocincuenta.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servocincuenta.write(angulo);
            delay(15);
          }

        suma = suma - 50;
        cantidad50 = cantidad50 - 1;
        EEPROM.write (50, cantidad50);
      }

    if (suma >= 20 && cantidad20 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servoveinte.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servoveinte.write(angulo);
            delay(15);
          }

        suma = suma - 20;
        cantidad20 = cantidad20 - 1;
        EEPROM.write (20, cantidad20);
      }

    if (suma >= 10 && cantidad10 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servodiez.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servodiez.write(angulo);
            delay(15);
          }

        suma = suma - 10;
        cantidad10 = cantidad10 - 1;
        EEPROM.write (10, cantidad10);
      }

    if (suma >= 5 && cantidad5 > 0)
      {
        for (int angulo = 0; angulo <= 180; angulo++) 
          {
            servocinco.write(angulo);
            delay(15); 
          }

        for (int angulo = 180; angulo >= 0; angulo--) 
          {
            servocinco.write(angulo);
            delay(15);
          }

        suma = suma - 5;
        cantidad5 = cantidad5 - 1;
        EEPROM.write (5, cantidad5);
      }
  }
void loop()
  { 
    switch (Estado)
      {
        case 0:

          Lectura_de_5cent(); //Lee si se ha introducido una moneda de 5 céntimos
          Lectura_de_10cent(); //Lee si se ha introducido una moneda de 10 céntimos
          Lectura_de_20cent(); //Lee si se ha introducido una moneda de 20 céntimos
          Lectura_de_50cent(); //Lee si se ha introducido una moneda de 50 céntimos
          Lectura_de_1euro(); //Lee si se ha introducido una moneda de 1 euro
          Lectura_de_2euros(); //Lee si se ha introducido una moneda de 2 euros

          if (suma > 0) { Estado = 1; }
        
        break;

        case 1:

          Dispensa_Producto_1(); //Reconoce y en caso de pedrise dispensa el producto denominado 1
          Dispensa_Producto_2(); //Reconoce y en caso de pedrise dispensa el producto denominado 2
          Dispensa_Producto_3(); //Reconoce y en caso de pedrise dispensa el producto denominado 3
          Dispensa_Producto_4(); //Reconoce y en caso de pedrise dispensa el producto denominado 4
          Boton_Devolucion(); //Reconoce y en caso de pedrise devuelve el dinero introducido (no las mismas monedas, solo el mismo valor)
          Estado = 0;

        break;
      }
  }