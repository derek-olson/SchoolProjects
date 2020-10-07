 let canvas = document.getElementById('canvas');
let ctx = canvas.getContext('2d');
let raf;
let running = false;

let currentX = canvas.width / 2;
let currentY = canvas.height / 2;

let chaseX = currentX - 200;
let chaseY = currentY - 300;

let background = new Image();
background.src = "Images/forest.jpg";

let img = new Image();
img.src = "Images/winnie.png.jpg";

let chasers = new Image();
chasers.src = "Images/bees.jpg";

function clear() {
    ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
    ctx.fillRect(0,0,canvas.width,canvas.height);
}

function draw() {
    clear();
    ctx.drawImage(background, 0, 0, canvas.width, canvas.height);
    ctx.drawImage(img, currentX - (img.width / 2), currentY - (img.height / 2), 200, 200);
    ctx.drawImage(chasers, chaseX, chaseY, 200, 200);
    if(chaseX < )

    raf = window.requestAnimationFrame(draw);
}

canvas.addEventListener('mousemove', function(e) {
    if (!running) {
        clear();
        currentX = e.clientX + 325;
        currentY = e.clientY + 190;
        ctx.drawImage(background, 0, 0, canvas.width, canvas.height);
        ctx.drawImage(img, currentX, currentY, 200, 200);
        ctx.drawImage(chasers, chaseX, chaseY, 200, 200);
    }
});


draw();


