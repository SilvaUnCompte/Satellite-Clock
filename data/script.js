let right = 0, left = 0; let buf_right = 0, buf_left = 0; let speed = 0, angle_in_degrees = 0;
setInterval(function sendDirection() {
    sensibility = 15;
    ratio_speed = speed / 100;

    if (angle_in_degrees < 22.5 || angle_in_degrees > 337.5) {
        right = 100*ratio_speed;
        left = -25*ratio_speed;
    }
    else if (angle_in_degrees >= 22.5 && angle_in_degrees < 67.5) {
        right = 100*ratio_speed;
        left = 0*ratio_speed;
    }
    else if (angle_in_degrees >= 67.5 && angle_in_degrees < 112.5) {
        right = 100*ratio_speed;
        left = 100*ratio_speed;
    }
    else if (angle_in_degrees >= 112.5 && angle_in_degrees < 157.5) {
        right = 0*ratio_speed;
        left = 100*ratio_speed;
    }
    else if (angle_in_degrees >= 157.5 && angle_in_degrees < 202.5) {
        right = -25*ratio_speed;
        left = 100*ratio_speed;
    }
    else if (angle_in_degrees >= 202.5 && angle_in_degrees < 247.5) {
        right = -0*ratio_speed;
        left = -100*ratio_speed;
    }
    else if (angle_in_degrees >= 247.5 && angle_in_degrees < 295.5) {
        right = -100*ratio_speed;
        left = -100*ratio_speed;
    }
    else {
        right = -100*ratio_speed;
        left = -0*ratio_speed;
    }

    if (left != buf_left || right != buf_right) {

        buf_left = left;
        buf_right = right;

        // Convert % to V for right motor (195 - 255)
        let v_left = 0; let v_right = 0;
        if (Math.abs(buf_right) > sensibility) {
            v_right = (buf_right * .6);
            v_right += (buf_right > 0) ? 195 : -195;
        }
        if (Math.abs(buf_left) > sensibility) {
            v_left = (buf_left * .6);
            v_left += (buf_left > 0) ? 195 : -195;
        }

        let xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/direction-stream?right=" + v_right + "&left=" + v_left, true);
        xhttp.send();
    }
}, 500);

let canvas, ctx, coord, paint, y_orig, x_orig;
function init() {
    canvas = document.getElementById('joystick');
    ctx = canvas.getContext('2d');
    coord = { x: 0, y: 0 };
    paint = false;
    resize();
}

document.addEventListener('mousedown', startDrawing);
document.addEventListener('mouseup', stopDrawing);
document.addEventListener('mousemove', Draw);
document.addEventListener('touchstart', startDrawing);
document.addEventListener('touchend', stopDrawing);
document.addEventListener('touchcancel', stopDrawing);
document.addEventListener('touchmove', Draw);
window.addEventListener('resize', resize);
document.getElementById("speed").innerText = 0;
document.getElementById("angle").innerText = 0;

function background() {
    x_orig = radius + 65;
    y_orig = height - radius - 85;
    ctx.beginPath()
    ctx.arc(x_orig, y_orig, radius + 10, 0, Math.PI * 2, true);
    ctx.fillStyle = '#AEAEAE';
    ctx.fill()
    ctx.strokeStyle = '#C4C4C4';
    ctx.lineWidth = 8;
    ctx.stroke();
}

function joystick(width, height) {
    ctx.beginPath();
    ctx.arc(width, height, radius, 0, Math.PI * 2, true);
    ctx.fillStyle = '#F08080';
    ctx.fill();
    ctx.strokeStyle = '#F6ABAB';
    ctx.lineWidth = 8;
    ctx.stroke();
}

function resize() {
    width = window.innerWidth; //Sets the variable width to be equal to the windows width
    height = window.innerHeight; //Sets the variable height
    radius = height / 5; // specify the radius to 200
    ctx.canvas.width = width; //sets the canvas width to be equal to variable width
    ctx.canvas.height = height; //sets the canvas height
    background();//draw the background
    joystick(x_orig, y_orig); //sends to the joystick function this variables
}

function getPosition(event) {
    let mouse_x = event.clientX || event.touches[0].clientX;
    let mouse_y = event.clientY || event.touches[0].clientY;
    coord.x = mouse_x - canvas.offsetLeft;
    coord.y = mouse_y - canvas.offsetTop;
}

function is_it_in_the_circle() {
    let current_radius = Math.sqrt(Math.pow(coord.x - x_orig, 2) + Math.pow(coord.y - y_orig, 2));
    return radius >= current_radius ? true : false;
}

function startDrawing(event) {
    paint = true;
    getPosition(event);
    if (is_it_in_the_circle()) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        background();
        joystick(coord.x, coord.y);
        Draw();
    }
}


function stopDrawing() {
    paint = false;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    background();
    joystick(x_orig, y_orig);
    document.getElementById("speed").innerText = 0;
    document.getElementById("angle").innerText = 0;
    speed = 0;
    angle_in_degrees = 0;
}


function Draw(event) {

    if (paint) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        background();
        let x, y;
        let angle = Math.atan2((coord.y - y_orig), (coord.x - x_orig));

        if (Math.sign(angle) == -1) {
            angle_in_degrees = Math.round(-angle * 180 / Math.PI);
        }
        else {
            angle_in_degrees = Math.round(360 - angle * 180 / Math.PI);
        }

        if (is_it_in_the_circle()) {
            joystick(coord.x, coord.y);
            x = coord.x;
            y = coord.y;
        }
        else {
            x = radius * Math.cos(angle) + x_orig;
            y = radius * Math.sin(angle) + y_orig;
            joystick(x, y);
        }

        getPosition(event);

        speed = Math.round(100 * Math.sqrt(Math.pow(x - x_orig, 2) + Math.pow(y - y_orig, 2)) / radius);

        let x_relative = Math.round(x - x_orig);
        let y_relative = Math.round(y - y_orig);

        document.getElementById("speed").innerText = speed;
        document.getElementById("angle").innerText = angle_in_degrees;
    }
}