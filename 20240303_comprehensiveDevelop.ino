void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    connect_NET();
    web_server();

}

void loop() {
  // put your main code here, to run repeatedly:
    DNS_request_loop();
}
