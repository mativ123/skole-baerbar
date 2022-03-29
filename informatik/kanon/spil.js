window.onload=function()
{
    var canvas = document.getElementById('spilCanvas');
    var context = canvas.getContext('2d');
    var cannonball = new Image();
    cannonball.src = 'cannonball.png';
    var cannonBase = new Image();
    cannonBase.src = 'cannon-base.png';
    var cannonShooter = new Image();
    cannonShooter.src = 'cannon-shooter.png';

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

    var rollingSlowdown = 10;

    var posString = "X: "+Math.round(ballX)+", Ball Y"+Math.round(ballY);
    var speedString;
    var tempX;
    var tempY;

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
    var powerOutput = document.getElementById("powerText");
    power.oninput = function()
    {
        powerOutput.innerHTML = this.value;
    }

    var angleOutput = document.getElementById("angleText");
    angle.oninput = function()
    {
        angleOutput.innerHTML = this.value;
    }

    function main()
    {
        if(skydBool)
        {
            posString = "X: "+Math.round(ballX)+", Ball Y: "+Math.round(800-ballY);

            context.clearRect(0, 0, 2000, 800);
           // context.save();
           // context.translate(100, 100);
           // context.rotate(20*Math.PI/180);
           // context.translate(-100, -100);
           // context.drawImage(cannonShooter, 100, 100, 100, 100);
           // context.restore();
           // context.drawImage(cannonBase, 100, 100, 100, 100);
            drawLine();
            context.drawImage(cannonball, ballX, ballY, 50, 50);
            context.font = "30px Arial";
            context.fillText(posString , 10, 50); 
            context.fillText(speedString, 10, 100);

            ySpeed-=0.00982;
            ballX+=xSpeed;
            

            if(ballY < 750)
            {
                ballY-=ySpeed;
            } else
            {
                if(xSpeed>0)
                {
                    xSpeed -= rollingSlowdown/1000;
                } else
                {
                    xSpeed = 0;
                }

                stoppedFlying = true;
            }
        }
        setTimeout(main, 1);
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

    function speedDef()
    {
        var velX = Math.abs(Math.round(((ballX-tempX)/0.001)/100));
        var velY = Math.abs(Math.round(((ballY-tempY)/0.001)/100));
        speedString = "X: "+velX+"m/s, Y: "+velY+"m/s";
        tempX = ballX;
        tempY = ballY;

        setTimeout(speedDef, 1);
    }
    main();
    speedDef();
}
