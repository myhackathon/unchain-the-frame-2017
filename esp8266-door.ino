#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "WifiConf.h"

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(13, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
 
  WiFi.begin(WIFI_SSID, WIFI_PSK);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
 
  if (request.indexOf("/Lock1on") > 0)  {
    digitalWrite(5, HIGH);
   
  }
  if (request.indexOf("/Lock11off") >0)  {
    digitalWrite(5, LOW);
   
  }
   if (request.indexOf("/Lock2on") > 0)  {
    digitalWrite(4, HIGH);
   
  }
  if (request.indexOf("/Lock2off") >0)  {
    digitalWrite(4, LOW);
   
  }
    if (request.indexOf("/Lock3on") >0)  {
    digitalWrite(0, HIGH);
   
  }
  if (request.indexOf("Lock33off") > 0)  {
    digitalWrite(0, LOW);
   
  }
   if (request.indexOf("/Lock4On") > 0)  {
    digitalWrite(13, HIGH);
   
  }
  if (request.indexOf("/Lock4Off") > 0)  {
    digitalWrite(13, LOW);
   
  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
 client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> Charitytrails Lock Control </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lock 1");
  client.println("<a href=\"/Lock1On\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Lock1Off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
   client.println("<center>");
   client.println("Lock 2");
  client.println("<a href=\"/Lock2On\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Lock2Off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
    client.println("<center>");
   client.println("Lock 3");
  client.println("<a href=\"/Lock3On\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Lock3Off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
   client.println("<center>");
   client.println("Lock 4");
  client.println("<a href=\"/Lock4On\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Lock4Off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
 client.println("<tr>");
  if (digitalRead(5))
         { 
           client.print("<td>Lock 1 is ON</td>");
        
         }
          else
          {
            client.print("<td>Lock 1 is OFF</td>");
      
        }
     
        client.println("<br />");
             
         if (digitalRead(4))
          { 
           client.print("<td>Lock 2 is ON</td>");
         }
          else
          {
            client.print("<td>Lock 2 is OFF</td>");
          }
          client.println("</tr>");
          client.println("<tr>");
          if (digitalRead(0))
          { 
           client.print("<td>Lock 3 is ON</td>");
          }
          else
          {
            client.print("<td>Lock 3 is OFF</td>");
          }
          if (digitalRead(13))
          { 
           client.print("<td>Lock 4 is ON</td>");
          }
          else
          {
            client.print("<td>Lock 4 is OFF</td>");
          }
          client.println("</tr>");
          client.println("</table>");
          client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
