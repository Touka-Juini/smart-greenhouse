const int capteur_tube_pin = 10;
const int capteur_niveaubas_pin = 2;
const int capteur_niveauhaut_pin = 3;
const int relais_pin = 7;
const int duree_pompe = 10;

void setup() {
//initialisation des pins
pinMode (capteur_tube_pin,INPUT)      ;
pinMode (capteur_niveaubas_pin,INPUT) ;
pinMode (capteur_niveauhaut_pin,INPUT);
pinMode (relais_pin,OUTPUT)           ;
//initialisation la pompe a off
digitalWrite(relais_pin,LOW)          ;
Serial.begin(9600)                    ;
}

void loop() {
int niveau_tube = analogRead (capteur_tube_pin)      ;
int niveau_haut = analogRead (capteur_niveauhaut_pin);
int niveau_bas  = analogRead (capteur_niveaubas_pin) ;
if(niveau_tube<100)
{ if((niveau_haut==1 && niveau_bas==1 ) || (niveau_haut==0 && niveau_bas==1))
{digitalWrite(relais_pin,HIGH);
 delay(duree_pompe);
 digitalWrite(relais_pin,LOW);
}else {Serial.println('citerne vide_pompe desactivé');}
}
delay(300000); //attend 5 mins entre chaque lecture
}
