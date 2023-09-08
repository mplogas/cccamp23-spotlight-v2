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
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>Spotlight Control</h2>
  %COLORPLACEHOLDER%
  %EFFECTPLACEHOLDER%
<script>function watchEffectButtons(element) {
  var effect = element.value;
  let formData = new FormData();
  formData.append("effect", effect);

  // send it out
  let xhr = new XMLHttpRequest();
  xhr.open("POST", "/action");
  xhr.send(formData);
}
function watchColorPicker(element) {
  var color = element.value;
  let formData = new FormData();
  formData.append("color", color);

  // send it out
  let xhr = new XMLHttpRequest();
  xhr.open("POST", "/action");
  xhr.send(formData);
}
</script>
</body>
</html>
)rawliteral";


// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
    String result = "";

    if(var == "COLORPLACEHOLDER") {
        result += "<h4>Basecolor</h4>";
        result += "<label class=\"color\"><input name=\"color\" value=\"#" + Color::rgbToHex(color) + "\" type=\"color\" onchange=\"watchColorPicker(this)\"></label> ";
    }
    if(var == "EFFECTPLACEHOLDER"){
        result += "<h4>Effects</>";
        result += "<label class=\"button\"><button class=\"effect\" onclick=\"watchEffectButtons(this)\" value=\"0\" >Inwards</Button></label>";
        result += "<label class=\"button\"><button class=\"effect\" onclick=\"watchEffectButtons(this)\" value=\"1\" >Outwards</Button></label>";
    }
    return result;
}

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

    request->send_P(200, "text/html", index_html);
    }

void setup()
{          
    Serial.begin(115200);
    while (!Serial); // wait for serial attach  

    Serial.printf("setting up");
    light.init(color,lightEffect);
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
    light.runEffect(250);
 }