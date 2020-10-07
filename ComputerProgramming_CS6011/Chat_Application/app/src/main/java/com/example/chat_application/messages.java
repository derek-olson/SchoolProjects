package com.example.chat_application;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;
import com.neovisionaries.ws.client.WebSocketException;
import com.neovisionaries.ws.client.WebSocketExtension;
import com.neovisionaries.ws.client.WebSocketFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class messages extends AppCompatActivity {
    private static final String SERVER = "ws://10.0.2.2:8080";
    private WebSocket ws = null;
    private String room = "";
    private ArrayList<String> messages = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_messages);

        // Get the Intent that started this activity and extract the string
        Intent intent = getIntent();
        room = intent.getStringExtra(MainActivity.ROOM);

        // Capture the layout's TextView and set the string as its text
        TextView displayRoomName = findViewById(R.id.roomName);
        displayRoomName.setText(room);
        System.out.println("display room name: "+room);

        WebSocketFactory factory = new WebSocketFactory().setConnectionTimeout(5000);
        try {
            final ArrayAdapter<String> itemsAdapter =
                    new ArrayAdapter<>(this, android.R.layout.simple_list_item_1,messages);

            ListView listView = (ListView) findViewById(R.id.messages_view);
            listView.setAdapter(itemsAdapter);
            ws = factory.createSocket(SERVER);
            ws.addListener(new WebSocketAdapter() {
                @Override
                public void onConnected(WebSocket websocket, Map<String,List<String>> headers) throws Exception {
                    EditText message = (EditText) findViewById(R.id.editText);
                    String messageString = message.getText().toString();
                    message.setText("");
                    ws.sendText("join: "+MainActivity.USER+" "+MainActivity.ROOM);

                }

                @Override
                public void onTextMessage(WebSocket webSocket, String message) throws Exception{
                    messages.add(message);
                    runOnUiThread(new Runnable(){
                        @Override
                        public void run(){
                            itemsAdapter.notifyDataSetChanged();
                        }
                    });
                }
            });
            ws.connectAsynchronously();

            ws.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void sendMessage(View view) {
        EditText message = (EditText) findViewById(R.id.editText);
        String messageString = message.getText().toString();
        ws.sendText(MainActivity.ROOM+ " " + MainActivity.USER + " " +messageString);
        message.setText("");
    }


}
