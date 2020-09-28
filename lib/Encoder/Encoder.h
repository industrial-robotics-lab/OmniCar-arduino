class Encoder {
  private:
    const int TICKS_PER_REV = 360;
    volatile int value;
    float fractOfSec;
    float rpm;
    
  public:
    int pin;
    Encoder(int pin, int intervalMillis);
    float getRPM();
    void evaluateSpeed();
    void increment();
};
