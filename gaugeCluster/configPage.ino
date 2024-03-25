void cfgPage() {
  mfd.setCursor(3, 40);
  mfd.print("Change UI color");
  mfd.drawLine(0, 60, 240, 60, ui_color);
  mfd.setCursor(3, 66);
  mfd.print("Set time");
  mfd.drawLine(0, 86, 240, 86, ui_color);
  mfd.setCursor(3, 92);
  mfd.print("Apply settings");
  mfd.drawLine(0, 112, 240, 112, ui_color);
}
