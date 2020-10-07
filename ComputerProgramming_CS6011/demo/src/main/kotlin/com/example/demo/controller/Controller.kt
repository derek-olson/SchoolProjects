package com.example.demo.controller

import com.example.demo.service.Service
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RequestParam
import org.springframework.web.bind.annotation.RestController

@RestController
class Controller(private val Service: Service) {

    @GetMapping("/hello")
    fun sayHello(): String{
        return Service.sayHello()
    }

    @GetMapping("/join")
    fun joinRoom(@RequestParam name: String, @RequestParam roomName: String): String{
        return Service.joinRoom(name, roomName)
    }

    fun getUsersInRoom(@RequestParam roomName: String): List<String>{
        return Service.getUsersInRoom(roomName)
    }



}
