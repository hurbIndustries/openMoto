// Initialize the page bar at the bottom of the UI.
void pageBar() {
  mfd.fillRect(0, 32, 240, 2, ui_color);
  mfd.drawLine(0, 290, 320, 290, ui_color);
  mfd.setTextSize(2);
  mfd.setCursor(7, 300);
  mfd.print("SPD");
  mfd.drawLine(50, 290, 50, 320, ui_color);
  mfd.setCursor(60, 300);
  mfd.print("MPG");
  mfd.drawLine(105, 290, 105, 320, ui_color);
  mfd.setCursor(115, 300);
  mfd.print("MUS");
  mfd.drawLine(160, 290, 160, 320, ui_color);
  mfd.setCursor(170, 300);
  mfd.print("AFR");
  mfd.drawLine(215, 290, 215, 320, ui_color);
  mfd.setCursor(225, 300);
  mfd.print("C");
}

void setPage(int page) {
  if(pageChange) {
    mfd.fillRect(0, 275, 240, 10, ST77XX_BLACK);
    resetArea();
    pageChange = false;
  }
  if(pageNum == 1) {
    mfd.fillTriangle(20, 277, 30, 277, 25, 285, ui_color); 
  } else
  if(pageNum == 2) {
    mfd.fillTriangle(70, 277, 80, 277, 75, 285, ui_color);
  } else 
  if(pageNum == 3) {
    mfd.fillTriangle(125, 277, 135, 277, 130, 285, ui_color);
  } else
  if(pageNum == 4) {
    mfd.fillTriangle(180, 277, 190, 277, 185, 285, ui_color);
  } else 
  if(pageNum == 5) {
    mfd.fillTriangle(225, 277, 235, 277, 230, 285, ui_color);
  } else {
    pageNum = 1;
  }
}

void resetArea() {
  mfd.fillRect(0, 33, 240, 260, ST77XX_BLACK);
}

void pageCheck() {
  if(lastPage != pageNum) {
    pageChange = true;
  }
  lastPage = pageNum;
  switch(pageNum) {
    case 0:
      pageNum = 5;
      setPage(pageNum);
      break;
    case 1:
      setPage(pageNum);
      speedPage();
      break;
    case 2:
      setPage(pageNum);
      mpgPage();
      break;
    case 3:
      setPage(pageNum);
      musPage();
      break;
    case 4:
      setPage(pageNum);
      musPage();
      break;
    case 5:
      pageBar();
      setPage(pageNum);
      cfgPage();
      break;
    case 6:
      pageNum = 1;
      setPage(pageNum);
      break;
    default:
      pageNum = 1;
      setPage(pageNum);
      break;
  }
}