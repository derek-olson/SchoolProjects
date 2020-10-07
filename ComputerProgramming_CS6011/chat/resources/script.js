let chatRoomButton = document.getElementById("chatRoomButton");
let sendMessageButton = document.getElementById("sendMessageButton");
let message = "";
let messageWS = "";
let prevChatRooms = [];
let prevMessages = [];
let outMessages = [];
let user = "";

let ws = new WebSocket("ws://"+location.host);

let openChatRoom = function(){
    let chatroom = document.getElementById("chatroom").value;
    prevChatRooms.push(chatroom);
    messageWS = "join "+chatroom;

    ws.send(messageWS);
    alert("Message is sent...");

    ws.onmessage = function (evt) {
        //alert("Message is received...");
        let obj = JSON.parse(evt.data);
        console.log(evt.data);
        document.getElementById("messages").value += obj.user+": "+obj.message+"\n";
    };

    ws.onclose = function() {
        // websocket is closed.
        alert("Connection is closed...");
    };
}

let sendMessage = function(){
    let username = document.getElementById("username").value;
    let toSend = document.getElementById("message").value;

    messageWS = username+" "+toSend;

    ws.send(messageWS);
    alert("Message is sent...");

    ws.onmessage = function (evt) {
        document.getElementById("message").value = " ";
        let receivedMessage = evt.data;
        let obj = JSON.parse(receivedMessage);
        prevMessages.push(obj.message);
        //console.log(obj.message);
        alert("Message is received...");
        document.getElementById("messages").value += obj.user+": "+obj.message+"\n";
    };

    ws.onclose = function() {
        // websocket is closed.
        alert("Connection is closed...");
    };
}

chatRoomButton.addEventListener("click", openChatRoom);
sendMessageButton.addEventListener("click", sendMessage);


// let xhr = new XMLHttpRequest()
// xhr.open("GET", message);
// xhr.addEventListener("load", function(){console.log(this);
//     document.getElementById("resultText").value = this.responseText;
// });
// xhr.send();