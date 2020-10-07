let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");

window.requestAnimFrame = (function (callback) {
    return window.requestAnimationFrame;
});

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

let pct = 0.00;
let fps = 60;

let isDraggable = true;

img.onload = function () {
    handleMovement();
};

function handleMovement() {
    canvas.onmouseout = function (e) {
        isDraggable = false;
    };

    canvas.onmousemove = function (e) {
        if (isDraggable) {
            currentX = e.pageX - this.offsetLeft + 300;
            currentY = e.pageY - this.offsetTop + 200;
        }
    };
    animate();
}

function animate() {
    setTimeout(function () {
        pct += 0.01;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.drawImage(background, 0, 0, canvas.width, canvas.height);
        ctx.drawImage(img, currentX - (img.width / 2), currentY - (img.height / 2), 200, 200);
        ctx.drawImage(chasers, chaseX, chaseY, 200, 200);
        let dx = currentX - chaseX;
        let dy = currentY - chaseY;
        if(dx < 0){chaseX -= dx * pct;
            //if (pct < 1.00) {requestAnimationFrame(animate)};
        }
        if(dx > 0){chaseX += dx * pct;
            //if (pct < 1.00) {requestAnimationFrame(animate)};
        }
        if(dy < 0){chaseY -= dy * pct;
            //if (pct < 1.00) {requestAnimationFrame(animate)};
        }
        if(dy< 0){chaseY += dy * pct;
            //if (pct < 1.00) {requestAnimationFrame(animate)};
        }
        if (pct < 1.00) {requestAnimationFrame(animate)}
    }, 1000/fps);
}


