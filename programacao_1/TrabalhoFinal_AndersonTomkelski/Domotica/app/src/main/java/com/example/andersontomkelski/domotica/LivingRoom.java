package com.example.andersontomkelski.domotica;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Date;

public class LivingRoom extends AppCompatActivity {

    private Actuator lamp1 = new Actuator(0, 1);
    private Actuator TV = new Actuator(0, 2);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_living_room);

    }

    public void toggleLamp(View view){
        String send = lamp1.toString();
        new SendData().execute(send);
    }

    public void toggleTV(View view){
        String send = TV.toString();
        new SendData().execute(send);
    }
}
