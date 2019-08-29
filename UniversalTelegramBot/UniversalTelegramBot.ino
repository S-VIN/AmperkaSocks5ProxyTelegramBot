#include <UniversalTelegramBot.h>
#include <Socks5Proxy.h>

char ssid[] = "Amperka";     // your network SSID (name)
char password[] = "mega2560"; // your network key

// Initialize Telegram BOT
#define BOTtoken "954847022:AAHZDWrHM0nOpGfJNDfbvLty2HaUO5RqAX4"  // your Bot Token (Get from Botfather)
IPAddress proxyIP(166, 62, 91, 254);
	
WiFiClientSecure Client;
Socks5Proxy ProxyClient(proxyIP, 14718, Client);


UniversalTelegramBot bot(BOTtoken, ProxyClient);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) {
        bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}