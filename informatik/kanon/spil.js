window.onload=function()
{
    var canvas = document.getElementById('spilCanvas');
    var context = canvas.getContext('2d');
    var cannonball = new Image();
    cannonball.src = 'cannonball.png';

    var ballX = 0;
    var ballY = 200;
    var xSpeed = 1;
    var ySpeed = 1;

    var power = document.getElementById("power");
    var angle = document.getElementById("angle");
    
    var skydBool = false;
    var powerPercent;
    var powerSub;
    var powerVal;

    function skydFunc()
    {
        ballX = 0;
        ballY = 800;
        powerVal = power.value/20;
        powerPercent = (angle.value*1.1111)/100;
        powerSub = powerVal*powerPercent;
        console.log(powerPercent);
        console.log(powerSub);


        ySpeed = powerVal-(powerVal-powerSub);
        xSpeed= powerVal-powerSub;
        console.log(ySpeed);
        console.log(xSpeed);
        skydBool = true;
    }

    document.getElementById("skydKnap").onclick = function () { skydFunc() };

    function skud()
    {
        if(skydBool)
        {
            context.clearRect(0, 0, 2000, 800);
            context.drawImage(cannonball, ballX, ballY, 50, 50);
            ballX+=xSpeed;
            ballY-=ySpeed;

            ySpeed-=0.00982;

            if(ballY > 800 && ballX)
            {
                skydBool = false;
            }
        }
        setTimeout(skud, 1);
    }

    skud();
}
