var smoothX = 0;
var smoothY = 0;

var scaleX;
var scaleY;

function preload() {
	img = loadImage('./assets/clouds.jpg');
}

function setup() {
  image(img, 0, 0);
  createCanvas(windowWidth, windowHeight);
  // createCanvas(600,600);
  
}


function draw(){
  
  // background(23, 185, 239); 
  
  smoothX = .99*smoothX + .01*mouseX;
  smoothY = .99*smoothY + .01*mouseY;

  rectangle(smoothX,smoothY,40,40);

  // fill(255,0,255,0);
  // rectangle(50,50,50,50);
  
  // change scale as rectangle moves from foreground to background
  // x, y is location
  // size would be another variable
}