void speedPage() {
  mfd.setTextSize(10);
  if(speed <= 9) {
    mfd.setCursor(50, 120);
  } else if(speed >= 10 && speed <= 99) {
    mfd.setCursor(15, 120);
  } else {
    mfd.setTextSize(8);
    mfd.setCursor(0, 120);
  }
  mfd.print(speed);
  mfd.setTextSize(5);
  mfd.print("mph");
}