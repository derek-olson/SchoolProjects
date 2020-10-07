package com.example.demo.service

import org.springframework.stereotype.Service

@Service
class Service {
    var map: HashMap<String, MutableList<String>> = HashMap();

    fun sayHello(): String{
        return "Hello World"
    }

    fun joinRoom(name: String, roomName: String): String{
        var room : MutableList<String>? = map.get(roomName)
        if(room == null) room = mutableListOf()

        room.add(name)
        map.put(roomName, room)
        return "$name, thanks for joining $roomName"
    }

    fun getUsersInRoom(roomName: String): List<String>{
        return map.getOrDefault(roomName, listOf("Room does not exist"))
    }

}