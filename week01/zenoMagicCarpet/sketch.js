var smoothX = 0;
var smoothY = 0;

var scaleWidth = 129;
var scaleHeight = 100;

function preload() {
	img = loadImage('assets/clouds.jpg');
  rug = loadImage('assets/carpet-small.jpg');
}

function setup() {
  // image(img, 0, 0);
  createCanvas(windowWidth, windowHeight);
  // createCanvas(600,600);
  
  // canvas resize
}


function draw(){
  
  // background(23, 185, 239); 
  background(img, 0, 0, 1920, 1200);

  smoothX = .99*smoothX + .01*mouseX;
  smoothY = .99*smoothY + .01*mouseY;
  // blending current and destination values
  // helps with sensor data (to reduce noise)

  // change scale as rectangle moves from foreground to background
  // x, y is location
  // size would be another variable

  image(rug, smoothX, smoothY, scaleWidth, scaleHeight);

  if (mouseX >= 100){
    scaleWidth = .999*scaleWidth;
    scaleHeight = .999*scaleHeight;

      console.log(scaleWidth);

  } else { 
    scaleWidth = 1.001*scaleWidth;
    scaleHeight = 1.001*scaleHeight;
  };

  // distance of object mapped to center of the window
  // map function with min max
  // map(value,start1,stop1,start2,stop2,[withinBounds])

  // scaleWidth = map(smoothX, 100, 200, 400, 500, true);
  // scaleHeight = map(smoothY, 100, 200, 400, 500, true);
  // image(rug, smoothX, smoothY, scaleWidth, scaleHeight); 

  // image(img,x,y,[width],[height])

  
  // rect(smoothX,smoothY,70,40);
  // image(rug, x, y, scaleWidth, scaleHeight);
  // image(rug, smoothX, smoothY);


}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}