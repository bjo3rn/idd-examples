/*
 IDD - RedBear Duo Ping Example
 
 This example connects to a WPA2-encrypted Wifi network.
 Then it prints the MAC address of the Duo Board
 the IP address obtained, and other network details.
 It then tries to ping 8.8.8.8 (Google DNS) and prints the results of the ping.
  
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 2 July 2014
 by Noah Luskey
 modified 1 DEC 2015
 by Jackson Lv
 modified 10 OCT 2016
 by Bjoern
 */
 
/*
 * SYSTEM_MODE:
 *     - AUTOMATIC: Automatically try to connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     - SEMI_AUTOMATIC: Manually connect to Wi-Fi and the Particle Cloud, but automatically handle the cloud messages.
 *     - MANUAL: Manually connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     
 * SYSTEM_MODE(AUTOMATIC) does not need to be called, because it is the default state. 
 * However the user can invoke this method to make the mode explicit.
 * Learn more about system modes: https://docs.particle.io/reference/firmware/photon/#system-modes .
 */
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif
STARTUP(WiFi.selectAntenna(ANT_EXTERNAL)); // selects the u.FL antenna

///// CONFIGURATION - EDIT THIS BLOCK /////
// your network name also called SSID
char ssid[] = "idd";
// your network password (key)
char password[] = "iddfall16";
IPAddress pingAddress(8,8,8,8);
///////////////////////////////////////////


void printWifiData();
void printCurrentNet();
void printPing();

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 

  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.on();
  WiFi.setCredentials(ssid,password);
  WiFi.connect();
  
  while ( WiFi.connecting()) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  IPAddress localIP = WiFi.localIP();
  while (localIP[0] == 0) {
    localIP = WiFi.localIP();
    Serial.println("waiting for an IP address");
    delay(1000);
  }
  
  
  Serial.println("\nIP Address obtained");
  
  // you're connected now, so print out the status  
  printCurrentNet();
  printWifiData();
}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
  printPing(); 
  
}

void printPing() {
  int tries = 5;
  int received = WiFi.ping(pingAddress,tries);
  Serial.print("Pinged: ");
  Serial.println(pingAddress);
  Serial.print("Tries: ");
  Serial.print(tries);
  Serial.print("; Responses: ");
  Serial.println(received);
}

void printWifiData() {
  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  //print gateway IP address
  IPAddress gatewayip = WiFi.gatewayIP();
  Serial.print("Gateway IP: ");
  Serial.println(gatewayip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  Serial.print("Encryption Type:");
  Serial.println(WPA, HEX);
  Serial.println();
}

