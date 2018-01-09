#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>


ESP8266WebServer webServer(80);
void fade(int pin);
void testRGB();
void fading();
void stripOff ();
void fadered ();
void fadeblue();
void fadegreen();
bool fader = 1;

String webpage = ""
"<!DOCTYPE html><html><head><title>RGB Traka by A.Ajdin</title><meta name='mobile-web-app-capable' content='yes' />"
"<meta name='viewport' content='width=device-width' /></head><body style='margin: 0px; padding: 0px;'>"
//DIO GDJE SE MOZE IMPLEMENTIRATI


"<canvas id='colorspace'></canvas>"
"</body>"
"<script type='text/javascript'>"
"(function () {"
" var canvas = document.getElementById('colorspace');"
" var ctx = canvas.getContext('2d');"
" function drawCanvas() {"
" var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);"
" for(var i=0; i <= 360; i+=10) {"
" colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');"
" }"
" ctx.fillStyle = colours;"
" ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);"
" var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);"
" luminance.addColorStop(0, '#ffffff');"
" luminance.addColorStop(0.05, '#ffffff');"
" luminance.addColorStop(0.5, 'rgba(0,0,0,0)');"
" luminance.addColorStop(0.95, '#000000');"
" luminance.addColorStop(1, '#000000');"
" ctx.fillStyle = luminance;"
" ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);"
" }"
" var eventLocked = false;"
" function handleEvent(clientX, clientY) {"
" if(eventLocked) {"
" return;"
" }"
" function colourCorrect(v) {"
" return Math.round(1023-(v*v)/64);"
" }"
" var data = ctx.getImageData(clientX, clientY, 1, 1).data;"
" var params = ["
" 'r=' + colourCorrect(data[0]),"
" 'g=' + colourCorrect(data[1]),"
" 'b=' + colourCorrect(data[2])"
" ].join('&');"
" var req = new XMLHttpRequest();"
" req.open('POST', '?' + params, true);"
" req.send();"
" eventLocked = true;"
" req.onreadystatechange = function() {"
" if(req.readyState == 4) {"
" eventLocked = false;"
" }"
" }"
" }"
" canvas.addEventListener('click', function(event) {"
" handleEvent(event.clientX, event.clientY, true);"
" }, false);"
" canvas.addEventListener('touchmove', function(event){"
" handleEvent(event.touches[0].clientX, event.touches[0].clientY);"
"}, false);"
" function resizeCanvas() {"
" canvas.width = window.innerWidth;"
" canvas.height = window.innerHeight;"
" drawCanvas();"
" }"
" window.addEventListener('resize', resizeCanvas, false);"
" resizeCanvas();"
" drawCanvas();"
" document.ontouchmove = function(e) {e.preventDefault()};"
" })();"
"</script>"
"</html>";
//////////////////////////////////////////////////////////////////////////////////////////////////
void handleRoot() {
//uzmi argumente canvasa
String red = webServer.arg(0);
String green = webServer.arg(1);
String blue = webServer.arg(2);
analogWrite(16, red.toInt());
analogWrite(5, green.toInt());
analogWrite(4, blue.toInt());
webServer.send(200, "text/html", webpage);
fader = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
//PRIPREMI PINOVE
pinMode(16, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);

analogWrite(16, 1023);
analogWrite(5, 1023);
analogWrite(4, 1023);
delay(1000);
//SPOJI SE NA MREZU
WiFi.begin("Ahmetovic", "guliver159753");
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to ");
  Serial.print("ssid");
}
Serial.println("ssid");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());


webServer.on("/", handleRoot);
webServer.begin();

testRGB();


//HANDLER ZA SVAKI BUTTON
webServer.on("/gasitraku", [](){
  webServer.send(200, "text/html", webpage);
  stripOff();
  delay(1000);
  fader = 1;
});

webServer.on("/fadergb", [](){
  webServer.send(200, "text/html", webpage);
  while (fader){
  fading();
  webServer.handleClient();
  webServer.on("/offset", [](){
    fader = 0;
    delay(1000);
  });
  webServer.handleClient();
  //fader = 1;
}
  delay(1000);
});

webServer.on("/fadered", [](){
  webServer.send(200, "text/html", webpage);
  while (fader){
  fadered();
  webServer.handleClient();
  webServer.on("/offset", [](){
    fader = 0;
    delay(1000);
  });
  webServer.handleClient();
  //fader = 1;
}
  delay(1000);
});

webServer.on("/fadegreen", [](){
  webServer.send(200, "text/html", webpage);
  while (fader){
  fadegreen();
  webServer.handleClient();
  webServer.on("/offset", [](){
    fader = 0;
    delay(1000);
  });
  webServer.handleClient();
  //fader = 1;
}
  delay(1000);
});


webServer.on("/fadeblue", [](){
  webServer.send(200, "text/html", webpage);
  while (fader){
  fadeblue();
  webServer.handleClient();
  webServer.on("/offset", [](){
    fader = 0;
    delay(1000);
  });
  webServer.handleClient();
  //fader = 1;
}
  delay(1000);
});



}
//////////////////////////////////////////////////////////////////////////////////////////////////
void loop () {
webServer.handleClient();
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//FUNKCIJE OVDJE SE MOZE DODATI JOS MODEOVA PO ZELJI I MJERI
void testRGB() {
analogWrite(16, 1023); // Crvena gasi
analogWrite(5, 1023); // Zelena gasi
analogWrite(4, 1023); // Plava gasi
fade(16); // Crvena
fade(5); // Zelena
fade(4); // Plava

}

//////////////////////////////////////////////////////////////////////////////////////////////////

void fade(int pin) {
for (int u = 0; u < 1024; u++) {
analogWrite(pin, 1023 - u);
delay(1);
}
for (int u = 0; u < 1024; u++) {
analogWrite(pin, u);
delay(1);
}
}

void fading (){
  for (int u = 0; u < 1024; u++) {
  analogWrite(16, 1023 - u);
  analogWrite(5, 1023 - u);
  analogWrite(4, 1023 - u);
  delay(1);
  }
  for (int u = 0; u < 1024; u++) {
  analogWrite(16, u);
  analogWrite(5, u);
  analogWrite(4, u);
  delay(1);
}
}
//OVO GASI TRAKU LOGICNO
void stripOff (){
  digitalWrite(16, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
}

void fadered (){
  for (int u = 0; u < 1024; u++) {
  analogWrite(16, 1023 - u);
  delay(1);
  }
  for (int u = 0; u < 1024; u++) {
  analogWrite(16, u);
  delay(1);
}
}

void fadegreen (){

  for (int u = 0; u < 1024; u++) {
  analogWrite(5, 1023 - u);
  delay(1);
  }
  for (int u = 0; u < 1024; u++) {
  analogWrite(5, u);
  delay(1);
}
}

void fadeblue(){

  for (int u = 0; u < 1024; u++) {
  analogWrite(4, 1023 - u);
  delay(1);
  }
  for (int u = 0; u < 1024; u++) {
  analogWrite(4, u);
  delay(1);
}
}
