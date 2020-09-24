class Encoder {
  private:
    const int TICKS_PER_REV = 360;
    volatile int value;
    float fractOfSec;
    int intervalMillis; // 10 - 20000
    long previousMillis = 0;
    long currentMillis = 0;
    float rpm;
    
  public:
    int pin;
    Encoder(int pin, int intervalMillis);
    float getRPM();
    void update();
    void increment();
};
