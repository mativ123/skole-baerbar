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
    var backgroundImg = new Image();
    backgroundImg.src = 'background.jpg';

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
        ballX = 140;
        ballY = 650;
        powerVal = power.value/20;
        //her laver jeg tallene jeg får fra sliderne og laver dem om til procent (1.1111 er bare 100/90)
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
        angleOutput.innerHTML = this.value+"°";
    }

    function main()
    {
        if(skydBool)
        {
            posString = "X: "+Math.round(ballX)+"m, Y: "+Math.round(800-ballY)+"m";

            //context.drawImage(backgroundImg, 0, 0, 2000, 1125);
            context.clearRect(0, 0, 2000, 800);
            drawLine();
            context.drawImage(cannonball, ballX, ballY, 50, 50);
            context.save();
            context.translate(40+248/2, 650+59/2);
            context.rotate(-angle.value*Math.PI/180);
            context.translate(-(40+248/2), -(650+59/2));
            context.drawImage(cannonShooter, 40, 650, 248, 59);
            context.restore();
            context.drawImage(cannonBase, 20, 675, 200, 125);
            context.font = "30px Arial";
            if(ballY<30)
            {
                context.fillText(posString, ballX, 30); 
                context.fillText(speedString, ballX, 60);
            } else if(ballX>canvas.width-300)
            {
                context.fillText(posString, canvas.width-300, ballY); 
                context.fillText(speedString, canvas.width-300, ballY-30);
            } else
            {
                context.fillText(posString , ballX, ballY-10); 
                context.fillText(speedString, ballX, ballY-40);
            }

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

    //her gemmer jeg koordinaterne i lister
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

    //her tegner jeg linjen ud fra koordinaterne
    function drawLine()
    {
        //blå linje
        context.lineWidth = 10;
        context.strokeStyle = "#ff000d";
        context.beginPath();
        context.moveTo(140,650);
        for(var i = 0; i<prevListY.length; ++i)
        {
            context.lineTo(prevListX[i]+25, prevListY[i]+25);
        }
        context.stroke();

        //røde linje
        context.lineWidth = 10;
        context.strokeStyle = "#2200ff";
        context.beginPath();
        context.moveTo(140,650);
        for(var i = 0; i<trailPointListX.length; ++i)
        {
            context.lineTo(trailPointListX[i]+25, trailPointListY[i]+25);
        }
        context.stroke();
    }

    function speedDef()
    {
        //var velX = Math.abs(Math.round(((ballX-tempX)/0.001)/100));
        //var velY = Math.abs(Math.round(((ballY-tempY)/0.001)/100));
        var distance = Math.sqrt(Math.pow((ballX-tempX), 2) + Math.pow((ballY-tempY), 2));
        var velocity = Math.round(distance/0.001);
        speedString = velocity+"m/s";

        tempX = ballX;
        tempY = ballY;

        setTimeout(speedDef, 1);
    }
    main();
    speedDef();
}
