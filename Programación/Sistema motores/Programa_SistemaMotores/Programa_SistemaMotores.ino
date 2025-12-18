#define pincon 12 // Pin de conexión entre arduinos
#define pindin 2 // Pin de conexión entre arduinos, se activa en caso de que el dinero necesario para dispensar un producto se haya metido
#define bit1 3 // Pin del bit uno
#define bit2 4 // Pin del bit dos
#define bit3 5 // Pin del bit tres
#define detector 6 // Pin de la fotocélula
int estadocon = 0; // Variable pin de conexión entre arduinos
int estadodin = 0; // Variable pin de conexión entre arduinos, se activa en caso de que el dinero necesario para dispensar un producto se haya metido
int estadobit1 = 0; // Variable pin del bit uno
int estadobit2 = 0; // Variable pin del bit dos
int estadobit3 = 0; // Variable pin del bit tres
int estadodet = 0; // Variable pin de la fotocélula

#define motor1 7 // Pin motor 1
#define motor2 8 // Pin motor 2
#define motor3 9 // Pin motor 3
#define motor4 10 // Pin motor 4

int Switch = 0; // Variable de selección de producto

void setup() 
  {
    //Inputs
    pinMode (pincon, INPUT_PULLUP);
    pinMode (pindin, INPUT_PULLUP);
    pinMode (bit1, INPUT_PULLUP);
    pinMode (bit2, INPUT_PULLUP);
    pinMode (bit3, INPUT_PULLUP);
    pinMode (detector, INPUT_PULLUP);

    digitalWrite (pincon, HIGH);
    digitalWrite (pindin, HIGH);
    digitalWrite (bit1, HIGH);
    digitalWrite (bit2, HIGH);
    digitalWrite (bit3, HIGH);
    digitalWrite (detector, HIGH);

    estadocon = 1;
    estadodin = 1;
    estadobit1 = 1;
    estadobit2 = 1;
    estadobit3 = 1;
    estadodet = 1;

    //Outputs
    pinMode (motor1, OUTPUT);
    pinMode (motor2, OUTPUT);
    pinMode (motor3, OUTPUT);
    pinMode (motor4, OUTPUT);

    digitalWrite (motor1, LOW);
    digitalWrite (motor2, LOW);
    digitalWrite (motor3, LOW);
    digitalWrite (motor4, LOW);

    //Switch
    Switch = 0;
  }

void loop() 
  {
    // Lectura de variables
    estadocon = digitalRead (pincon); 
    estadodin = digitalRead (pindin); 
    estadobit1 = digitalRead (bit1);
    estadobit2 = digitalRead (bit2);
    estadobit3 = digitalRead (bit3);
    estadodet = digitalRead (detector);

    // Cepo de seguridad, para el caso en donde los dos arduinos no estén conectados entre si
    while (digitalRead (pincon) == HIGH); 

    //Selección de producto a dispensar    
    if (estadodin == LOW)
      {
        if (estadobit1 == LOW)
          {
            if (estadobit2 == HIGH && estadobit3 == HIGH)
              {
                Switch = 1;
              }
            if (estadobit2 == LOW && estadobit3 == HIGH)
              {
                Switch = 3;
              }
          }
            
        if (estadobit1 == HIGH)
          {
            if (estadobit2 == LOW && estadobit3 == HIGH)
              {
                Switch = 2;
              }
            if (estadobit2 == HIGH && estadobit3 == LOW)
              {
                Switch = 4;
              }
          }
      }

    switch (Switch)
      {
        case 1: // Dispensa el producto del botón 1
          estadodet = digitalRead (detector);

          if (estadodet == LOW)
            {
              digitalWrite (motor1, HIGH);
              digitalWrite (motor2, LOW);
              digitalWrite (motor3, LOW);
              digitalWrite (motor4, LOW);
            }

          else
            {
              digitalWrite (motor1, LOW);
              estadobit1 = 1;
              estadodin = 1;
              Switch = 0;
            }

        break; // Termina el caso 1

        case 2: // Dispensa el producto del botón 2
          estadodet = digitalRead (detector);

          if (estadodet == LOW)
            {
              digitalWrite (motor1, LOW);
              digitalWrite (motor2, HIGH);
              digitalWrite (motor3, LOW);
              digitalWrite (motor4, LOW);
            }

          else 
            {
              digitalWrite (motor2, LOW);
              estadobit2 = 1;
              estadodin = 1;
              Switch = 0;
            }

        break; // Termina el caso 2

            case 3: // Dispensa el producto del botón 3

              estadodet = digitalRead (detector);

              if (estadodet == LOW)
              {
                digitalWrite (motor1, LOW);
                digitalWrite (motor2, LOW);
                digitalWrite (motor3, HIGH);
                digitalWrite (motor4, LOW);
              }

              else
                {
                  digitalWrite (motor3, LOW);
                  estadobit1 = 1;
                  estadobit2 = 1;
                  estadodin = 1;
                  Switch = 0;
                }
        break; // Termina el caso 3

        case 4: // Dispensa el producto del botón 4

          estadodet = digitalRead (detector);

          if (estadodet == LOW)
            {
              digitalWrite (motor1, LOW);
              digitalWrite (motor2, LOW);
              digitalWrite (motor3, LOW);
              digitalWrite (motor4, HIGH);
            }

          else
            {
              digitalWrite (motor4, LOW);
              estadobit3 = 1;
              estadodin = 1;
              Switch = 0;
            }

        break; // Termina el caso 4

        default: // Casos que no nos interesan

            digitalWrite (motor1, LOW);
            digitalWrite (motor2, LOW);
            digitalWrite (motor3, LOW);
            digitalWrite (motor4, LOW);
        
        break; // Fin de casos que no nos interesan
      }
  }