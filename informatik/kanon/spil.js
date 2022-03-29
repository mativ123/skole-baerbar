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

    var trailPointListX = [];
    var trailPointListY = [];
    var stoppedFlying = true;
    var prevListX = [];
    var prevListY = [];

    var rollingRot = 0;
    var rollingSlowdown = 1;

    function main()
    {
        setTimeout(main, 1);
    }

    function skydFunc()
    {
        ballX = 0;
        ballY = 700;
        powerVal = power.value/20;
        powerPercent = (angle.value*1.1111)/100;
        powerSub = powerVal*powerPercent;

        ySpeed = powerVal-(powerVal-powerSub);
        xSpeed= powerVal-powerSub;
        skydBool = true;
        stoppedFlying = false;

        prevListX = trailPointListX;
        prevListY = trailPointListY;
        trailPointListX = [];
        trailPointListY = [];
        trailPointAdd();
    }

    document.getElementById("skydKnap").onclick = function () { skydFunc() };

    function skud()
    {
        if(skydBool)
        {
            context.clearRect(0, 0, 2000, 800);
            drawLine();
            context.drawImage(cannonball, ballX, ballY, 50, 50);
            ballX+=xSpeed;

            ySpeed-=0.00982;

            if(ballY < 750)
            {
                ballY-=ySpeed;
            } else
            {
                xSpeed -= rollingSlowdown/1000;
                rollingRot+=1;
                context.rotate(rollingRot * Math.PI / 180);

                stoppedFlying = true;
            }
        }
        setTimeout(skud, 1);
    }

    function trailPointAdd()
    {
        trailPointListX.push(ballX);
        trailPointListY.push(ballY);

        if(stoppedFlying)
        {
            return;
        }

        setTimeout(trailPointAdd, 1);
    }

    function drawLine()
    {
        context.lineWidth = 10;
        context.strokeStyle = "#ff000d";
        context.beginPath();
        context.moveTo(0 ,700);
        for(var i = 0; i<prevListY.length; ++i)
        {
            context.lineTo(prevListX[i]+25, prevListY[i]+25);
        }
        context.stroke();

        context.lineWidth = 10;
        context.strokeStyle = "#2200ff";
        context.beginPath();
        context.moveTo(0 ,700);
        for(var i = 0; i<trailPointListX.length; ++i)
        {
            context.lineTo(trailPointListX[i]+25, trailPointListY[i]+25);
        }
        context.stroke();
    }

    skud();
    main();
}
