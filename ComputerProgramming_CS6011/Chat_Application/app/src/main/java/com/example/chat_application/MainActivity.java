package com.example.chat_application;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    public static String ROOM = "";
    public static String USER = "";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void enterRoom(View view) {
        Intent intent = new Intent(this, messages.class);
        EditText chatRoom = (EditText) findViewById(R.id.chatRoom);
        String room = chatRoom.getText().toString();
        intent.putExtra(ROOM, room);
        ROOM = room;
        EditText user = (EditText) findViewById(R.id.username);
        String username = user.getText().toString();
        intent.putExtra(USER, username);
        USER = username;
        startActivity(intent);
    }

    public String getUser(){
        return USER;
    }

    public String getRoom(){
        return ROOM;
    }



}
