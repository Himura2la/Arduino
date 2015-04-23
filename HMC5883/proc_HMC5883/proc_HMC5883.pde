import processing.serial.*;

final int[] scale = {-600, 600};
final int grid = 100;
final char txtUpd = 20;  //Text update delay

color c_X = color(127, 34, 255);
color c_Y = color(15, 128, 55);
color c_Z = color(255, 170, 59);

Serial s;
int[] curPoint = {0, 0, 0};
int[] prevPoint = new int[3]; //Will be inited anyway
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


void serialEvent(Serial s) {
  try {
    String inString = s.readStringUntil('\r');
    float[] inArray = float(split(inString, '\t'));
    
    char i = 0; for (int elem : curPoint) prevPoint[i++] = elem; //Save previous
    i = 0; for (float elem : inArray)
      curPoint[i++] = (int)map(elem, scale[1], scale[0], 0, height);
    
    stroke(c_X); line(t, prevPoint[0], t, curPoint[0]); //x
    stroke(c_Y); line(t, prevPoint[1], t, curPoint[1]); //y
    stroke(c_Z); line(t, prevPoint[2], t, curPoint[2]); //z

    if (upd_i-- <= 0) {
      stroke(50); fill(0); rect(1, 1, 165, 95);
      fill(c_X);
      text("X:", 35, 30);
      text(nf(inArray[0], 0, 2), 160, 30);
      
      fill(c_Y);
      text("Y:", 35, 60);
      text(nf(inArray[1], 0, 2), 160, 60);
      
      fill(c_Z);
      text("Z:", 35, 90);
      text(nf(inArray[2], 0, 2), 160, 90);
      upd_i = txtUpd;
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
    println(e);
  }
}
