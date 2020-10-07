let http = require('http');
let fs = require('fs');
let mime = require("mime-types")
let WebSocketServer = require('websocket').server;

let server = http.createServer(function (req, res) {
    console.log("URL: "+ req.url);
    let resources = "resources";
    let path = resources+req.url;
    if (path == resources+"/"){
        path = resources+"/index.html";
    }else{path = resources+req.url}

    fs.readFile(path, function(err, data) {
        // if (err.code === 404){
        //     res.writeHead((int)err.code)
        // }
        res.writeHead(200, {'Content-Type': mime.lookup(path)});
        res.write(data);
        res.end();
    });
}).listen(8080);

wsServer = new WebSocketServer({
    httpServer: server,
    autoAcceptConnections: false
});

function originIsAllowed(origin) {
    // put logic here to detect whether the specified origin is allowed.
    return true;
}
let rooms = {};
wsServer.on('request', function(request) {
    if (!originIsAllowed(request.origin)) {
        // Make sure we only accept requests from an allowed origin
        request.reject();
        console.log((new Date()) + ' Connection from origin ' + request.origin + ' rejected.');
        return;
    }


    let connection = request.accept(null, request.origin);
    console.log((new Date()) + ' Connection accepted.');
    connection.on('message', function(message) {
        if (message.utf8Data.startsWith("join")){
            let room = message.utf8Data.split(" ", 3)[2];
            let user = message.utf8Data.split(" ", 3)[1];
            if (room in rooms){
                let chatroom = rooms[room];
                console.log("here 0: ");
                console.log(chatroom);
                //this may need to be rooms[room].websocket.push(connection);
                chatroom.websocket.push(connection);
                connection.sendUTF(chatroom.messages);
            }
            else{
                let chatroom = {
                    websocket: [],
                    messages: [],
                    users: []
                }
                chatroom.websocket.push(connection);
                chatroom.users.push(user);
                rooms[room] = chatroom;
                console.log("here 1: ");
                console.log(rooms);
            }
        }else {
            let room = message.utf8Data.split(" ", 3)[0];
            let user = message.utf8Data.split(" ", 3)[1];
            let text = message.utf8Data.split(" ").slice(2).join(" ");
            rooms[room].websocket.forEach(function(connection){connection.sendUTF(text)});
            rooms[room].messages.push(text);
            console.log("here 2: ");
            console.log(rooms);
        }
    });
    connection.on('close', function(reasonCode, description) {
        console.log((new Date()) + ' Peer ' + connection.remoteAddress + ' disconnected.');
    });
});


