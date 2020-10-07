
var outMessages = [];
var chatRoomButton = document.getElementById("chatRoomButton");
var sendMessageButton = document.getElementById("sendMessageButton");
var messageWS = "";
var chatRoom = "";
var prevChatRooms = [];
var prevMessages = [];


var ws;

var openChatRoom = function(){
    var username = document.getElementById("username").value;
    var chatroom = document.getElementById("chatroom").value;

    if (ws) {
        ws.close();
    }

    ws = new WebSocket("ws://"+location.host);
    ws.onmessage = function (evt) {
        document.getElementById("message").value = " ";
        var receivedMessage = evt.data;
        //var obj = JSON.parse(receivedMessage);
        prevMessages.push(receivedMessage);
        alert("Message is received...");
        //document.getElementById("messages").value += obj.user+": "+obj.message+"\n";
        document.getElementById("messages").value += receivedMessage+"\n";
    };
    prevChatRooms.push(chatroom);
    chatRoom = "join "+username+" "+chatroom;
    ws.onopen = function(evt) {
        ws.send(chatRoom);
    };

    alert("Message is sent...");


    var xhr = new XMLHttpRequest()
    xhr.open("GET", "/index.html");
    xhr.addEventListener("load", function () {
        console.log(this);
        document.getElementById("messages").value = " ";
    });
    xhr.send();

    ws.onclose = function() {
        // websocket is closed.
        alert("Connection is closed...");
    };
}

var sendMessage = function(){
    var chatroom = document.getElementById("chatroom").value;
    var username = document.getElementById("username").value;
    var toSend = document.getElementById("message").value;

    messageWS = chatroom+" "+username+" "+toSend;

    ws.send(messageWS);
    alert("Message is sent...");

    ws.onclose = function() {
        alert("Connection is closed...");
    };
}

chatRoomButton.addEventListener("click", openChatRoom);
sendMessageButton.addEventListener("click", sendMessage);


