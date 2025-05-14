#include "WebPage.hpp"

const char* ssid = "TensionMonitor";
const char* password = "12345678";

WebServer server(80);

void handleWebPage() {
  int raw1 = loadCell_1();
  int raw2 = loadCell_2();
  int diffRaw = abs(raw1 - raw2);

  float tension1_gF = raw1;
  float tension2_gF = raw2;
  float diff_gF = diffRaw;

  float tension1_mF = raw1 * 9.81;
  float tension2_mF = raw2 * 9.81;
  float diff_mF = diffRaw * 9.81;

  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='2'>";
  html += "<title>Tension Monitor</title></head><body>";
  html += "<h2>Tension Monitoring</h2>";

  html += "<p><b>Tension 1:</b><br>";
  html += String(tension1_gF, 2) + " gF<br>";
  html += String(tension1_mF, 2) + " mF</p>";

  html += "<p><b>Tension 2:</b><br>";
  html += String(tension2_gF, 2) + " gF<br>";
  html += String(tension2_mF, 2) + " mF</p>";

  html += "<p><b>Tension Difference:</b><br>";
  html += String(diff_gF, 2) + " gF<br>";
  html += String(diff_mF, 2) + " mF</p>";

  html += "<hr><p><small>WiFi: " + String(ssid) + "</small></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void webSetup() {
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.on("/", handleWebPage);
  server.begin();
  Serial.println("Web server started");
}

void serverHandler() {
  server.handleClient();
}
