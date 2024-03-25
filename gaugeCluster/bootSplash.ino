// Bootsplash.
void bootSplash() {
  mfd.fillScreen(ST77XX_BLACK);
  mfd.fillTriangle(120, 190, 70, 280, 170, 280, ST77XX_ORANGE);
  mfd.setTextSize(2);
  mfd.setCursor(7, 7);
  mfd.print(ver_id);
  mfd.setCursor(108, 230);
  mfd.setTextSize(5);
  mfd.write("!");
  mfd.setTextSize(3);
  mfd.setCursor(20, 100);
  mfd.write("Starting...");
}
