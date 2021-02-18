class Encoder
{
private:
  int pinA;
  int pinB;
  volatile long ticks = 0;
  int increment = 0;

public:
  Encoder(int pinA, int pinB, bool isClockwise);
  void triggerA();
  void triggerB();
  volatile long getTicks();
  void reset();
  int getPinA();
  int getPinB();
};
