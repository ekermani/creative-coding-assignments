var t = 0;  // time used to animate circle along the line
// var t;
var dir = 1;  // direction moving
var gSize = 150;  // size of the graph


function setup() {
  
  createCanvas(window.innerWidth, window.innerHeight);
  
}


function draw(){
  
  background(23, 185, 239); 
  
  // increase t in current direction
  t += .01 * dir;

  // reverse t if it becomes greater than 1 or less than 0
  if( t >= 1 || t <= 0){ dir *= -1; }
  
  
  push();

    translate(10,10);

    // draw the graph and animation passing in the function we want to use to ease as a parameter
    // LINEAR
    drawGraph(linear);
    // mousePressed(t, linear);
    drawAnimatedPoint(t,linear);
    drawLabel("Linear");
    
    // IN QUAD
    drawGraph(inQuad);
    drawAnimatedPoint(t, inQuad);
    drawLabel2("Quad In");

    // IN CUBIC
    drawGraph(inCubic);
    drawAnimatedPoint(t,inCubic);
    drawLabel3("Cubic In");

  pop();

}

// on mousePressed, animate point along curve
// mouseX has to be xPos, mouseY yPos on click
// function mousePressed(t,easeFunction,options=null) {

//   var pct = easeFunction(t,options);
//   var lerpPos = pct*gSize; // point A is 0 so only need to multily by point B which is at max graph size
  
//   var xPos = t * gSize;   // move in linear steps alon x axis
//   var yPos = gSize - lerpPos; // beacause coord inverted

//   fill(255);
//   ellipse(xPos, yPos, 10, 10);
//   t = 0;

// }

function drawAnimatedPoint(t,easeFunction,options=null){
  
  var pct = easeFunction(t,options);
  var lerpPos = pct*gSize; // point A is 0 so only need to multily by point B which is at max graph size
  
  var xPos = t * gSize;   // move in linear steps alon x axis
  var yPos = gSize - lerpPos; // because coord inverted

  fill(255);
  ellipse(xPos,yPos,10,10);

}


// function drawAnimatedPoint2(t,easeFunction,options=null){
  
//   var pct = easeFunction(t,options);
//   var lerpPos = pct*gSize; // point A is 0 so only need to multily by point B which is at max graph size
  
//   var xPos = t * gSize;   // move in linear steps alon x axis
//   var yPos = gSize - lerpPos; // beacause coord inverted

//   fill(255);
//   ellipse(xPos,yPos,10,10);
// }


function drawGraph(easeFunction,options=null){
  
  noFill();
  stroke(255);
  
  // draw lines for graph on left and bottom
  line(0,0,0,gSize);
  line(0,gSize,gSize,gSize);

  // x1, y1, x2, y2
  // second graph
  line(200,0,200,gSize);
  line(200,gSize,gSize *2.33,gSize);

  line(400,0,400,gSize);
  line(400,gSize,gSize*3.66,gSize);

  beginShape();

  for(var i = 0; i < gSize; i+=2){
    
    var pct =(1 / gSize) * i;
    
    pct = easeFunction(pct,options);
    
    var lerpPos = pct*gSize;
    
    vertex(i,gSize-lerpPos);
    
  }
  
  endShape();

}

// function drawGraph2(easeFunction,options=null){
  
//   noFill();
//   stroke(255);
  
//   // draw lines for graph on left and bottom
//   line(0,0,0,gSize);
//   line(0,gSize,gSize,gSize);

//   beginShape();

//   for(var i = 0; i < gSize; i+=2){
    
//     var pct =(1 / gSize) * i;
    
//     pct = easeFunction(pct,options);
    
//     var lerpPos = pct*gSize;
    
//     vertex(i,gSize-lerpPos);
    
//   }
  
//   endShape();

// }

function drawLabel(mytext){
  noStroke();
  textSize(14);
  text(mytext, 0, gSize+16);
}

function drawLabel2(mytext){
  noStroke();
  textSize(14);
  text(mytext, 200, gSize+16);
}

function drawLabel3(mytext){
  noStroke();
  textSize(14);
  text(mytext, 400, gSize+16);
}


// LINEAR
function linear(t,options=null){ 
  return t; 
}

// IN QUAD
function inQuad(t,options=null){ 
  return t * t; 
}

// IN CUBIC
function inCubic(t, options=null) {
    return t * t * t;
}

