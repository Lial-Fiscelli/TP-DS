#include <Servo.h>  //Appel de la librairie "SERVO"
const int trigPin = 7; // Trigger (emission) 
const int echoPin = 6; // Echo (réception) 
// Variables utiles 
long duree; // durée de l'echo 
int distance; // distance 



Servo myservo;  // Crée l'objet SERVO pour controler le SERVOMOTEUR 
int pos = 0;    // variable qui enregistre la position du SERVO 
// définition des bornes d'entrée et sortie
const int rouge = 3;   //La led rouge est connectée à la PIN 3 
const int verte = 4;   //La led verte est connectée à la PIN 4
const int servo = 9;  //Le servo est connecté à la PIN 9

void setup() {
  myservo.attach(servo);
  pinMode(rouge, OUTPUT); // Défintion des entrées/sorties 
  pinMode(verte, OUTPUT);
  pinMode(trigPin, OUTPUT); // Configuration du port du Trigger comme une SORTIE 
  pinMode(echoPin, INPUT); // Configuration du port de l'Echo comme une ENTREE
  Serial.begin(9600);
}

void loop() {
  // On initialise dés le début l'état des led
  digitalWrite(rouge, HIGH);
  digitalWrite(verte, LOW);
  
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(10);
  // Écoute de l'écho 
  duree = pulseIn(echoPin, HIGH); 
  // Calcul de la distance 
  distance = duree*0.035/2; 
  // Affichage de la distance dans le Moniteur Série 
  Serial.print("Distance : "); 
  Serial.print(distance); 
  Serial.println("cm"); 
  delay(500);

  
  if (distance <=20) {    // si bouton appuyé, alors on lève la barrière et on fait changer l'état des led, sinon, on reboucle
    
    for (pos = 0; pos <= 90; pos += 1) { // on commence à actionner dans un sens la barrière, jusqu'à 90°, degrè par degrè
      myservo.write(pos);              // va à la position "POS"
      delay(15);                       // attends 15ms avant de changer la position de la barrière d'1 degrè
    }
    // la barrière est levée, on peut allumer la led verte et éteindre la rouge
    digitalWrite(verte, HIGH);
    digitalWrite(rouge, LOW);

    delay(5000); // Attends 5 secondes
    // La led rouge s'allume et on éteind la verte
    digitalWrite(rouge, HIGH);
    digitalWrite(verte, LOW);
    //On referme ensuite la barrière
    for (pos = 90; pos >= 0; pos -= 1) { // cette fois si, on passe de 90° à 0° (décroit à chaque fois de -1)
      myservo.write(pos);              // va à la position "POS"
      delay(15);                       // attends 15ms avant de changer la position de la barrière d'1 degrè
    }
  }
}
