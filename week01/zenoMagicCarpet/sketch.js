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
  
}


function draw(){
  
  // background(23, 185, 239); 
  background(img, 0, 0, 1920, 1200);

  smoothX = .99*smoothX + .01*mouseX;
  smoothY = .99*smoothY + .01*mouseY;

  // change scale as rectangle moves from foreground to background
  // x, y is location
  // size would be another variable

  image(rug, smoothX, smoothY, scaleWidth, scaleHeight);

  if (mouseX >= 1000 && mouseY >= 1000){
    scaleWidth = .2*scaleWidth;
    scaleHeight = .2*scaleHeight;
  } else { 
    scaleWidth = 1.001*scaleWidth;
    scaleHeight = 1.001*scaleHeight;
  };

  // image(img,x,y,[width],[height])
  // image(rug, smoothX, smoothY);

  // rect(smoothX,smoothY,70,40);
  
}