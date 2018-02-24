
//Melodia01 - Quando for ligado a bomba de agua.
int melodia[] = {660,660,660,510,660,770,380};
int duracaodasnotas[] = {100,100,100,100,100,100,100};
int pausadepoisdasnotas[] = {150,300,300,100,300,550,575};

//Melodia02 - Quando não ha agua no reservatorio.
int melodia2[] = {523,523,523,494,440,392};
int duracaodasnotas2[] = {100,100,70,70,70,70};
int pausadepoisdasnotas2[] = {300,200,200,200,200,200};

//Pino que será conectado o alto-falante.
int portSpeak(3);

int pino2=2; //Pino de conexão da bomba dagua.
int pino4=4; //Pino do Led que indica quando o reservatorio está vazio.
int pino5=5; //Pino do sensor de umidade da planta.
int pino6=6; //Pino do sensor do reservatorio de agua.

// Meu limite de umidade, se tiver acima de 300 a planta ja está regando caso ao contrario continui regando até chegar a 300.
int limiteUmidade = 300; 
//Limite do meu Reservatorio, o led vermelho será acionado se o limite estiver abaixo do valor da variavel.
int limiteReserv = 350; 
int sensorVaso;
//Guarda o valor do reservatorio.
int sensorReserv;

void setup() {
  // put your setup code here, to run once:
  //Inicialização da serial.
  Serial.begin(9600);
  pinMode(pino2,OUTPUT);//Bomba de agua.
  pinMode(pino4,OUTPUT);//Led do reservatorio.
  pinMode(pino5,OUTPUT);//Alimentação sensor 1.
  pinMode(pino6,OUTPUT);//Alimentação sensor 2.

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVaso = leSensorVaso();//É guardado a leitura do sensor do Vaso.
  sensorReserv = leSensorReserv();//É guardado a leitura do sensor do Resevatorio.

  Serial.print("sensor vaso ");
  Serial.print(sensorVaso);
  Serial.println("");
  Serial.print("sensor reservatorio ");
  Serial.print(sensorReserv);
  Serial.println("");

  delay(10);

  // Verifico se ha agua suficiente no reservatorio
  if (sensorReserv < limiteReserv) {
    //Função para ligar o LED do reservatorio.
    ligaLedReserv();
    //Função tocar Musica.
    tocaMusica(2);
  }
  //Enquanto não tiver agua suficiente no reservatorio ele vai ficar dentro do while.
  //Enquanto meu reservatorio estiver vazio
  while (leSensorReserv() < limiteReserv) {
    delay(1000);//delay de um seguno
    Serial.println(leSensorReserv());
    //Mudar delay para fazer a leitura de 5hs em 5hs (18000000)
    delay(5000); //verificação a cada cinco segundos.
  }
  //Apos colocar agua no reservatorio o led desliga.
  desligaLedReserv(); 

  // verificar se a plantinha precisa de agua
  if(leSensorVaso() < limiteUmidade) {
    tocaMusica(1);
    ligaBomba();
    Serial.println("liga a bomba dagua");
  }
  //Se o vaso está com a terra seca e precisa de água && verigicação de água no reservatorio.
  while(leSensorVaso() < limiteUmidade && leSensorReserv() > limiteReserv) {
    delay(1000);
    Serial.print("Terra seca, valor: ");
    Serial.println(leSensorVaso());
  }
  desligaBomba();

  Serial.println("----- fim loop -----");

  //Mudar delay para fazer a leitura de 5hs em 5hs (18000000)
  delay(1000);
}
//Função ler sensor do vaso.
int leSensorVaso() {
  ligaSensores();//Liguei meu sensor.
  delay(10);//esperei 10 milisegundos.
  return analogRead(A0);//Retornei o valor para função.
  desligaSensores();//Desligar meu sensor. 
}
 //Função ler sensor reservatório.
int leSensorReserv() {
  ligaSensores(); //Liguei meu sensor.
  delay(10);//esperei 10 milisegundos.
  return analogRead(A1);//Retornei o valor para função.
  desligaSensores();//Desligar meu sensor. 
}
 //Essa função não vai voltar nada é só para ligar os sensores.
void ligaSensores() {
  digitalWrite(pino5,HIGH);
  digitalWrite(pino6,HIGH);
  Serial.println("Sensores ativados!");
}
 //Desligar sensores.
void desligaSensores() {
  digitalWrite(pino5,LOW);
  digitalWrite(pino6,LOW);
  Serial.println("Sensores desativados!");
}
 //Acender o Led vermelho do reservatório quando ele tiver vazio.
void ligaLedReserv() {
  digitalWrite(pino4,HIGH);//Led do reservatorio.
  Serial.println("Reservatorio vazio");
}
void desligaLedReserv() {
  digitalWrite(pino4,LOW);//Led do reservatorio.
  Serial.println("Reservatorio cheio");
}
//Função para chavear um transistor e ligar a bomba dagua.
void ligaBomba() {
  digitalWrite(pino2,HIGH);
  Serial.println("bomba ligada");
}
//Função para chavear um transistor e desligando a bomba dagua.
void desligaBomba() {
  delay(2000);
  digitalWrite(pino2,LOW);
  Serial.println("bomba desligada");
}

 //Função toca musica
void tocaMusica(int musica) {
  switch (musica) {
    case 1:
    //quanto a nota for menor que 7, execute o bloco de codigo que tiver no for.
    for (int nota=0; nota < 7; nota++) {
      //A função tone é responsavel por jogar a frequencia(variavel definida) no pino do alto-falante.
      tone(portSpeak, melodia[nota], duracaodasnotas[nota]);
      delay(pausadepoisdasnotas[nota]);
    }
    Serial.println("musica 1");
     //noTone é responsavel por desligar o alto-falante.
    noTone(portSpeak);
    break;
    
    case 2:
    //quanto a nota for menor que 6, execute o bloco de codigo que tiver no for.
    for (int nota=0; nota < 6; nota++) {
      //A função tone é responsavel por jogar a frequencia(variavel definida) no pino do alto-falante.
      tone(portSpeak, melodia2[nota], duracaodasnotas2[nota]);
      delay(pausadepoisdasnotas2[nota]);
    }
    Serial.println("musica 2");
     //noTone é responsavel por desligar o alto-falante.
    noTone(portSpeak);
    break;
  }
}

