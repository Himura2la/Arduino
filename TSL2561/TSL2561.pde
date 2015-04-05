import processing.serial.*;

final int[] scale = {0, 1500};
final int grid = 500;
final char txtUpd = 20;  //Text update delay

color c_plot = color(0, 255, 0);

Serial s;
int curPoint = 0;
int prevPoint; //Will be inited anyway
int t = 0;
int upd_i = txtUpd;

void drawCanvas(){
  background(0);
  stroke(50);
  for (int i = scale[0]; i < scale[1]; i += grid){
    int y = (int)map(i, scale[0], scale[1], 0, height);
    line(0, y, width, y);
  }
}

void setup () {
  size(1024, 600);
  s = new Serial(this, Serial.list()[1], 9600);
  s.bufferUntil('\n'); //serialEvent trigger
  drawCanvas();
  textSize(30);
  textAlign(RIGHT);
  println("Waiting for data...");
}

void draw () {
   // everything happens in the serialEvent()
}

boolean firstGet = true;
void serialEvent(Serial s) {
  try {
    String inString = s.readStringUntil('\r');
    float in = float(split(inString, '\t'))[0];
    
    prevPoint = curPoint; //Save previous
    curPoint = (int)map(in, scale[1], scale[0], 0, height);
    
    if (!firstGet) {
      stroke(c_plot);
      line(t, prevPoint, t, curPoint);
    }
    firstGet = false;

    if (upd_i-- <= 0) {
      stroke(50); fill(0); rect(1, 1, 190, 35);
      fill(c_plot);
      text("Lux:", 65, 30);
      text(nf(in, 0, 2), 190, 30);
    }

    // at the edge of the screen, go back to the beginning
    if (t >= width) {
      t = 0;
      drawCanvas();
    }
    else t++;
  }
  catch (Exception e) {
    println("Error!");
  }
}
