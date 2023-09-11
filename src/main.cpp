#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "leds.h"
#include "color.h"

const uint8_t PixelCount = 93;
const uint8_t PixelPin = 25; // make sure to set this to the correct pin, ignored for Esp8266
const char *SSID = "SPOTLIGHTv2";
const char *PASSWORD = "#cccamp.2023";

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
    <style>html{font-family:Arial;display:inline-block;text-align:center}h2{font-size:24px}h4{font-size:16px}div.col{margin:10px}body{max-width:600px;margin:0 auto;padding-bottom:25px}.button{background-color:#add8e6;margin: 0px 5px;border:none;text-align:center;text-decoration:none;display:inline-block;color:#2f4f4f;font-size:16px;padding:10px 18px;opacity:.7}.button:hover{opacity:1}.label-right{margin-right:5px;display:block}.color{-webkit-appearance:none;-moz-appearance:none;appearance:none;background-color:transparent;width:75px;height:75px;border:none;cursor:pointer}.color::-webkit-color-swatch{border-radius:50%%}.color::-moz-color-swatch{border-radius:50%%}.slider{-webkit-appearance:none;width:50%%;height:20px;background:#add8e6;outline:0;opacity:.7;-webkit-transition:.2s;transition:opacity .2s}.slider:hover{opacity:1}.slider::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:22px;height:22px;background:#2f4f4f;cursor:pointer;border:1px solid #000}.slider::-moz-range-thumb{width:22px;height:22px;background:#2f4f4f;cursor:pointer;border:1px solid #000}</style>
    <script>function watchEffectButtons(element) {sendData("effect", element.value);}function watchColorPicker(element) {sendData("color", element.value);}function watchRangeSlider(element) {sendData("speed", element.value);}function sendData(key, value) {let formData = new FormData();formData.append(key, value);let xhr = new XMLHttpRequest();xhr.open("POST", "/action");xhr.send(formData);}</script>
</head>
<body>
    <h2>Spotlight Control</h2>
    %COLORPLACEHOLDER%
    %EFFECTPLACEHOLDER%
    %SPEEDPLACEHOLDER%
</body>
</html>
)rawliteral";

String processor(const String &var)
{
  // Serial.println(var);
  String result = "";

  if (var == "COLORPLACEHOLDER")
  {
    result += "<h4>Animation Color</h4><div class=\"col\"><input type=\"color\" id=\"color\" name=\"color\" value=\"#";
    result += Color::rgbToHex(color);
    result += "\" class=\"color\" onchange=\"watchColorPicker(this)\" /></div>";
  }
  if (var == "EFFECTPLACEHOLDER")
  {
    result += "<h4>Animation Effect</h4><div class=\"col\">";
    result += "<button class=\"button\" onclick=\"watchEffectButtons(this)\" value=\"0\">Inwards</Button>";
    result += "<button class=\"button\" onclick=\"watchEffectButtons(this)\" value=\"1\">Outwards</Button>";
    result += "</div>";
  }
  if (var == "SPEEDPLACEHOLDER")
  {
    result += "<h4>Animation Speed</h4><div class=\"col\"><input type=\"range\" id=\"speed\" name=\"speed\" min=\"100\" max=\"1500\" step=\"50\" value=\"";
    //result += String(speedMs, 10);
    result += speedMs;
    result += "\" class=\"slider\" onchange=\"watchRangeSlider(this)\" /></div>";
  }
  return result;
}

// TODO: Security? On my embedded device? (⊙＿⊙')
void postAction(AsyncWebServerRequest *request)
{
  int params = request->params();
  for (int i = 0; i < params; i++)
  {
    AsyncWebParameter *p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }

  if (request->hasParam("effect", true))
  {
    Serial.println("Effect");
    AsyncWebParameter *p = request->getParam("effect", true);
    Serial.println(p->value().toInt());
    light.setEffect((Effect)p->value().toInt());
  }

  if (request->hasParam("color", true))
  {
    Serial.println("Color");
    AsyncWebParameter *p = request->getParam("color", true);
    Serial.println(p->value());
    light.setColor(Color::hexToRgb(p->value()));
  }

  if (request->hasParam("speed", true))
  {
    Serial.println("Speed");
    AsyncWebParameter *p = request->getParam("speed", true);
    Serial.println(p->value());
    light.setSpeed(strtoul(p->value().begin(), NULL, 10));
  }

  request->send_P(200, "text/html", index_html);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial attach

  Serial.printf("setting up");
  light.init(color, lightEffect, speedMs);
  light.printTopo();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, PASSWORD);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
  server.on("/action", HTTP_POST, postAction);

  server.begin();
}

void loop()
{
  light.runEffect();
}