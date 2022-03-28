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

    var power = document.getElementById("slider");
    
    var skydBool = false;

    function skud()
    {
        if(skydBool)
        {
            xSpeed=power.value/50;
            context.clearRect(0, 0, 500, 500);
            context.drawImage(cannonball, ballX, ballY, 50, 50);
            ballX+=xSpeed;
            ballY-=ySpeed;

            ySpeed-=0.00982;

            if(ballY > 500)
            {
                skydBool = false;
            }
        }
        setTimeout(skud, 1);
    }

    function skyd()
    {
        skydBool = true;
    }
    skud();
}
