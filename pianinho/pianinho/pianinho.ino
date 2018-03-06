
// define as notas musicais 
int DO = 262;
int RE = 294;
int MI = 329;
int FA = 349;
int SOL = 392;
int LA = 440;
int SI = 494;

//Uma array com todas as notas.
int notas[7] = {DO,RE,MI,FA,SOL,LA,SI};

void setup() {
  // put your setup code here, to run once:
  //Definido od pinos
  for (int i=2; i<9; i++) {
      pinMode(i,INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i=2; i<9; i++) {
    
    //Enquanto meu botão estiver com valor diferente de HIGH ele vai executar um bloco de codigo que vai tocar uma nota;
    while (digitalRead(i) != HIGH) {
      tone(12, notas[i-2]);
    }
    //Desligar o buzzer
    noTone(12);
  }

}
