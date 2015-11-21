#include <SoftwareSerial.h>

#define DEBUG true
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

SoftwareSerial esp8266(10,11);
char a;
int flag=0,temp;
float tempc;

void setup()
{
  Serial.begin(115200);
  esp8266.begin(115200);
  sensors.begin();

  pinMode (4,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (6,OUTPUT);

  sendCommand("AT+RST\r\n",2000,DEBUG);
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG);
  sendCommand("AT+CWJAP=\"TP-LINK_40D216\",\"36780389\"\r\n",3000,DEBUG);
  delay(1000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG);
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG);
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG);

  Serial.println("Server Ready");
  
  
}

void loop()
{
  if(esp8266.available())
  {
    if(esp8266.find("+IPD,"))
    {
      delay(1000);
      int connectionId = esp8266.read()-48;

      esp8266.find("func=");

      a = esp8266.read();

      if(a == '0')
      digitalWrite(4,LOW);
      if(a == '1')
      digitalWrite(5,LOW);
      if(a == '2')
      digitalWrite(6,LOW);
      flag=1;
      if(a == '3')
      flag = 2;
      if(a == '4')
      {
        analogRead(0);
      }
      flag = 3;

      sendHTTPResponse(connectionId,flag);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand+=connectionId;
      closeCommand+="\r\n";

      sendCommand(closeCommand,1000,DEBUG);

      
    }
  }
   sensors.requestTemperatures();
 tempc = sensors.getTempCByIndex(0);
 temp = (int)tempc;
 
}

String sendData(String command,const int timeout, boolean debug)
{
  String response = "";

  int dataSize = command.length();
  char data[dataSize];
  command.toCharArray(data,dataSize);

  esp8266.write(data,dataSize); 
  if(debug)
  {
    Serial.println("Response from arduino>>>>");
    Serial.write(data,dataSize);
  }
  long int time = millis();

  while((time+timeout) > millis())
  {
    while(esp8266.available())
    {
      char c = esp8266.read();
      response+=c;
    }
  }
  if(debug)
  {
    Serial.print(response);
  }
  return response;
}

void sendHTTPResponse(int connectionId, int res)
{
  String httpResponse;
  String httpHeader;
  String content;
  if(res == 1)
  {
    content = "OK";
  }
  if(res == 2)
  {
   content = String(temp);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }
  
  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
  httpHeader += "Content-Length";
  httpHeader += content.length();
  httpHeader += "\r\n";
  httpHeader = " Connection: close\r\n\r\n";
  httpResponse = httpHeader + content + " " ;
  sendCIPData(connectionId,httpResponse);
  
}

void sendCIPData(int connectionId,String data)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += data.length();
  cipSend += "\r\n";
  sendCommand(cipSend,1000,DEBUG);
  sendData(data,1000,DEBUG);
  
}

String sendCommand(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time= millis();

  while((time +timeout) > millis())
  {
    while(esp8266.available())
    {
    char c = esp8266.read();
    response += c;
    }
  }
  if(debug)
  Serial.print(response);
  return response;
}

