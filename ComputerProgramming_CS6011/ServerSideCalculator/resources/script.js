let b = document.getElementById("button");
let message = "";
let messageWS = ""
let f = function(){
    let num1 = document.getElementById("numeroUno").value;
    console.log(num1);
    let num2 = document.getElementById("numeroDos").value;
    console.log(num2)

    message = "/calculate?x="+num1+"&y="+num2;
    console.log(message);

    messageWS= num1+" "+num2;

    let xhr = new XMLHttpRequest()
    xhr.open("GET", message);
    xhr.addEventListener("load", function(){console.log(this);
        document.getElementById("resultText").value = this.responseText;
    });
    xhr.send();

    //WebSocket stuff
    let ws = new WebSocket("ws://"+location.host);

    ws.onopen = function() {
        ws.send(messageWS);
        alert("Message is sent...");

        ws.onmessage = function (evt) {
            let received_msg = evt.data;
            console.log(evt.data);
            alert("Message is received...");
            document.getElementById("resultTextWS").value = evt.data;
        };

        ws.onclose = function() {
            // websocket is closed.
            alert("Connection is closed...");
        };

    };

}

b.addEventListener("click", f);




