#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "leds.h"
#include "color.h"

const uint8_t PixelCount = 93;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266
const char* SSID = "SPOTLIGHTv2";
const char* PASSWORD = "#cccamp.2023";

Effect lightEffect = Effect::Outwards;
RgbColor color = ROSE;
unsigned long speedMs = 1000;
LEDs light(PixelCount, PixelPin);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Spotlight control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
  </style>
</head>
<body>
  <h2>Spotlight Control</h2>
  %COLORPLACEHOLDER%
  %EFFECTPLACEHOLDER%
  %SPEEDPLACEHOLDER%
<script>
function watchEffectButtons(element) {
  sendData("effect",element.value);
}
function watchColorPicker(element) {
  sendData("color",element.value);
}
function watchRangeSlider(element) {
  sendData("speed",element.value);
}

function sendData(key, value) {
  let formData = new FormData();
  formData.append(key, value);
  
  let xhr = new XMLHttpRequest();
  xhr.open("POST", "/action");
  xhr.send(formData);
}
</script>
</body>
</html>
)rawliteral";

String getSpeed() {
  return String(speedMs, 10);
}


String processor(const String& var){
  //Serial.println(var);
    String result = "";

    if(var == "COLORPLACEHOLDER") {
        result += "<h4>Animation Color</h4>";
        result += "<input type=\"color\" id=\"color\" name=\"color\" value=\"#" + Color::rgbToHex(color) + "\" onchange=\"watchColorPicker(this)\" /><label for=\"color\">Base Color</label>";
    }
    if(var == "EFFECTPLACEHOLDER"){
        result += "<h4>Animation Effect</>";
        result += "<div class=\"button\"><button class=\"effect\" onclick=\"watchEffectButtons(this)\" value=\"0\" >Inwards</Button></div>";        
        result += "<div class=\"button\"><button class=\"effect\" onclick=\"watchEffectButtons(this)\" value=\"1\" >Outwards</Button></div>";
    }
    if(var == "SPEEDPLACEHOLDER") {
        result += "<h4>Animation Speed</h4>";
        result += "<input type=\"range\" id=\"speed\" name=\"speed\" min=\"100\" max=\"1500\" step=\"50\" value=\"" + getSpeed() + "\" onchange=\"watchRangeSlider(this)\" /><label for=\"speed\">Animation</label>";
    }
    return result;
}

//TODO: Security? On my embedded device? (⊙＿⊙')
void postAction(AsyncWebServerRequest *request) {
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }

  if(request->hasParam("effect", true)) {
      Serial.println("Effect");
      AsyncWebParameter* p = request->getParam("effect", true);
      Serial.println(p->value().toInt());
      light.setEffect((Effect)p->value().toInt()); 
  }

  if(request->hasParam("color", true)) {
      Serial.println("Color");
      AsyncWebParameter* p = request->getParam("color", true);
      Serial.println(p->value());
      light.setColor(Color::hexToRgb(p->value()));
  }

  if(request->hasParam("speed", true)) {
      Serial.println("Speed");
      AsyncWebParameter* p = request->getParam("speed", true);
      Serial.println(p->value());
      light.setSpeed(strtoul(p->value().begin(),NULL,10));
  }

  request->send_P(200, "text/html", index_html);
}

void setup()
{          
    Serial.begin(115200);
    while (!Serial); // wait for serial attach  

    Serial.printf("setting up");
    light.init(color,lightEffect,speedMs);
    light.printTopo();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(SSID, PASSWORD);
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
    });
    server.on("/action", HTTP_POST, postAction);
    
    server.begin();
 }

void loop()
{
    light.runEffect();
 }